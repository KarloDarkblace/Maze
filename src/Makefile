CC := g++
CFLAGS := -Wall -Werror -Wextra -std=c++17 -g
LDFLAGS :=

BUILD_DIR := ../build
NAME_TASK := A1_MAZE_CPP

GTEST_FLAGS = -lgtest_main -lgtest
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS = --tool=memcheck --leak-check=yes

MODEL_DIR := model
MODEL_SRC := $(wildcard $(MODEL_DIR)/*.cc)
MODEL_OBJ := $(patsubst %.cc,%.o,$(MODEL_SRC))

TEST_DIR := tests
TEST_SRC := $(wildcard $(TEST_DIR)/*.cc)
TEST_OBJ := $(patsubst %.cc,%.o,$(TEST_SRC))
TEST_EXEC := s21_object_test*

OS := $(shell uname -s)

ifeq ($(OS),Linux)
	LDFLAGS += -lstdc++ -pthread -lrt -lm
	APP_FILE := MazeCPP
	OPEN_CMD := xdg-open
else ifeq ($(OS),Darwin)
	LDFLAGS += -lstdc++ -lm
	APP_FILE := MazeCPP.app
	OPEN_CMD := open
endif

all: clean install

install:
	@echo "┏=============================┓"
	@echo "┃    Start installation...    ┃"
	@echo "┗=============================┛"
	@mkdir -p $(BUILD_DIR)
	@qmake6 -o $(BUILD_DIR)/Makefile view/MazeCPP.pro
	@make -C $(BUILD_DIR)
	@make -C $(BUILD_DIR) clean
	@rm -rf $(BUILD_DIR)/.qmake.stash $(BUILD_DIR)/Makefile
	@echo "┏=================================================┓"
	@echo "┃        The installation was successful.         ┃"
	@echo "┃    The executable file is located in build.     ┃"
	@echo "┗=================================================┛"

uninstall:
	@echo "┏=================================┓"
	@echo "┃    Uninstalling a program...    ┃"
	@echo "┗=================================┛"
	@rm -rf $(BUILD_DIR)

dvi:
	@open README.md

dist:
	@echo "┏=================================┓"
	@echo "┃    Creating distribution...     ┃"
	@echo "┗=================================┛"
	@tar -czvf MazeCPP.tgz README.md $(BUILD_DIR)/$(APP_FILE)
	@echo "┏====================================┓"
	@echo "┃    Distribution tgz is ready.      ┃"
	@echo "┗====================================┛"

gcov_report: clean
	@echo "┏====================================┓"
	@echo "┃     Generating html report ...     ┃"
	@echo "┗====================================┛"
	@$(CC) $(GCOV_FLAGS) $(CFLAGS) $(TEST_SRC) $(MODEL_SRC) $(GTEST_FLAGS) $(LDFLAGS) -o $(TEST_EXEC)
	@./$(TEST_EXEC)
	@lcov --capture --directory . --output-file coverage.info
	@lcov --remove coverage.info '/usr/*' --output-file coverage.info
	@lcov --list coverage.info
	@genhtml coverage.info --output-directory report
	@rm -f *.gcno *.gcda *.info $(TEST_EXEC)
	@echo "┏=========================================┓"
	@echo "┃     HTML report is ready. Opening...    ┃"
	@echo "┗=========================================┛"
	@$(OPEN_CMD) ./report/index.html &

tests:
	$(CC) $(CFLAGS) $(TEST_SRC) $(MODEL_SRC) $(GTEST_FLAGS) -o $(TEST_EXEC) $(LDFLAGS)
	./$(TEST_EXEC)

valgrind:
	$(CC) $(CFLAGS) $(TEST_SRC) $(MODEL_SRC) $(GTEST_FLAGS) -o $(TEST_EXEC) $(LDFLAGS)
	valgrind $(VALGRIND_FLAGS) -s ./$(TEST_EXEC)

clang:
	@echo "┏=================================================┓"
	@echo "┃  Formatting code according to Google Style...   ┃"
	@echo "┗=================================================┛"
	clang-format -i controller/*.h view/*.h model/*.h
	clang-format -i tests/*.cc view/*.cc model/*.cc

clean:
	@echo "┏===============================┓"
	@echo "┃  Deleting temporary files...  ┃"
	@echo "┗===============================┛"
	@rm -rf $(TEST_EXEC)
	@rm -rf report

.PHONY: all install uninstall dvi dist gcov_report tests valgrind clang clean
