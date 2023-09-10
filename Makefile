# Makefile

CC = gcc # Flag for implicit rules
INCLUDES = -I /usr/local/include/json-c/ -I include
CFLAGS =  -std=c99 -g $(INCLUDES) # Flag for implicit rules. Turn on debug info

HEADERS = $(wildcard include/*.h)

objects = main.o log.o

js8fortune: main.o log.o
	gcc -o js8fortune $(objects) 


main.o: main.c
log.o: log.c

