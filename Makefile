CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = unn-lab1

all:
	$(CC) $(CFLAGS) -o $(TARGET) main.c menu.c

clean:
	rm -f $(TARGET)