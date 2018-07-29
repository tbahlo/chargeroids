#   $<    is just the first prerequisite 
#   $^    is a list of all the prerequisites of the rule
#   $@    is the target. 

# these are not used yet. out-of-source build will be implemented later. (maybe...)  
SOURCE_DIR    = src
HEADER_DIR    = inc
DEBUG_DIR     = debug
RELEASE_DIR   = bin

CC = g++
CFLAGS = -std=gnu++11 -g -lSDL2 -Wall


all: chargeroids


chargeroids: main.o Game.o DrawableObject.o Chargeroid.o Player.o types.h
	$(CC) -o chargeroids $^ $(CFLAGS)

# create object files from every cpp file you find:
%.o: %.cpp %.h
	$(CC) -c -o $@ $< $(CFLAGS)
	
# clean up - delete all earlier compiled files
clean:
	rm -f *.o
 
run: chargeroids
	./chargeroids
