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

Chargeroid::Chargeroid(Vector2D pos, SDL_Renderer* renderer)
: DrawableObject(pos, renderer)
{
	mass = rand()%90 + 10;
	character_class = 'C';
	charge = CHARGE;
}

Chargeroid::Chargeroid(Vector2D pos, Vector2D vel, SDL_Renderer* renderer)
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
		double mass_difference = rand() % int(mass / 4);
		double first_fragments_mass =  mass / 2 + mass_difference;
		double second_fragments_mass = mass / 2 - mass_difference;
		
		Vector2D first_position;
		first_position.x = position.x + 2 * sqrt(first_fragments_mass);
		first_position.y = position.y + 2 * sqrt(first_fragments_mass);

		Vector2D second_position;
		second_position.x = position.x - 2 *  sqrt(second_fragments_mass);
		second_position.y = position.y - 2 *  sqrt(second_fragments_mass);

		//TODO implement momentum conservation 
		Vector2D first_speed = velocity;
		Vector2D second_speed = velocity;

		Chargeroid* first_fragment = new Chargeroid(first_position, first_speed, renderer);
		first_fragment->mass = first_fragments_mass;
		first_fragment->charge = charge/2;
		children_objects.push_back(first_fragment);

		Chargeroid* second_fragment = new Chargeroid(second_position, second_speed, renderer);
		second_fragment->mass = second_fragments_mass;
		second_fragment->charge = charge/2;
		children_objects.push_back(second_fragment);
		printf("objects pushed in child list\n");
	}
	is_alive = false;
}

void Chargeroid::draw_myself()
{
		SDL_SetRenderDrawColor(renderer, 0xFF, int(0xFF * charge/5), int(0xFF * charge/5), 0xFF);

		// draw "star" shape
		double radius = 2* sqrt(mass);
		double old_angle = 0;
		const double pi = 3.14159;
		for (double angle = 0; angle <= 360; angle += 360/20)
		{
				SDL_RenderDrawLine(renderer, 
								position.x, 
								position.y,
								position.x + radius * cos(angle / 360. * 2 * pi),
								position.y + radius * sin(angle / 360. * 2 * pi));
				SDL_RenderDrawLine(renderer, 
								position.x + radius * cos(angle / 360. * 2 * pi),
								position.y + radius * sin(angle / 360. * 2 * pi),
								position.x + radius * cos(old_angle / 360. * 2 * pi),
								position.y + radius * sin(old_angle / 360. * 2 * pi));
				old_angle = angle;
		}

		// draw velocity vector
		SDL_RenderDrawLine(renderer, 
						position.x, 
						position.y,
						position.x + velocity.x, 
						position.y + velocity.y);


}

void Chargeroid::apply_force(Vector2D ext_force)
{
	this->force.x += ext_force.x;
	this->force.y += ext_force.y;
}

double Chargeroid::calculate_distance_to(Chargeroid* opponent)
{
	double result = 0;
	double others_x = opponent->get_pos().x;
	double others_y = opponent->get_pos().y;
	result = sqrt( pow(others_x - position.x, 2) + pow(others_y - position.y, 2));
	return result;
}
