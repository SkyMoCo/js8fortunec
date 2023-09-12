# Makefile

CC = gcc # Flag for implicit rules
INCLUDES = -I /usr/local/include/json-c/ -I include
CFLAGS =  -std=c99 -g $(INCLUDES) # Flag for implicit rules. Turn on debug info

HEADERS = $(wildcard include/*.h)

objects = main.o log.o

all: js8fortune js8server
	@echo "Done"

js8fortune: main.o log.o
	gcc -o js8fortune $(objects) -ljson-c

js8server: server.o log.o
	gcc -o js8server server.o log.o -ljson-c

main.o: main.c
log.o: log.c

