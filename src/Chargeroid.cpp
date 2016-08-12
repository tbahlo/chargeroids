/*
 * Chargeroid.cpp
 *
 *  Created on: 12.08.2016
 *      Author: thore
 */

#include "Chargeroid.h"

Chargeroid::Chargeroid(SDL_Renderer* renderer)
: DrawableObject(renderer)
{
	mass = rand()%90 + 10;
	charge = 100;
}

Chargeroid::Chargeroid(double x, double y, SDL_Renderer* renderer)
: DrawableObject(x, y, renderer)
{
	mass = rand()%90 + 10;
	charge = 100;
}

Chargeroid::Chargeroid(double x, double y, double velocity_x, double velocity_y, SDL_Renderer* renderer)
: DrawableObject(x, y, velocity_x, velocity_y, renderer)
{
	mass = rand()%90 + 10;
	charge = 100;
}


Chargeroid::~Chargeroid()
{
	// TODO Auto-generated destructor stub
}


double Chargeroid::calculate_distance_to(Chargeroid* opponent)
{
	double result = 0;
	double others_x = opponent->get_x();
	double others_y = opponent->get_y();
	result = sqrt( pow(others_x - get_x(), 2) + pow(others_y - get_y(), 2));
	return result;
}
