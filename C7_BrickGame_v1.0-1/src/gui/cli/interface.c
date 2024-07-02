#include "interface.h"

#include <unistd.h>

#define LEFT_BORDER_FIELD 2 * WIDTH + 2

void init_interface() {
  WINDOW* win;
  win = initscr();
  nodelay(win, TRUE);
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  timeout(0);
  curs_set(0);
  start_color();
  init_pair(1, COLOR_RED, COLOR_RED);
  init_pair(2, COLOR_GREEN, COLOR_GREEN);
  init_color(COLOR_WHITE, 1000, 647, 0);
  init_pair(3, COLOR_WHITE, COLOR_WHITE);
  init_pair(4, COLOR_BLUE, COLOR_BLUE);
  init_pair(5, COLOR_BLACK, COLOR_GREEN);
  init_pair(6, COLOR_CYAN, COLOR_CYAN);
  init_pair(7, COLOR_BLACK, COLOR_BLACK);
  init_pair(8, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(9, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(10, COLOR_WHITE, COLOR_BLACK);
}

void deinit_interface() {
  sleep(1);
  endwin();
}

void draw_interface(GameInfo_t gameinfo) {
  draw_frames();
  draw_field(gameinfo.field);
  draw_info(gameinfo);
}

void draw_frames() {
  attron(COLOR_PAIR(10));
  mvvline(1, 0, ACS_VLINE, HEIGHT);
  mvvline(1, 2 * WIDTH + 1, ACS_VLINE, HEIGHT);
  mvvline(1, 4 * WIDTH + 2, ACS_VLINE, HEIGHT);
  mvhline(0, 0, ACS_HLINE, 4 * WIDTH + 3);
  mvhline(4, LEFT_BORDER_FIELD, ACS_HLINE, 2 * WIDTH);
  mvhline(8, LEFT_BORDER_FIELD, ACS_HLINE, 2 * WIDTH);
  mvhline(12, LEFT_BORDER_FIELD, ACS_HLINE, 2 * WIDTH);
  mvhline(16, LEFT_BORDER_FIELD, ACS_HLINE, 2 * WIDTH);
  mvhline(HEIGHT + 1, 0, ACS_HLINE, 4 * WIDTH + 3);
  mvaddch(0, 0, ACS_ULCORNER);
  mvaddch(0, 4 * WIDTH + 2, ACS_URCORNER);
  mvaddch(HEIGHT + 1, 0, ACS_LLCORNER);
  mvaddch(HEIGHT + 1, 4 * WIDTH + 2, ACS_LRCORNER);
  attroff(COLOR_PAIR(10));
}

void draw_field(int** field) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      int color = field[i][j];
      if (color != 0) {
        attron(COLOR_PAIR(color));
        mvprintw(i + 1, j * 2 + 1, "  ");
        attroff(COLOR_PAIR(color));
      } else {
        attron(COLOR_PAIR(7));
        mvprintw(i + 1, j * 2 + 1, "  ");
        attroff(COLOR_PAIR(7));
      }
    }
  }
}

void draw_info(GameInfo_t gameInfo) {
  attron(COLOR_PAIR(10));
  attron(A_BOLD);
  int start_X = LEFT_BORDER_FIELD + 1;
  mvprintw(2, start_X, "              ");
  mvprintw(2, start_X, "SCORE: %d", gameInfo.score);
  mvprintw(6, start_X, "HIGH SCORE: %d", gameInfo.high_score);
  mvprintw(10, start_X, "              ");
  mvprintw(10, start_X, "LEVEL: %d", gameInfo.level);
  mvprintw(14, start_X, "NEXT:");
  mvprintw(17, start_X, "<, >, v - Move");
  mvprintw(18, start_X, "A       - Rotate");
  mvprintw(19, start_X, "Q       - Exit");
  mvprintw(20, start_X, "P       - Pause");
  attroff(COLOR_PAIR(10));
  attroff(A_BOLD);

  int figure_y = 13;
  start_X = LEFT_BORDER_FIELD + 10;
  for (int i = figure_y; i < figure_y + FIGURE_SIZE - 2; ++i) {
    for (int j = start_X; j < start_X + FIGURE_SIZE; ++j) {
      int color = gameInfo.next[i - figure_y][j - start_X];
      attron(COLOR_PAIR(color));
      mvprintw(i, 2 * j - start_X, "  ");
      attroff(COLOR_PAIR(color));
    }
  }
}

void draw_game_over() {
  draw_frames();
  attron(COLOR_PAIR(10));
  attron(A_BOLD);
  mvprintw(9, 1, "                    ");
  mvprintw(10, 1, "      GAME OVER     ");
  mvprintw(11, 1, " Press R to restart ");
  mvprintw(12, 1, " Press Q to exit    ");
  mvprintw(13, 1, "                    ");
  attroff(COLOR_PAIR(10));
  attroff(A_BOLD);
}

void draw_pause() {
  attron(COLOR_PAIR(10));
  attron(A_BOLD);
  mvprintw(9, 1, "                    ");
  mvprintw(10, 1, "        PAUSE       ");
  mvprintw(11, 1, " Press P to continue");
  mvprintw(12, 1, " Press R to restart ");
  mvprintw(13, 1, " Press Q to exit    ");
  mvprintw(14, 1, "                    ");
  attroff(COLOR_PAIR(10));
  attroff(A_BOLD);
}

void draw_start() {
  draw_frames();
  attron(COLOR_PAIR(10));
  attron(A_BOLD);
  mvprintw(10, 3, "Press S to start");
  attroff(COLOR_PAIR(10));
  attroff(A_BOLD);
}