/*
 * Player.h
 *
 *  Created on: 12.08.2016
 *      Author: thore
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "types.h"
#include "DrawableObject.h"

class Player : public DrawableObject
{
public:
	Player(SDL_Renderer* renderer);
	Player(Position pos, SDL_Renderer* renderer);
	Player(Position pos, Velocity vel, SDL_Renderer* renderer);

	virtual
	~Player();

	void kill() override;
	void draw_myself() override;

	double acceleration;
	double rotation_speed;
};

#endif /* SRC_PLAYER_H_ */
