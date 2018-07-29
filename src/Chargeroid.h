/*
 * Chargeroid.h
 *
 *  Created on: 12.08.2016
 *      Author: thore
 */

#ifndef SRC_CHARGEROID_H_
#define SRC_CHARGEROID_H_

#include "types.h"
#include "DrawableObject.h"

class Chargeroid : public DrawableObject
{
public:
	Chargeroid(SDL_Renderer* renderer);
	Chargeroid(Position pos, SDL_Renderer* renderer);
	Chargeroid(Position pos, Velocity vel, SDL_Renderer* renderer);

	virtual
	~Chargeroid();

	void kill() override;
	void draw_myself() override;
	void apply_force(Force force) override;


private:
	double calculate_distance_to(Chargeroid* opponent);
};

#endif /* SRC_CHARGEROID_H_ */
