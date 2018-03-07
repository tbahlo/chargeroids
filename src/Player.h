/*
 * Player.h
 *
 *  Created on: 12.08.2016
 *      Author: thore
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "DrawableObject.h"

class Player : public DrawableObject
{
public:
	Player(SDL_Renderer* renderer);
	Player(double x, double y, SDL_Renderer* renderer);
	Player(double x, double y, double velocity_x, double velocity_y, SDL_Renderer* renderer);

	virtual
	~Player();

	void kill() override;
	void draw_myself() override;

	double acceleration;
	double rotation_speed;
};

#endif /* SRC_PLAYER_H_ */
