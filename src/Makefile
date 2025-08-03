# ===== Компилятор и флаги =====
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
CHECK_LIBS = -lcheck -lm -lsubunit

BUILD_DIR = build
SRC_OBJ_DIR = $(BUILD_DIR)/src
TEST_OBJ_DIR = $(BUILD_DIR)/tests

COV_DIR = coverage
COV_INFO = coverage.info
COV_FILTERED = coverage_filtered.info

# ===== Включение флагов покрытия при необходимости =====
GCOV ?= 0
ifeq ($(GCOV), 1)
    CFLAGS += $(GCOV_FLAGS)
endif

# ===== Файлы библиотеки =====
SRC = $(wildcard s21_*.c)
OBJ = $(patsubst %.c, $(SRC_OBJ_DIR)/%.o, $(SRC))
LIB_NAME = s21_decimal.a

# ===== Тестовые файлы =====
TEST_DIR = tests
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(patsubst %.c, %.o, $(TEST_SRC))
TEST_OBJ = $(patsubst $(TEST_DIR)/%.c, $(TEST_OBJ_DIR)/%.o, $(TEST_SRC))
TEST_BIN = test_app

# ===== Цель: all (полная сборка, запуск и отчёт покрытия) =====
all: s21_decimal.a

# ===== Цель: полная пересборка без покрытия =====
re: clean $(LIB_NAME) test_build

# ===== Цель: сборка библиотеки без покрытия =====
s21_decimal.a: $(OBJ)
	ar rcs $(LIB_NAME) $(OBJ)
	ranlib $(LIB_NAME)

# ===== Цель: сборка тестового приложения без покрытия =====
test_build: $(TEST_BIN)

# ===== Цель: запуск тестов (предполагается, что собраны) =====
test: test_build
	./$(TEST_BIN)

# ===== Цель: сборка с покрытием (пересборка библиотеки и тестов с флагами покрытия) =====
coverage_build:
	$(MAKE) clean
	$(MAKE) GCOV=1 $(LIB_NAME)
	$(MAKE) GCOV=1 test_build

# ===== Цель: генерация отчёта покрытия, зависит от сборки с покрытием и запуска тестов =====
gcov_report: re coverage_build
	./$(TEST_BIN)
	lcov --capture --directory . --output-file $(COV_INFO) --rc branch_coverage=1
	lcov --remove $(COV_INFO) '*/$(TEST_DIR)/*' --output-file $(COV_FILTERED) --rc branch_coverage=1
	genhtml $(COV_FILTERED) --output-directory $(COV_DIR) --rc branch_coverage=1

# ===== Сборка тестового приложения =====
$(TEST_BIN): $(TEST_OBJ) $(LIB_NAME)
	$(CC) $(CFLAGS) -I. $(TEST_OBJ) $(LIB_NAME) -o $(TEST_BIN) $(CHECK_LIBS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(SRC_OBJ_DIR):
	mkdir -p $(SRC_OBJ_DIR)

$(TEST_OBJ_DIR):
	mkdir -p $(TEST_OBJ_DIR)

cppcheck:
	cppcheck --enable=all --inconclusive --std=c11 --quiet --force \
  --suppress=missingIncludeSystem $(SRC) $(TEST_DIR)/

%_cpp:
	cppcheck --enable=all --inconclusive --std=c11 --quiet --force \
  --suppress=missingIncludeSystem "s21_$*.c"

# ===== Цель: проверка на утечки памяти с помощью valgrind =====
valgrind: test_build
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes ./$(TEST_BIN)

%_suite: test_build
	CK_RUN_SUITE="$*" valgrind --tool=memcheck --leak-check=yes ./$(TEST_BIN)

%_test: test_build
	CK_RUN_SUITE="$*" ./$(TEST_BIN)

# ===== Компиляция объектных файлов библиотеки =====
$(SRC_OBJ_DIR)/%.o: %.c s21_decimal.h | $(SRC_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ===== Компиляция объектных файлов тестов =====
$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c s21_decimal.h | $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) -I. -c $< -o $@

# ===== Очистка =====
clean:
	rm -rf $(BUILD_DIR)
	rm -f *.info $(TEST_BIN) $(LIB_NAME)
	rm -rf coverage

format:
	clang-format -i -style=Google *.c *.h tests/*.c