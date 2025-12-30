CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRC = src/main.c \
      src/parser.c \
      src/builtins.c \
      src/executor.c \
      src/signals.c \
      src/pipe.c

TARGET = mini-shell

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
