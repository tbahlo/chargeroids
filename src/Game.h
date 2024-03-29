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
#include <ctime>
#include <stdint.h>
#include "DrawableObject.h"
#include "Chargeroid.h"
#include "Player.h"
#include "Particle.h"
#include "Vector2D.h"

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
				bool initialize();
				SDL_Window* game_window;
				SDL_Surface* screen_surface;
				SDL_Surface* testbild;
				SDL_Event input_event;
				SDL_Renderer* renderer;
				list<DrawableObject*> drawable_objects;
				Player* active_player;


				void handle_input_events();

				float get_current_time_in_s();
				void update_game_state(float time_passed);

				void let_all_objects_interact();
				void spawn_new_objects();
				void remove_dead_objects();
				void apply_friction();
				void update_positions(float time_passed);
				void check_for_border_crossings();

				void render_current_frame();
				uint32_t get_amount_of_alive_chargeroids();
				void initialize_level(uint32_t level);
				void clean_up();




};

#endif /* SRC_GAME_H_ */
