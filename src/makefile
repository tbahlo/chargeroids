#   $<    is just the first prerequisite 
#   $^    is a list of all the prerequisites of the rule
#   $@    is the target. 

# these are not used yet. out-of-source build will be implemented later. (maybe...)  
SOURCE_DIR    = src
HEADER_DIR    = inc
DEBUG_DIR     = debug
RELEASE_DIR   = bin

CC = g++
CFLAGS = -g -lSDL2 -Wall

all: chargeroids

#sdl_tutorial.cpp: 
#  $(CC) $(CFLAGS) -o sdl_tutorial $(SOURCE_DIR)/$@

chargeroids: main.o Game.o
	$(CC) $(CFLAGS) -o chargeroids main.o Game.o

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -f *.o

#main.o: $(SOURCE_DIR)/main.cpp $(SOURCE_DIR)/Game.h
#	$(CC) $(CFLAGS) -c $(SOURCE_DIR)/main.cpp -o $(DEBUG_DIR)/main.o

#Game.o: $(SOURCE_DIR)/Game.h $(SOURCE_DIR)/Game.cpp
#	$(CC) $(CFLAGS) -o $(DEBUG_DIR)/Game.o $(SOURCE_DIR)/Game.h $(SOURCE_DIR)/Game.cpp
