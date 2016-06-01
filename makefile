SOURCE_DIR    = src
HEADER_DIR    = inc
DEBUG_DIR     = debug
RELEASE_DIR   = bin

CC = g++
CFLAGS = -g -lSDL2 -Wall

all: sdl_tutorial.cpp

sdl_tutorial.cpp: 
	$(CC) $(CFLAGS) -o sdl_tutorial $(SOURCE_DIR)/$@
