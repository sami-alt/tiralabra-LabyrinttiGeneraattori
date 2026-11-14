
CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c11 -g -DUNITY_INCLUDE_DOUBLE
COVERAGE_FLAGS = --coverage -fprofile-abs-path
COVERAGE_DIR = coverage_tests
OBJECT_DIR = $(COVERAGE_DIR)/objects

SRC = src/point.c \
      src/edge.c \
      src/edge_list.c \
      src/triangle.c \
      src/triangulation.c \
      src/graph.c \
      src/union_find.c \
      src/kruskal.c

TEST_SRC = tests/test_main.c \
           tests/test_point.c \
           tests/test_edge.c \
           tests/test_edge_list.c \
           tests/test_triangle.c \
           tests/test_triangulation.c \
           tests/test_graph.c \
           tests/test_union_find.c \
           tests/test_kruskal.c

UNITY_SRC = ../Unity/src/unity.c

INCLUDES = -Isrc -I../Unity/src
LDLIBS = -lm

TEST_BINARY = test_runner
SRC_OBJECTS = $(patsubst src/%.c,$(OBJECT_DIR)/src_%.o,$(SRC))
TEST_OBJECTS = $(patsubst tests/%.c,$(OBJECT_DIR)/test_%.o,$(TEST_SRC))
UNITY_OBJECT = $(OBJECT_DIR)/unity.o
CPPCHECK ?= cppcheck
CLANG_TIDY ?= clang-tidy
CPPCHECK_FLAGS = --enable=warning,style,performance,portability \
                 --error-exitcode=1 \
                 --suppress=missingIncludeSystem
CLANG_TIDY_FLAGS = --quiet

.PHONY: all test coverage static-analysis cppcheck clang-tidy clean

all: test

$(TEST_BINARY): $(SRC_OBJECTS) $(TEST_OBJECTS) $(UNITY_OBJECT)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $^ $(LDLIBS) -o $@

$(OBJECT_DIR):
	mkdir -p $@

$(OBJECT_DIR)/src_%.o: src/%.c | $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $(INCLUDES) -c $< -o $@

$(OBJECT_DIR)/test_%.o: tests/%.c | $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $(INCLUDES) -c $< -o $@

$(UNITY_OBJECT): $(UNITY_SRC) | $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $(INCLUDES) -c $< -o $@

test: $(TEST_BINARY)
	./$(TEST_BINARY)

coverage: clean
	$(MAKE) --no-print-directory $(TEST_BINARY)
	./$(TEST_BINARY)
	cd $(COVERAGE_DIR) && gcov -b -c -o objects $(addprefix objects/src_,$(notdir $(SRC:.c=.o)))

static-analysis: cppcheck clang-tidy

cppcheck:
	@command -v $(CPPCHECK) >/dev/null || \
		{ echo "Error: cppcheck is not installed."; exit 1; }
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(INCLUDES) $(SRC) $(TEST_SRC)

clang-tidy:
	@command -v $(CLANG_TIDY) >/dev/null || \
		{ echo "Error: clang-tidy is not installed."; exit 1; }
	$(CLANG_TIDY) $(CLANG_TIDY_FLAGS) $(SRC) $(TEST_SRC) -- $(CFLAGS) $(INCLUDES)

clean:
	rm -f $(TEST_BINARY)
	rm -f *.gcda *.gcno *.gcov
	rm -rf $(COVERAGE_DIR)