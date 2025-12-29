CC=gcc
CFLAGS=-Wall -Wextra -g
TARGET=mini-shell

all:
	$(CC) $(CFLAGS) src/main.c -o $(TARGET)

clean:
	rm -f $(TARGET)
