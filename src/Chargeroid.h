/*
 * Chargeroid.h
 *
 *  Created on: 12.08.2016
 *      Author: thore
 */

#ifndef SRC_CHARGEROID_H_
#define SRC_CHARGEROID_H_

#include "DrawableObject.h"

class Chargeroid : public DrawableObject
{
public:
	Chargeroid(SDL_Renderer* renderer);
	Chargeroid(double x, double y, SDL_Renderer* renderer);
	Chargeroid(double x, double y, double velocity_x, double velocity_y, SDL_Renderer* renderer);

	virtual
	~Chargeroid();

	double calculate_distance_to(Chargeroid* opponent);

private:
	int mass;
	int charge;
};

#endif /* SRC_CHARGEROID_H_ */
