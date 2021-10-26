#include "Game.h"
#include <time.h>

/*
 * main.cpp
 *
 *  Created on: 17.06.2016
 *      Author: thore
 */
int main(int argc, char* argv[]){
	/* TODO: interpret console line arguments */
	(void) argc, argv;


	/* seed the random generator */
	srand(time(0));

	/* create a Game class instance and run it */
	Game current_game;
	return current_game.start();
} 


