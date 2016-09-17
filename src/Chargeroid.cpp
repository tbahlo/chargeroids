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
	character_class = 'C';
	mass = rand()%90 + 10;
	charge = 100;
}

Chargeroid::Chargeroid(double x, double y, SDL_Renderer* renderer)
: DrawableObject(x, y, renderer)
{
	mass = rand()%90 + 10;
	character_class = 'C';
	charge = 100;
}

Chargeroid::Chargeroid(double x, double y, double velocity_x, double velocity_y, SDL_Renderer* renderer)
: DrawableObject(x, y, velocity_x, velocity_y, renderer)
{
	character_class = 'C';
	mass = rand()%90 + 10;
	charge = 100;
}


Chargeroid::~Chargeroid()
{
	// TODO Auto-generated destructor stub
}

void Chargeroid::kill()
{
	Chargeroid first_fragment = Chargeroid(x_position, y_position, x_velocity+50, y_velocity+50, renderer);
	Chargeroid second_fragment = Chargeroid(x_position, y_position, x_velocity-50, y_velocity-50, renderer);
	children_objects.push_back(first_fragment);
	children_objects.push_back(second_fragment);
}

void Chargeroid::draw_myself()
{
	SDL_Rect my_body;
	my_body.x = x_position;
	my_body.y = y_position;
	my_body.w = 10;
	my_body.h = 10;
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &my_body);

}

double Chargeroid::calculate_distance_to(Chargeroid* opponent)
{
	double result = 0;
	double others_x = opponent->get_x();
	double others_y = opponent->get_y();
	result = sqrt( pow(others_x - get_x(), 2) + pow(others_y - get_y(), 2));
	return result;
}
