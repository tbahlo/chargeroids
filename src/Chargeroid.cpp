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
	if (mass > 25)
	{
		//TODO implement momentum conservation
		Chargeroid* first_fragment = new Chargeroid(x_position, y_position, renderer);
		Chargeroid* second_fragment = new Chargeroid(x_position, y_position, renderer);

		double mass_difference = rand() % int(mass / 2);

		double first_fragments_mass =  mass / 2 + mass_difference;
		first_fragment->mass = first_fragments_mass;

		double second_fragments_mass = mass / 2 - mass_difference;
		second_fragment->mass = second_fragments_mass;

		first_fragment->charge = charge/2;
		second_fragment->charge = charge/2;

		children_objects.push_back(first_fragment);
		children_objects.push_back(second_fragment);
		printf("objects pushed in child list\n");
	}
	is_alive = false;
}

void Chargeroid::draw_myself()
{
	SDL_Rect my_body;
	my_body.x = x_position;
	my_body.y = y_position;
	my_body.w = sqrt(mass);
	my_body.h = sqrt(mass);
	SDL_SetRenderDrawColor(renderer, 0xFF, int(0xFF * charge/100), int(0xFF * charge/100), 0xFF);
	SDL_RenderFillRect(renderer, &my_body);

}

void Chargeroid::apply_x_force(double x_force)
{
	this->x_force += x_force;
}

void Chargeroid::apply_y_force(double y_force)
{
	this->y_force += y_force;
}

double Chargeroid::calculate_distance_to(Chargeroid* opponent)
{
	double result = 0;
	double others_x = opponent->get_x();
	double others_y = opponent->get_y();
	result = sqrt( pow(others_x - get_x(), 2) + pow(others_y - get_y(), 2));
	return result;
}
