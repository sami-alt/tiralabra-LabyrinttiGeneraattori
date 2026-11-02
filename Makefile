CC      = gcc
CFLAGS  = -Wall -Wextra -g -I headers
LDLIBS  = -lm
TARGET  = labyrinthGenerator
SRCS    = $(wildcard src/*.c)
OBJS    = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean