#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>
#include <time.h>

#include "figures.h"

#define HEIGHT 20
#define WIDTH 10

#define start_x 4
#define start_y 0

#define FIGURE_SIZE 4

#define SCORE_FILENAME "../high_score.txt"

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Down,
  Up,
  Action
} UserAction_t;

typedef struct {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum { StartScreen, GameScreen, GameOverScreen } ScreenState;

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

void init();
void deinit();
void start();

void create_figure(int**** figure);

int find_up_border(int*** figure, int orientation);

int find_down_border(int*** figure, int orientation);

int find_right_border(int*** figure, int orientation);

int find_left_border(int*** figure, int orientation);

void find_borders();

bool can_move_down();
bool can_move_right();
bool can_move_left();

bool can_spin();

void move_figure();
void move_right();
void move_left();
void spin();
void spawn();
void clean();
void fill();

void check_lines(int y_down, int y_up);

bool row_is_complete(int row);

void destroy_row(int row);

void update_score(int count_destroyed_rows);

void update_high_score();

int read_highscore();

void update_level();

int get_screen_state();

FigureInfo get_figure_info();

#endif