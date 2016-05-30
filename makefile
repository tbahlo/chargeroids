SOURCE_DIR    = src
HEADER_DIR    = inc
DEBUG_DIR     = debug
RELEASE_DIR   = bin

CC = gcc
CFLAGS = -Wall -g -I/usr/include/SDL2

all: sdl_tutorial.cpp

sdl_tutorial.cpp: 
	$(CC) $(CFLAGS) -o sdl_tutorial $(SOURCE_DIR)/$@
