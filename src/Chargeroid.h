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

	void kill() override;
	void draw_myself() override;
	double calculate_distance_to(Chargeroid* opponent);

private:
	double mass;
	double charge;
};

#endif /* SRC_CHARGEROID_H_ */
