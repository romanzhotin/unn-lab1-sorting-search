CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = unn-lab1
SRCS = main.c menu.c array_utils.c sorts.c

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)