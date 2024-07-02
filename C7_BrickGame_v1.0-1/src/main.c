#include "brick_game/tetris/tetris.h"
#include "gui/cli/interface.h"

void process_user_input(int input);

int main() {
  init();
  start();
  init_interface();
  GameInfo_t gamestate = updateCurrentState();
  while (gamestate.pause != 2) {
    process_user_input(getch());
    gamestate = updateCurrentState();
    if (gamestate.pause == 1) {
      draw_pause();
    } else if (get_screen_state() == GameScreen) {
      draw_interface(gamestate);
    } else if (get_screen_state() == GameOverScreen) {
      draw_game_over();
    } else if (get_screen_state() == StartScreen) {
      draw_start();
    }
    doupdate();
  }
  deinit_interface();
  deinit();
  return 0;
}

void process_user_input(int input) {
  switch (input) {
    case KEY_LEFT:
      userInput(Left, false);
      break;
    case KEY_RIGHT:
      userInput(Right, false);
      break;
    case 'a':
    case 'A':
      userInput(Action, false);
      break;
    case KEY_DOWN:
      userInput(Down, false);
      break;
    case 'q':
    case 'Q':
      userInput(Terminate, false);
      break;
    case 'p':
    case 'P':
      userInput(Pause, false);
      break;
    case 'r':
    case 'R':
    case 'S':
    case 's':
      userInput(Start, false);
      break;
  }
}