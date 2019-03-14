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
	void update(float time_passed) override;
	void boost();
	void stop();
	void rotate(int direction);

	bool is_boosting;
	int rotation_direction;
	double acceleration;
	double rotation_speed;
	double orientation_angle;
};

#endif /* SRC_PLAYER_H_ */
