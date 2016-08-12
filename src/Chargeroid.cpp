/*
 * Chargeroid.cpp
 *
 *  Created on: 12.08.2016
 *      Author: thore
 */

#include "Chargeroid.h"

Chargeroid::Chargeroid(SDL_Renderer* renderer) : DrawableObject(renderer)
{
	mass = rand()%90 + 10;
	charge = 100;
}

Chargeroid::Chargeroid(double x, double y, SDL_Renderer* renderer) : DrawableObject(x, y, renderer)
{
	mass = rand()%90 + 10;
	charge = 100;
}

Chargeroid::~Chargeroid()
{
	// TODO Auto-generated destructor stub
}

double calculate_distance_to(Chargeroid opponent)
{
	return 100; //TODO: implement distance calculation
}
