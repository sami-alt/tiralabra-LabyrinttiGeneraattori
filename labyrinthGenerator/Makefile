CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c11 -g -DUNITY_INCLUDE_DOUBLE

SRC = src/point.c \
      src/edge.c \
      src/edge_list.c \
      src/triangle.c \
      src/triangulation.c

TEST_SRC = tests/test_main.c \
           tests/test_point.c \
           tests/test_edge.c \
           tests/test_edge_list.c \
           tests/test_triangle.c\
           tests/test_triangulation.c

UNITY_SRC = ../Unity/src/unity.c

INCLUDES = -Isrc -I../Unity/src

LDLIBS = -lm

TEST_BINARY = test_runner

.PHONY: all test clean

all: test

$(TEST_BINARY): $(SRC) $(TEST_SRC) $(UNITY_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) $(TEST_SRC) $(UNITY_SRC) $(LDLIBS) -o $(TEST_BINARY)

test: $(TEST_BINARY)
	./$(TEST_BINARY)

clean:
	rm -f $(TEST_BINARY)