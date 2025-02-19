#ifndef FIGURES_H
#define FIGURES_H

#define FIGURE_SIZE 4

typedef struct {
  int ***figure;
  int ***next_figure;
  int x;
  int y;
  int y_up;
  int y_down;
  int x_left;
  int x_right;
  int orientation;
} FigureInfo;

static int Figures[7][4][4][4] = {
    {{{0, 0, 9, 0}, {9, 9, 9, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 9, 0, 0}, {0, 9, 0, 0}, {0, 9, 9, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {9, 9, 9, 0}, {9, 0, 0, 0}, {0, 0, 0, 0}},
     {{9, 9, 0, 0}, {0, 9, 0, 0}, {0, 9, 0, 0}, {0, 0, 0, 0}}},
    {{{6, 6, 0, 0}, {0, 6, 6, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 6, 0}, {0, 6, 6, 0}, {0, 6, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {6, 6, 0, 0}, {0, 6, 6, 0}, {0, 0, 0, 0}},
     {{0, 6, 0, 0}, {6, 6, 0, 0}, {6, 0, 0, 0}, {0, 0, 0, 0}}},
    {{{0, 4, 0, 0}, {4, 4, 4, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 4, 0, 0}, {0, 4, 4, 0}, {0, 4, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {4, 4, 4, 0}, {0, 4, 0, 0}, {0, 0, 0, 0}},
     {{0, 4, 0, 0}, {4, 4, 0, 0}, {0, 4, 0, 0}, {0, 0, 0, 0}}},
    {{{0, 2, 2, 0}, {2, 2, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 2, 0, 0}, {0, 2, 2, 0}, {0, 0, 2, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {0, 2, 2, 0}, {2, 2, 0, 0}, {0, 0, 0, 0}},
     {{2, 0, 0, 0}, {2, 2, 0, 0}, {0, 2, 0, 0}, {0, 0, 0, 0}}},
    {{{3, 0, 0, 0}, {3, 3, 3, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 3, 3, 0}, {0, 3, 0, 0}, {0, 3, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {3, 3, 3, 0}, {0, 0, 3, 0}, {0, 0, 0, 0}},
     {{0, 3, 0, 0}, {0, 3, 0, 0}, {3, 3, 0, 0}, {0, 0, 0, 0}}},
    {{{0, 8, 8, 0}, {0, 8, 8, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 8, 8, 0}, {0, 8, 8, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 8, 8, 0}, {0, 8, 8, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 8, 8, 0}, {0, 8, 8, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
    {{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
     {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}}};

#endif