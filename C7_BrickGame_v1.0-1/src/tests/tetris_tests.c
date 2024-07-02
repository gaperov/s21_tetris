
#include <check.h>
#include <stdlib.h>

#include "../brick_game/tetris/tetris.h"

START_TEST(test_tetris_init) {
  init();
  start();
  GameInfo_t gamestate = updateCurrentState();
  ck_assert_int_eq(gamestate.level, 1);
  ck_assert_int_eq(gamestate.score, 0);
  ck_assert_int_eq(gamestate.speed, 1000);
  ck_assert_int_eq(gamestate.pause, 0);
  ck_assert_int_eq(get_screen_state(), StartScreen);
  deinit();
}
END_TEST

START_TEST(test_move_down_1) {
  init();
  start();
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_eq(get_figure_info().y, start_y);
  move_figure();
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_eq(get_figure_info().y, start_y + 1);
  move_figure();
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_eq(get_figure_info().y, start_y + 2);
  deinit();
}
END_TEST

START_TEST(test_move_down_2) {
  init();
  start();
  while (get_figure_info().y + get_figure_info().y_down != HEIGHT - 1 &&
         can_move_down()) {
    move_figure();
  }
  ck_assert_int_eq(can_move_down(), 0);
  spawn();
  while (can_move_down()) {
    move_figure();
  }
  ck_assert_int_eq(can_move_down(), 0);
  ck_assert_int_ne(get_figure_info().y + get_figure_info().y_down, HEIGHT - 1);
  deinit();
}
END_TEST

START_TEST(test_move_right_1) {
  init();
  start();
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_eq(get_figure_info().y, start_y);
  move_right();
  ck_assert_int_eq(get_figure_info().x, start_x + 1);
  ck_assert_int_eq(get_figure_info().y, start_y);
  move_right();
  ck_assert_int_eq(get_figure_info().x, start_x + 2);
  ck_assert_int_eq(get_figure_info().y, start_y);
  deinit();
}
END_TEST

START_TEST(test_move_right_2) {
  init();
  start();
  while (get_figure_info().x + get_figure_info().x_right != WIDTH - 1 &&
         can_move_right()) {
    move_right();
  }
  ck_assert_int_eq(can_move_right(), 0);
  while (get_figure_info().y + get_figure_info().y_down != HEIGHT - 1 &&
         can_move_down()) {
    move_figure();
  }
  spawn();
  while (get_figure_info().y + get_figure_info().y_down != HEIGHT - 1 &&
         can_move_down()) {
    move_figure();
  }
  while (can_move_right()) {
    move_right();
  }
  ck_assert_int_eq(can_move_down(), 0);
  ck_assert_int_eq(can_move_right(), 0);
  ck_assert_int_ne(get_figure_info().x + get_figure_info().x_right, WIDTH);
  deinit();
}
END_TEST

START_TEST(test_move_left_1) {
  init();
  start();
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_eq(get_figure_info().y, start_y);
  move_left();
  ck_assert_int_eq(get_figure_info().x, start_x - 1);
  ck_assert_int_eq(get_figure_info().y, start_y);
  move_left();
  ck_assert_int_eq(get_figure_info().x, start_x - 2);
  ck_assert_int_eq(get_figure_info().y, start_y);
  deinit();
}
END_TEST

START_TEST(test_move_left_2) {
  init();
  start();
  while (get_figure_info().x + get_figure_info().x_left > 0 &&
         can_move_left()) {
    move_left();
  }
  ck_assert_int_eq(can_move_left(), 0);
  while (get_figure_info().y + get_figure_info().y_down != HEIGHT - 1 &&
         can_move_down()) {
    move_figure();
  }
  spawn();
  while (get_figure_info().y + get_figure_info().y_down != HEIGHT - 1 &&
         can_move_down()) {
    move_figure();
  }
  while (can_move_left()) {
    move_left();
  }
  ck_assert_int_eq(can_move_down(), 0);
  ck_assert_int_eq(can_move_left(), 0);
  ck_assert_int_eq(get_figure_info().x + get_figure_info().x_left, 0);

  deinit();
}
END_TEST

START_TEST(test_spin_1) {
  init();
  start();
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_eq(get_figure_info().y, start_y);
  ck_assert_int_eq(get_figure_info().orientation, 0);
  spin();
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_eq(get_figure_info().y, start_y);
  ck_assert_int_eq(get_figure_info().orientation, 1);
  spin();
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_eq(get_figure_info().y, start_y);
  ck_assert_int_eq(get_figure_info().orientation, 2);
  spin();
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_eq(get_figure_info().y, start_y);
  ck_assert_int_eq(get_figure_info().orientation, 3);
  spin();
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_eq(get_figure_info().y, start_y);
  ck_assert_int_eq(get_figure_info().orientation, 0);
  deinit();
}
END_TEST

START_TEST(test_spin_2) {
  init();
  start();
  while (get_figure_info().x + get_figure_info().x_right != WIDTH - 1 &&
         can_move_right()) {
    move_right();
  }
  for (int i = 1; i < FIGURE_SIZE; ++i) {
    ck_assert_int_eq(can_spin(), 1);
    spin();
    ck_assert_int_eq(get_figure_info().orientation, i);
  }
  ck_assert_int_eq(can_spin(), 1);
  spin();
  ck_assert_int_eq(get_figure_info().orientation, 0);
  deinit();
}
END_TEST

START_TEST(test_game) {
  init();
  start();
  userInput(Start, false);
  clock_t before = clock();
  for (int i = 0; i < 3; ++i) {
    while (clock() < before + 1000000) {
      updateCurrentState();
    }
    userInput(Down, false);
    before = clock();
  }
  deinit();
}
END_TEST

START_TEST(test_right_button) {
  init();
  start();
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_eq(get_figure_info().y, start_y);
  userInput(Right, false);
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_eq(get_figure_info().y, start_y);
  userInput(Start, false);
  userInput(Right, false);
  ck_assert_int_eq(get_figure_info().x, start_x + 1);
  ck_assert_int_eq(get_figure_info().y, start_y);
  userInput(Right, false);
  ck_assert_int_eq(get_figure_info().x, start_x + 2);
  ck_assert_int_eq(get_figure_info().y, start_y);
  deinit();
}
END_TEST

START_TEST(test_left_button) {
  init();
  start();
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_eq(get_figure_info().y, start_y);
  userInput(Left, false);
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_eq(get_figure_info().y, start_y);
  userInput(Start, false);
  userInput(Left, false);
  ck_assert_int_eq(get_figure_info().x, start_x - 1);
  ck_assert_int_eq(get_figure_info().y, start_y);
  userInput(Left, false);
  ck_assert_int_eq(get_figure_info().x, start_x - 2);
  ck_assert_int_eq(get_figure_info().y, start_y);
  deinit();
}
END_TEST

START_TEST(test_down_button) {
  init();
  start();
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_eq(get_figure_info().y, start_y);
  ck_assert_int_eq(can_move_down(), 1);
  userInput(Down, false);
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_eq(get_figure_info().y, start_y);
  ck_assert_int_eq(can_move_down(), 1);
  userInput(Start, false);
  userInput(Down, false);
  ck_assert_int_eq(get_figure_info().x, start_x);
  ck_assert_int_ne(get_figure_info().y, start_y);
  ck_assert_int_eq(get_figure_info().y + get_figure_info().y_down, HEIGHT - 1);
  ck_assert_int_eq(can_move_down(), 0);
  deinit();
}
END_TEST

START_TEST(test_action_button) {
  init();
  start();
  ck_assert_int_eq(get_figure_info().orientation, 0);
  userInput(Action, false);
  ck_assert_int_eq(get_figure_info().orientation, 0);
  userInput(Start, false);
  userInput(Action, false);
  ck_assert_int_eq(get_figure_info().orientation, 1);
  userInput(Action, false);
  ck_assert_int_eq(get_figure_info().orientation, 2);
  userInput(Action, false);
  ck_assert_int_eq(get_figure_info().orientation, 3);
  userInput(Action, false);
  ck_assert_int_eq(get_figure_info().orientation, 0);
  deinit();
}
END_TEST

START_TEST(test_pause_button) {
  init();
  start();
  GameInfo_t gameState = updateCurrentState();
  ck_assert_int_eq(gameState.pause, 0);
  userInput(Pause, false);
  gameState = updateCurrentState();
  ck_assert_int_eq(gameState.pause, 0);
  userInput(Start, false);
  ck_assert_int_eq(get_screen_state(), GameScreen);
  userInput(Pause, false);
  gameState = updateCurrentState();
  ck_assert_int_eq(gameState.pause, 1);
  userInput(Pause, false);
  gameState = updateCurrentState();
  ck_assert_int_eq(gameState.pause, 0);
  deinit();
}
END_TEST

START_TEST(test_terminate_button) {
  init();
  start();
  ck_assert_int_eq(updateCurrentState().pause, 0);
  userInput(Terminate, false);
  ck_assert_int_eq(updateCurrentState().pause, 2);
  deinit();
}
END_TEST

START_TEST(test_score_and_level) {
  init();
  start();
  userInput(Start, false);
  ck_assert_int_eq(updateCurrentState().score, 0);
  ck_assert_int_eq(updateCurrentState().level, 1);
  ck_assert_int_eq(updateCurrentState().speed, 1000);
  update_score(1);
  update_level();
  ck_assert_int_eq(updateCurrentState().score, 100);
  ck_assert_int_eq(updateCurrentState().level, 1);
  ck_assert_int_eq(updateCurrentState().speed, 1000);
  update_score(2);
  update_level();
  ck_assert_int_eq(updateCurrentState().score, 500);
  ck_assert_int_eq(updateCurrentState().level, 1);
  ck_assert_int_eq(updateCurrentState().speed, 1000);
  update_score(3);
  update_level();
  ck_assert_int_eq(updateCurrentState().score, 1200);
  ck_assert_int_eq(updateCurrentState().level, 3);
  ck_assert_int_eq(updateCurrentState().speed, 1650);
  update_score(4);
  update_level();
  ck_assert_int_eq(updateCurrentState().score, 2700);
  ck_assert_int_eq(updateCurrentState().level, 5);
  ck_assert_int_eq(updateCurrentState().speed, 2200);
  deinit();
}
END_TEST

START_TEST(test_high_score) {
  init();
  start();
  userInput(Start, false);
  ck_assert_int_eq(updateCurrentState().score, 0);
  ck_assert_int_ne(updateCurrentState().score, updateCurrentState().high_score);
  while (updateCurrentState().score < updateCurrentState().high_score) {
    update_score(4);
  }
  ck_assert_int_eq(updateCurrentState().score, updateCurrentState().high_score);
  deinit();
}
END_TEST

Suite *tetris_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("test_tetris");

  tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_tetris_init);
  tcase_add_test(tc_core, test_move_down_1);
  tcase_add_test(tc_core, test_move_down_2);
  tcase_add_test(tc_core, test_move_right_1);
  tcase_add_test(tc_core, test_move_right_2);
  tcase_add_test(tc_core, test_move_left_1);
  tcase_add_test(tc_core, test_move_left_2);
  tcase_add_test(tc_core, test_spin_1);
  tcase_add_test(tc_core, test_spin_2);
  tcase_add_test(tc_core, test_game);
  tcase_add_test(tc_core, test_right_button);
  tcase_add_test(tc_core, test_left_button);
  tcase_add_test(tc_core, test_down_button);
  tcase_add_test(tc_core, test_action_button);
  tcase_add_test(tc_core, test_pause_button);
  tcase_add_test(tc_core, test_terminate_button);
  tcase_add_test(tc_core, test_score_and_level);
  tcase_add_test(tc_core, test_high_score);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s_tetris;
  SRunner *sr;

  s_tetris = tetris_suite();

  sr = srunner_create(s_tetris);

  srunner_run_all(sr, CK_NORMAL);

  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}