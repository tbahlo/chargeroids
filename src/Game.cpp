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
	game_window = NULL;
	screen_surface = NULL;
	testbild = NULL;
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}


/*
 * starts the game
 */
int Game::start(){

	if (!initialize()){
		printf("Could not initialize => exit \n");
	}
	else{

		while (isRunning){
			handle_input_events();
			update_game_state();
			render_current_frame();
			SDL_Delay(2000);
			isRunning = false;
		}

		clean_up();

		return 0;
	}
	return 1;
}

int Game::initialize(){
	// initialisiere SDL (gfx engine):
	bool success = false;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not be initialized! SDL_Error: %s\n ", SDL_GetError());
	}
	else {
		// create a Window:
		game_window = SDL_CreateWindow(
				"chargeroids v0.0",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				500,
				500,
				SDL_WINDOW_SHOWN);
		if (game_window == NULL) {
			printf("Window could not be created! SDL_Error: %s,\n", SDL_GetError());
		}
		else {
			// create Screen Surface (TODO: check for failing) :
			screen_surface = SDL_GetWindowSurface(game_window);

			// load image:
			testbild = SDL_LoadBMP("/home/thore/Dokumente/chargeroids/src/testbild.bmp");
			if(testbild == NULL){
				printf("Image could not be loaded! SDL_Error: %s\n", SDL_GetError());
			}
			success = true;
		}
	}

	return success;
}

void Game::handle_input_events(){
}

void Game::update_game_state(){
}

void Game::render_current_frame(){
	SDL_BlitSurface(testbild, NULL, screen_surface, NULL );
	SDL_UpdateWindowSurface(game_window);
}

void Game::clean_up(){
	// deallocate surface
	SDL_FreeSurface(screen_surface);
	screen_surface = NULL;

	// Destroy the window
	SDL_DestroyWindow(game_window);
	game_window = NULL;

	SDL_Quit();
}
