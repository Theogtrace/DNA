# A simple Makefile
# # Saad Arshad 00857432
# # CS 262, Lab Section 208
# # Lab 7

CC = gcc
CFLAGS = -g -Wall -pedantic-errors

TARGET1 = project2

all: $(TARGET1)

$(TARGET1):
	$(CC) $(CFLAGS) -o $(TARGET1) $(TARGET1).c

clean:
	rm $(TARGET1)
