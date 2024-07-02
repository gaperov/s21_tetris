CC= gcc
CFLAGS= -c -Wall -Werror -Wextra -std=c11
LFLAGS = -lncurses
SOURCES = gui/cli/interface.c brick_game/tetris/tetris.c main.c
OBJECTS = interface.o tetris.o main.o
BACKEND_DIR=brick_game/tetris
FRONTEND_DIR=gui/cli
TEST_DIR=tests
GCOVFLAGS=-fprofile-arcs -ftest-coverage
DOCS_DIR=docs
DIST_DIR=tetris_1.0
DIST_FILE=tetris_1.0.tar.gz
BUILD_DIR= ../build


ifeq ($(shell uname -s),Linux)
	OPEN_CMD = xdg-open
  	ADD_LIB = -lcheck -lsubunit -lrt -lm -lpthread -D_GNU_SOURCE
	RFLAGS = -lcheck -lsubunit -lm -lrt -lpthread -DLinux
	BREW = .
endif

ifeq ($(shell uname -s),Darwin)
	OPEN_CMD = open
	RFLAGS = -lcheck -lm -DMacos
	BREW := ${HOME}/homebrew
endif

PATH := $(BREW)/bin:$(PATH)

all: install

install:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(ADD_LIB) $(SOURCES)
	$(CC) $(OBJECTS) -o $(BUILD_DIR)/tetris $(LFLAGS)
	rm -rf $(OBJECTS)

uninstall: clean

rebuild: clean install

test: rebuild
	$(CC) $(CFLAGS) $(BACKEND_DIR)/tetris.c -o $(BUILD_DIR)/tetris.o
	ar rcs $(BUILD_DIR)/tetris.a $(BUILD_DIR)/tetris.o
	$(CC) $(TEST_DIR)/tetris_tests.c -L. $(BUILD_DIR)/tetris.a -o $(BUILD_DIR)/tetris_tests -lcheck
	./$(BUILD_DIR)/tetris_tests
	rm -rf $(BUILD_DIR)/*.o  $(BUILD_DIR)/*.a


valgrind: test
	CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes --log-file=RESULT_VALGRIND.txt ./$(BUILD_DIR)/tetris_tests


gcov_report: clean ${SOURCES}
	gcc --coverage brick_game/tetris/tetris.c tests/tetris_tests.c -o test ${RFLAGS}
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	$(OPEN_CMD) ./report/index.html

doxygen: rebuild
	mkdir -p $(DOCS_DIR)
	doxygen Doxyfile

dvi: doxygen
	open docs/html/index.html

dist: doxygen
	mkdir -p $(DIST_DIR)
	mkdir -p $(DIST_DIR)/src
	cp -r src $(DIST_DIR)/src
	cp -r Makefile Doxyfile $(DIST_DIR)
	tar -czf $(DIST_FILE) $(DIST_DIR)/*

format:
	clang-format --style=file:"../materials/linters/.clang-format" -i brick_game/tetris/* gui/cli/* tests/* main.c
	clang-format --style=file:"../materials/linters/.clang-format" -n brick_game/tetris/* gui/cli/* tests/* main.c

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem brick_game/tetris/* src/gui/cli/* src/tests/* src/main.c


clean:
	rm -rf *.o *.gcno *.gcda *.info *.a tetris_tests RESULT_VALGRIND.txt docs tetris html latex report test $(DIST_DIR) $(DIST_FILE) $(BUILD_DIR)