#include "tetris.h"

#include <stdio.h>
#include <stdlib.h>

static GameInfo_t gameinfo;
static FigureInfo figureinfo;
static UserAction_t useraction;
static ScreenState gamescreenstate;
static clock_t time_manage;

int speeds[10] = {1000, 1350, 1650, 1900, 2200, 2500, 2850, 3100, 3500, 4000};

int scores[4] = {100, 400, 700, 1500};

void userInput(UserAction_t action, bool hold) {
  useraction = action;
  switch (useraction) {
    case Left:
      if (can_move_left() && gameinfo.pause == 0 &&
          gamescreenstate == GameScreen) {
        if (hold) {
          while (!hold) {
            move_left();
          }
        }
        move_left();
      }
      break;
    case Right:
      if (can_move_right() && gameinfo.pause == 0 &&
          gamescreenstate == GameScreen) {
        move_right();
      }
      break;
    case Action:
      if (can_spin() && gameinfo.pause == 0 && gamescreenstate == GameScreen) {
        spin();
      }
      break;
    case Down:
      while (can_move_down() && gameinfo.pause == 0 &&
             gamescreenstate == GameScreen) {
        move_figure();
      }
      break;
    case Terminate:
      gameinfo.pause = 2;
      break;
    case Pause:
      if (gameinfo.pause == 0 && gamescreenstate == GameScreen) {
        gameinfo.pause = 1;
      } else {
        gameinfo.pause = 0;
      }
      break;
    case Start:
      if (gameinfo.pause == 1 || gamescreenstate != GameScreen) {
        start();
        gamescreenstate = GameScreen;
      }
      break;
    case Up:
      break;
  }
}

GameInfo_t updateCurrentState() {
  if (gameinfo.pause == 0 && gamescreenstate == GameScreen &&
      (clock() - time_manage) * gameinfo.speed / CLOCKS_PER_SEC >= 1000) {
    if (can_move_down()) {
      move_figure();
      time_manage = clock();
    } else {
      check_lines(figureinfo.y + figureinfo.y_down,
                  figureinfo.y + figureinfo.y_up);
      update_level();
      spawn();
      if (!can_move_down()) {
        gamescreenstate = GameOverScreen;
      } else {
        time_manage = clock();
      }
    }
  }
  return gameinfo;
}

void init() {
  figureinfo.figure = calloc(FIGURE_SIZE, sizeof(int **));
  for (int i = 0; i < FIGURE_SIZE; ++i) {
    figureinfo.figure[i] = calloc(FIGURE_SIZE, sizeof(int *));
    for (int j = 0; j < FIGURE_SIZE; ++j) {
      figureinfo.figure[i][j] = calloc(FIGURE_SIZE, sizeof(int));
    }
  }
  figureinfo.next_figure = calloc(FIGURE_SIZE, sizeof(int **));
  for (int i = 0; i < FIGURE_SIZE; ++i) {
    figureinfo.next_figure[i] = calloc(FIGURE_SIZE, sizeof(int *));
    for (int j = 0; j < FIGURE_SIZE; ++j) {
      figureinfo.next_figure[i][j] = calloc(FIGURE_SIZE, sizeof(int));
    }
  }
  gameinfo.field = calloc(HEIGHT, sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    gameinfo.field[i] = calloc(WIDTH, sizeof(int));
  }
}

void start() {
  figureinfo.orientation = 0;
  figureinfo.x = start_x;
  figureinfo.y = start_y;
  create_figure(&figureinfo.figure);
  find_borders();
  create_figure(&figureinfo.next_figure);
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      gameinfo.field[y][x] = 0;
    }
  }
  gameinfo.pause = 0;
  gameinfo.score = 0;
  gameinfo.high_score = read_highscore();
  gameinfo.level = 1;
  gameinfo.speed = speeds[gameinfo.level - 1];
  gameinfo.next = figureinfo.next_figure[0];
  int y = 0;
  for (int i = figureinfo.y; i < figureinfo.y + FIGURE_SIZE; ++i, ++y) {
    int x = 0;
    for (int j = figureinfo.x; j < figureinfo.x + FIGURE_SIZE; ++j, ++x) {
      gameinfo.field[i][j] = figureinfo.figure[figureinfo.orientation][y][x];
    }
  }
  useraction = Start;
  time_manage = clock();
  gamescreenstate = StartScreen;
}

void deinit() {
  for (int i = 0; i < FIGURE_SIZE; ++i) {
    for (int j = 0; j < FIGURE_SIZE; ++j) {
      free(figureinfo.figure[i][j]);
    }
    free(figureinfo.figure[i]);
  }
  free(figureinfo.figure);

  for (int i = 0; i < FIGURE_SIZE; ++i) {
    for (int j = 0; j < FIGURE_SIZE; ++j) {
      free(figureinfo.next_figure[i][j]);
    }
    free(figureinfo.next_figure[i]);
  }
  free(figureinfo.next_figure);

  for (int i = 0; i < HEIGHT; i++) {
    free(gameinfo.field[i]);
  }
  free(gameinfo.field);
}

void create_figure(int ****figure) {
  int figure_num = rand() % 7;
  for (int i = 0; i < FIGURE_SIZE; ++i) {
    for (int j = 0; j < FIGURE_SIZE; ++j) {
      for (int k = 0; k < FIGURE_SIZE; ++k) {
        (*figure)[i][j][k] = Figures[figure_num][i][j][k];
      }
    }
  }
}

void find_borders() {
  figureinfo.y_up = find_up_border(figureinfo.figure, figureinfo.orientation);
  figureinfo.y_down =
      find_down_border(figureinfo.figure, figureinfo.orientation);
  figureinfo.x_left =
      find_left_border(figureinfo.figure, figureinfo.orientation);
  figureinfo.x_right =
      find_right_border(figureinfo.figure, figureinfo.orientation);
}

int find_up_border(int ***figure, int orientation) {
  int y_up = 0;
  bool found = false;
  for (int i = y_up; i < FIGURE_SIZE && found == false; ++i) {
    for (int j = 0; j < FIGURE_SIZE && found == false; ++j) {
      if (figure[orientation][i][j] != 0) {
        y_up = i;
        found = true;
      }
    }
  }
  return y_up;
}

int find_down_border(int ***figure, int orientation) {
  int y_down = FIGURE_SIZE - 1;
  bool found = false;
  for (int i = y_down; i >= 0 && found == false; --i) {
    for (int j = 0; j < FIGURE_SIZE && found == false; ++j) {
      if (figure[orientation][i][j] != 0) {
        y_down = i;
        found = true;
      }
    }
  }
  return y_down;
}

int find_right_border(int ***figure, int orientation) {
  int x_right = FIGURE_SIZE - 1;
  bool found = false;
  for (int i = x_right; i >= 0 && found == false; --i) {
    for (int j = 0; j < FIGURE_SIZE && found == false; ++j) {
      if (figure[orientation][j][i] != 0) {
        x_right = i;
        found = true;
      }
    }
  }
  return x_right;
}

int find_left_border(int ***figure, int orientation) {
  int x_left = 0;
  bool found = false;
  for (int i = x_left; i < FIGURE_SIZE && found == false; ++i) {
    for (int j = 0; j < FIGURE_SIZE && found == false; ++j) {
      if (figure[orientation][j][i] != 0) {
        x_left = i;
        found = true;
      }
    }
  }
  return x_left;
}

bool can_move_down() {
  bool solid = false;
  bool can_move = true;
  int new_y = figureinfo.y + figureinfo.y_down + 1;
  if (new_y == HEIGHT) return false;
  for (int y = figureinfo.y + figureinfo.y_down;
       y >= figureinfo.y + figureinfo.y_up && !solid && can_move; --y) {
    solid = true;
    for (int x = figureinfo.x + figureinfo.x_left;
         x <= figureinfo.x + figureinfo.x_right && can_move; ++x) {
      if (figureinfo.figure[figureinfo.orientation][y - figureinfo.y]
                           [x - figureinfo.x] == 0 &&
          (y - figureinfo.y == figureinfo.y_down ||
           figureinfo.figure[figureinfo.orientation][y - figureinfo.y + 1]
                            [x - figureinfo.x] == 0)) {
        solid = false;
      }
      if (figureinfo.figure[figureinfo.orientation][y - figureinfo.y]
                           [x - figureinfo.x] != 0 &&
          (y - figureinfo.y == figureinfo.y_down ||
           figureinfo.figure[figureinfo.orientation][y - figureinfo.y + 1]
                            [x - figureinfo.x] == 0)) {
        if (gameinfo.field[y + 1][x] != 0) {
          can_move = false;
        }
      }
    }
  }
  return can_move;
}

void move_figure() {
  clean();
  figureinfo.y += 1;
  fill();
}

bool can_move_right() {
  bool solid = false;
  bool can_move = true;
  int new_x = figureinfo.x + figureinfo.x_right + 1;
  if (new_x == WIDTH) return false;
  for (int x = figureinfo.x + figureinfo.x_right;
       x >= figureinfo.x + figureinfo.x_left && !solid && can_move; --x) {
    solid = true;
    for (int y = figureinfo.y + figureinfo.y_up;
         y <= figureinfo.y + figureinfo.y_down && can_move; ++y) {
      if (figureinfo.figure[figureinfo.orientation][y - figureinfo.y]
                           [x - figureinfo.x] == 0 &&
          (x - figureinfo.x == FIGURE_SIZE - 1 ||
           figureinfo.figure[figureinfo.orientation][y - figureinfo.y]
                            [x - figureinfo.x + 1] == 0)) {
        solid = false;
      }
      if (figureinfo.figure[figureinfo.orientation][y - figureinfo.y]
                           [x - figureinfo.x] != 0 &&
          (x - figureinfo.x == figureinfo.x_right ||
           figureinfo.figure[figureinfo.orientation][y - figureinfo.y]
                            [x - figureinfo.x + 1] == 0)) {
        if (gameinfo.field[y][x + 1] != 0) {
          can_move = false;
        }
      }
    }
  }
  return can_move;
}

void move_right() {
  clean();
  figureinfo.x += 1;
  fill();
}

bool can_move_left() {
  bool solid = false;
  bool can_move = true;
  int new_x = figureinfo.x + figureinfo.x_left - 1;
  if (new_x == -1) return false;
  for (int x = figureinfo.x + figureinfo.x_left;
       x >= figureinfo.x + figureinfo.x_right && !solid && can_move; ++x) {
    solid = true;
    for (int y = figureinfo.y + figureinfo.y_up;
         y <= figureinfo.y + figureinfo.y_down && can_move; ++y) {
      if (figureinfo.figure[figureinfo.orientation][y - figureinfo.y]
                           [x - figureinfo.x] == 0 &&
          (x - figureinfo.x == 0 ||
           figureinfo.figure[figureinfo.orientation][y - figureinfo.y]
                            [x - figureinfo.x - 1] == 0)) {
        solid = false;
      }
      if (figureinfo.figure[figureinfo.orientation][y - figureinfo.y]
                           [x - figureinfo.x] != 0 &&
          (x - figureinfo.x == figureinfo.x_left ||
           figureinfo.figure[figureinfo.orientation][y - figureinfo.y]
                            [x - figureinfo.x - 1] == 0)) {
        if (gameinfo.field[y][x - 1] != 0) {
          can_move = false;
        }
      }
    }
  }
  return can_move;
}

void move_left() {
  clean();
  figureinfo.x -= 1;
  fill();
}

bool can_spin() {
  bool can_spin = true;
  int d_x = 0;
  int next_orientation = figureinfo.orientation + 1;
  if (next_orientation == FIGURE_SIZE) next_orientation = 0;
  int y_down = find_down_border(figureinfo.figure, next_orientation);
  if (y_down >= HEIGHT) return false;
  int x_left = find_left_border(figureinfo.figure, next_orientation);
  int x_right = find_right_border(figureinfo.figure, next_orientation);
  int y_up = find_up_border(figureinfo.figure, next_orientation);
  if (figureinfo.x + x_right >= WIDTH) {
    d_x = -(figureinfo.x + x_right - WIDTH + 1);
  }
  if (figureinfo.x + x_left < 0) d_x = -(figureinfo.x + x_left);
  int y_fig = y_up;
  for (int y = figureinfo.y + y_up; y <= figureinfo.y + y_down && can_spin;
       ++y, ++y_fig) {
    int x_fig = x_left;
    for (int x = figureinfo.x + x_left + d_x;
         x <= figureinfo.x + x_right + d_x && can_spin; ++x, ++x_fig) {
      if (gameinfo.field[y][x] != 0 &&
          figureinfo.figure[next_orientation][y_fig][x_fig] != 0 &&
          figureinfo.figure[figureinfo.orientation][y - figureinfo.y]
                           [x - figureinfo.x] == 0) {
        can_spin = false;
      }
    }
  }
  return can_spin;
}

void spin() {
  clean();
  figureinfo.orientation += 1;
  if (figureinfo.orientation == FIGURE_SIZE) figureinfo.orientation = 0;
  find_borders();
  if (figureinfo.x + figureinfo.x_right >= WIDTH) {
    figureinfo.x -= (figureinfo.x + figureinfo.x_right - WIDTH + 1);
  }
  if (figureinfo.x + figureinfo.x_left < 0) {
    figureinfo.x -= (figureinfo.x + figureinfo.x_left);
  }
  fill();
}

void spawn() {
  figureinfo.orientation = 0;
  figureinfo.x = start_x;
  figureinfo.y = start_y;
  for (int i = 0; i < FIGURE_SIZE; ++i) {
    for (int j = 0; j < FIGURE_SIZE; ++j) {
      for (int k = 0; k < FIGURE_SIZE; ++k) {
        figureinfo.figure[i][j][k] = figureinfo.next_figure[i][j][k];
      }
    }
  }
  find_borders();
  create_figure(&figureinfo.next_figure);
  gameinfo.next = figureinfo.next_figure[0];
}

void clean() {
  for (int y = figureinfo.y + figureinfo.y_up;
       y <= figureinfo.y + figureinfo.y_down; ++y) {
    for (int x = figureinfo.x + figureinfo.x_left;
         x <= figureinfo.x + figureinfo.x_right; ++x) {
      if (figureinfo.figure[figureinfo.orientation][y - figureinfo.y]
                           [x - figureinfo.x] != 0) {
        gameinfo.field[y][x] = 0;
      }
    }
  }
}

void fill() {
  int y_fig = 0;
  for (int y = figureinfo.y; y <= figureinfo.y + figureinfo.y_down;
       ++y, ++y_fig) {
    int x_fig = figureinfo.x_left;
    for (int x = figureinfo.x + figureinfo.x_left;
         x <= figureinfo.x + figureinfo.x_right; ++x, ++x_fig) {
      if (figureinfo.figure[figureinfo.orientation][y_fig][x_fig] != 0) {
        gameinfo.field[y][x] =
            figureinfo.figure[figureinfo.orientation][y_fig][x_fig];
      }
    }
  }
}

void check_lines(int y_down, int y_up) {
  int count_destroyed_rows = 0;
  for (int i = y_up; i <= y_down; ++i) {
    if (row_is_complete(i)) {
      destroy_row(i);
      count_destroyed_rows += 1;
    }
  }
  if (count_destroyed_rows > 0) update_score(count_destroyed_rows);
}

bool row_is_complete(int row) {
  bool complete = true;
  for (int x = 0; x < WIDTH && complete; ++x) {
    if (gameinfo.field[row][x] == 0) complete = false;
  }
  return complete;
}

void destroy_row(int row) {
  bool flag = true;
  int y = row;
  while (flag) {
    bool empty_row = true;
    for (int x = 0; x < WIDTH; ++x) {
      if (y == 0) {
        gameinfo.field[y][x] = 0;
      } else {
        if (gameinfo.field[y - 1][x] != 0) empty_row = false;
        gameinfo.field[y][x] = gameinfo.field[y - 1][x];
      }
    }
    y--;
    if (y == 0 || empty_row) flag = false;
  }
}

void update_score(int count_destroyed_rows) {
  gameinfo.score += scores[count_destroyed_rows - 1];
  if (gameinfo.score > gameinfo.high_score) update_high_score();
}

void update_high_score() {
  gameinfo.high_score = gameinfo.score;
  FILE *f = fopen(SCORE_FILENAME, "w");
  if (f != NULL) {
    fprintf(f, "%d", gameinfo.high_score);
  }
  fclose(f);
}

int read_highscore() {
  int high_score = 0;
  FILE *f = fopen(SCORE_FILENAME, "r");
  if (f != NULL) {
    fscanf(f, "%d", &high_score);
    fclose(f);
  }
  return high_score;
}

void update_level() {
  if (gameinfo.level < 10 && gameinfo.score / 600 + 1 > gameinfo.level) {
    gameinfo.level = gameinfo.score / 600 + 1;
    gameinfo.speed = speeds[gameinfo.level - 1];
  }
}

int get_screen_state() { return gamescreenstate; }

FigureInfo get_figure_info() { return figureinfo; }