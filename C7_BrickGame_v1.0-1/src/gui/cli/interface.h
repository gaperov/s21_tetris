#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>

#include "../../brick_game/tetris/tetris.h"

#define HEIGHT 20
#define WIDTH 10

void init_interface();

void deinit_interface();

void draw_interface(GameInfo_t gameinfo);

void draw_field(int** field);

void draw_info(GameInfo_t gameinfo);

void draw_frames();

void draw_game_over();

void draw_pause();

void draw_start();

#endif