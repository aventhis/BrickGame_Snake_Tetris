CC = gcc
CG = g++
FLAGS = -Wall -Werror -Wextra -g 
GFLAGS = -std=c++17 -g -Wall -Werror -Wextra 
CFLAGS = -lstdc++
GCOV_FLAGS = --coverage
GCOVFLAGS = -fprofile-arcs -ftest-coverage
# -std=c11 -D_POSIX_C_SOURCE=199309L
# Змейка
BRICK_GAME_DIR = brick_game/snake
GUI_DIR = gui/cli/snake
EXE = test
# Флаги для линковки
LDFLAGS = -lncurses
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Путь к заголовочным файлам GTest
GTEST_INCLUDE = /opt/homebrew/opt/googletest/include

# Путь к библиотекам GTest
GTEST_LIB_PATH = /opt/homebrew/opt/googletest/lib

# Файлы исходного кода
SOURCES_SNAKE = $(BRICK_GAME_DIR)/snake_game_model.cpp $(GUI_DIR)/snake_game_view.cpp $(BRICK_GAME_DIR)/snake_game_controller.cpp $(BRICK_GAME_DIR)/snake_fsm.cpp $(BRICK_GAME_DIR)/snake_main.cpp

# ТЕТРИС
SOURCE_TEST_C = $(wildcard ./tests/*.c)
SOURCE_TEST_H = $(wildcard ./tests/*.h)

TARGET = brick_games

LIB = s21_tetris
LIBNAME = $(LIB).a
PROJECT = tetris
TEST = tetris_test
LIB_DEST = brick_game/tetris/game_logic.c
BACKSNAKE = brick_game/snake/*.c*
GUI_DEST = gui/cli/tetris/cli.c
CLISNAKE = gui/cli/snake/*.c*
LIB_DIR = lib
BUILD_DIR = ../build
DIST_DIR = dist
DOCS_DIR = docs
TESTS_DIR = tests
GCOV_REPORT_DIR := report
SYSTEM := $(shell uname -s)

ifeq ($(SYSTEM), Linux)
    # Код для компиляции под Linux
    OPEN_CMD = xdg-open
    ADD_LIB = -lncurses -lcheck -lsubunit -lm
else ifeq ($(SYSTEM), Darwin)
    # Код для компиляции под macOS
    OPEN_CMD = open
    ADD_LIB =  -lncurses -lcheck
    BREW := ${HOME}/homebrew
else
    $(error Unsupported system: $(SYSTEM))
endif

PATH := $(BREW)/bin:$(PATH)

# Цель по умолчанию
all_snake: $(TARGET)

$(TARGET): 
	$(CG) $(GFLAGS) $(SOURCES_SNAKE) -o $(TARGET) $(LDFLAGS)

all:  install dvi dist cli

# install: clean build_dir $(LIBNAME)
# 	$(CC) $(FLAGS) brick_game/tetris/tetris_main.c brick_game/tetris/fsm.c $(GUI_DEST) $(LIB_DIR)/$(LIBNAME) -o $(LIB_DIR)/$(PROJECT) ${ADD_LIB}
# 	mv $(LIB_DIR)/$(PROJECT) $(BUILD_DIR)

install: clean uninstall
	echo "Installation of $(TARGET).app:"
	mkdir -p ../build
	cd gui/desktop/Brick_game && qmake && make && make clean && rm -rf Makefile && mv Brick_game.app ../../../../build/$(TARGET).app
	echo "Installation completed! You can find app in the ../build/ folder!"


$(LIBNAME): lib_dir
	$(CC) $(FLAGS) -c $(LIB_DEST) -o $(LIB_DIR)/$(LIB).o
	ar rc $(LIB_DIR)/$(LIBNAME) $(LIB_DIR)/$(LIB).o
	ranlib $(LIB_DIR)/$(LIBNAME) 

# cli: clean $(LIBNAME)
# 	$(CC) $(FLAGS) brick_game/main.cpp $(GUI_DEST) brick_game/tetris/*.c $(CLISNAKE) $(BACKSNAKE) $(CFLAGS) $(LDFLAGS) -o $(TARGET)
# 	./$(TARGET)

cli: clean build_dir $(LIBNAME) 
	$(CC) $(FLAGS) brick_game/main.cpp $(GUI_DEST) $(LIB_DIR)/$(LIBNAME) brick_game/tetris/fsm.c brick_game/tetris/tetris_main.c $(CLISNAKE) $(BACKSNAKE) $(CFLAGS) $(LDFLAGS) -o $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

uninstall:
	rm -rf $(BUILD_DIR) $(LIB_DIR) $(DOCS_DIR)/latex $(DOCS_DIR)/html $(DOCS_DIR)/*.dvi
	rm -rf /tmp/highscore.txt 
	rm -rf /tmp/highscoresnake.txt 

dvi:
	doxygen Doxyfile

dist: dist_dir
	cp -rf brick_game/ $(DIST_DIR)/
	cp -rf gui/ $(DIST_DIR)/
	cp -rf docs/fsm_diagram.jpg $(DIST_DIR)/
	cp -rf Makefile $(DIST_DIR)/
	cp -rf Doxyfile ${DIST_DIR}/
	tar -czf tetris_v1.0.tar.gz ${DIST_DIR}/
	rm -rf $(DIST_DIR)/*
	mv tetris_v1.0.tar.gz $(DIST_DIR)/

gcov_$(LIBNAME):
	$(CC) $(FLAGS) $(GCOV_FLAGS) -c $(LIB_DEST) -o $(GCOV_REPORT_DIR)/$(LIB).o
	ar rc $(GCOV_REPORT_DIR)/$(LIB).a $(GCOV_REPORT_DIR)/$(LIB).o
	ranlib $(GCOV_REPORT_DIR)/$(LIB).a
	rm -rf $(GCOV_REPORT_DIR)/$(LIB).o

test_gcov: gcov_$(LIBNAME)
	$(CC) $(FLAGS) $(GCOV_FLAGS) ${SOURCE_TEST_C} $(GCOV_REPORT_DIR)/$(LIBNAME) -o $(TESTS_DIR)/$(TEST) ${ADD_LIB}
	./$(TESTS_DIR)/$(TEST)

gcov_report: clean
	$(CG) $(GFLAGS) $(GCOVFLAGS) -I$(GTEST_INCLUDE) -c tests/test.cc -o tests/test.o
	$(CG) $(GFLAGS) $(GCOVFLAGS) tests/test.o $(BRICK_GAME_DIR)/snake_game_model.cpp -L$(GTEST_LIB_PATH) $(GTEST_LIBS) -o $(EXE) $(LDFLAGS) -pthread
	./$(EXE)
	lcov --no-external --ignore-errors inconsistent -t "$(EXE)" -o test.info -c -d .
	genhtml --ignore-errors inconsistent,corrupt -o report test.info
	open report/index.html

lib_dir:
	mkdir $(LIB_DIR)

build_dir:
	mkdir $(BUILD_DIR)

dist_dir:
	mkdir $(DIST_DIR)

gcov_dir:
	mkdir $(GCOV_REPORT_DIR)

clean:
	rm -rf */*/*/*.o *.o *.g* *.info *.out lib report doxygen *.a test *.log gcov* *.dSYM $(TARGET) ../dist ../build
	rm -rf $(BUILD_DIR) $(LIB_DIR) $(DOCS_DIR)/latex $(DOCS_DIR)/html $(DOCS_DIR)/*.dvi $(DIST_DIR) $(GCOV_REPORT_DIR) $(TESTS_DIR)/$(TEST) score
	rm -rf $(TESTS_DIR)/*.gcda $(TESTS_DIR)/*.gcno $(TESTS_DIR)/*.o $(TESTS_DIR)/*.dSYM
	rm -rf *.gcno *.gcda *.txt
	rm -rf /tmp/highscore.txt
	rm -rf /tmp/highscoresnake.txt tests/test_snake_game_model
	rm -rf $(TARGET)

leaks: clean test
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --track-origins=yes ./$(TESTS_DIR)/$(TEST)

check:
	clang-format -style=google -i $(LIB_DEST) $(GUI_DEST) brick_game/tetris/game_logic.h gui/cli/cli.h brick_game/tetris/tetris_main.c brick_game/tetris/fsm.c ${SOURCE_TEST_C} ${SOURCE_TEST_H}
	# cppcheck enable=all missingIncludeSystem ${SOURCE_TEST_C}
	cppcheck enable=all missingIncludeSystem $(LIB_DEST) $(GUI_DEST) brick_game/tetris/tetris_main.c brick_game/tetris/fsm.c --check-level=exhaustive

pcheck:
	clang-format -style=google -n $(LIB_DEST) $(GUI_DEST) brick_game/tetris/game_logic.h gui/cli/cli.h brick_game/tetris/tetris_main.c ${SOURCE_TEST_C} ${SOURCE_TEST_H}

rebuild: clean all

# Tests
tests: clean
	$(CG) $(GFLAGS) -I$(GTEST_INCLUDE) -L$(GTEST_LIB_PATH) $(CFLAGS) tests/test.cc $(BRICK_GAME_DIR)/snake_game_model.cpp $(GTEST_LIBS) -o tests/test_snake_game_model
	./tests/test_snake_game_model

valgrind: clean 
	$(CXX) $(WFLAGS) $(CFLAGS) tests/test.cc $(BRICK_GAME_DIR)/snake_game_model.cpp $(LTEST) -o tests/test_snake_game_model -pthread
	valgrind --tool=memcheck --leak-check=yes ./tests/test_snake_game_model

# gcov_report: clean
# 	$(CXX) $(WFLAGS) $(CFLAGS) $(GCOVFLAGS) -c tests/test.cc
# 	$(CXX) $(WFLAGS) $(CFLAGS) $(GCOVFLAGS) tests/snake_game_model_tests.o $(BRICK_GAME_DIR)/snake_game_model.cpp $(LTEST) -o tests/test_snake_game_model -pthread
# 	./tests/test_snake_game_model
# 	lcov --no-external -t "tests/test_snake_game_model" -o test.info -c -d .
# 	genhtml -o report test.info
# 	open report/index.html
