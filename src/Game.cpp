/*
 * Game.cpp
 *
 *  Created on: 26.06.2016
 *      Author: thore
 */

#include "Game.h"
#include "SDL2/SDL.h"

Game::Game() {
	isRunning = true;
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}


/*
 * starts the game
 */
int Game::start(){

	initialize();

	while (isRunning){
		handle_input_events();
		update_game_state();
		render_current_frame();
	}

	clean_up();

	return 0;
}

int Game::initialize(){
	// initialisiere SDL engine
	return 0;
}

void Game::handle_input_events(){
}

void Game::update_game_state(){
}

void Game::render_current_frame(){
}

void Game::clean_up(){

}
