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
	void apply_x_force(double x_force) override;
	void apply_y_force(double y_force) override;


private:
	double mass;
	double charge;
	double calculate_distance_to(Chargeroid* opponent);
};

#endif /* SRC_CHARGEROID_H_ */
