/*
 * Game.h
 *
 *  Created on: 26.06.2016
 *      Author: thore
 */

#ifndef SRC_GAME_H_
#define SRC_GAME_H_
#include <SDL2/SDL.h>

class Game {
public:
	Game();
	virtual ~Game();

	/*
	 * starts the game
	 */
	int start();



private:
	bool isRunning;
	int initialize();
	void handle_input_events();
	void update_game_state();
	void render_current_frame();
	void clean_up();
};

#endif /* SRC_GAME_H_ */
