/*
 * Chargeroid.cpp
 *
 *  Created on: 12.08.2016
 *      Author: thore
 */

#include "Chargeroid.h"
#define CHARGE 10


Chargeroid::Chargeroid(SDL_Renderer* renderer)
: DrawableObject(renderer)
{
	character_class = 'C';
	mass = rand()%90 + 10;
	charge = CHARGE;
}

Chargeroid::Chargeroid(Position pos, SDL_Renderer* renderer)
: DrawableObject(pos, renderer)
{
	mass = rand()%90 + 10;
	character_class = 'C';
	charge = CHARGE;
}

Chargeroid::Chargeroid(Position pos, Velocity vel, SDL_Renderer* renderer)
: DrawableObject(pos, vel, renderer)
{
	character_class = 'C';
	mass = rand()%90 + 10;
	charge = CHARGE;
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
		//WARNING: FRAGMENTS ARE ON TOP OF EACH OTHER => SHIFT THEM A LITTLE!
		Chargeroid* first_fragment = new Chargeroid(position, renderer);
		Chargeroid* second_fragment = new Chargeroid(position, renderer);

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
		SDL_SetRenderDrawColor(renderer, 0xFF, int(0xFF * charge/5), int(0xFF * charge/5), 0xFF);

		// draw "star" shape
		double radius = sqrt(mass);
		for (double angle = 0; angle < 360; angle += 360/10)
		{
				SDL_RenderDrawLine(renderer, 
								position.x, 
								position.y,
								position.x + radius * cos(angle / 360. * 2 * 3.14159),
								position.y + radius * sin(angle / 360. * 2 * 3.14159));
		}

		// draw velocity vector
		SDL_RenderDrawLine(renderer, 
						position.x, 
						position.y,
						position.x + velocity.vx, 
						position.y + velocity.vy);


}

void Chargeroid::apply_force(Force ext_force)
{
	this->force.fx += ext_force.fx;
	this->force.fy += ext_force.fy;
}

double Chargeroid::calculate_distance_to(Chargeroid* opponent)
{
	double result = 0;
	double others_x = opponent->get_pos().x;
	double others_y = opponent->get_pos().y;
	result = sqrt( pow(others_x - position.x, 2) + pow(others_y - position.y, 2));
	return result;
}
