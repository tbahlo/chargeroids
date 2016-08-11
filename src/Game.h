/*
 * Game.h
 *
 *  Created on: 26.06.2016
 *      Author: thore
 */

#ifndef SRC_GAME_H_
#define SRC_GAME_H_
#include <SDL2/SDL.h>
#include <list>
#include "DrawableObject.h"
using namespace std;


class Game {
public:
	Game();
	virtual ~Game();

	/*
	 * starts the game
	 */
	int start();

private:
	bool is_Running;
	int initialize();
	SDL_Window* game_window;
	SDL_Surface* screen_surface;
	SDL_Surface* testbild;
	SDL_Event input_event;
	SDL_Renderer* renderer;
	list<DrawableObject> drawable_objects;


	void handle_input_events();

	void update_game_state();
		void let_all_objects_interact();
		void spawn_new_objects();
		void remove_dead_objects();
		void apply_friction()	;
		void update_positions();
		void check_for_border_crossings();

	void render_current_frame();

	void clean_up();




};

#endif /* SRC_GAME_H_ */
