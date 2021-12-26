/*
 * Chargeroid.cpp
 *
 *  Created on: 12.08.2016
 *      Author: thore
 */

#include "Chargeroid.h"
#define CHARGE 100


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
	if (mass > 25) // only Chargeroids that are "big enough" shall spawn fragments
	{
		double mass_difference = rand() % int(mass / 4); // fragments shall not split evenly but with a mass variation of 25%
		double first_fragments_mass =  mass / 2 + mass_difference;
		double second_fragments_mass = mass / 2 - mass_difference;
		
		// calculate random positionin which fragments are emitted:
		double fragment_emission_angle_in_deg = rand() % 360;
		double velocity_gain = 200; 

		Vector2D first_position;
		first_position.x = position.x + 4 * sqrt(first_fragments_mass) * cos(fragment_emission_angle_in_deg / 360. * 3.14159);
		first_position.y = position.y + 4 * sqrt(first_fragments_mass) * sin(fragment_emission_angle_in_deg / 360. * 3.14159);

		Vector2D second_position;
		second_position.x = position.x - 4 * cos(fragment_emission_angle_in_deg / 360. * 3.14159);
		second_position.y = position.y - 4 * sin(fragment_emission_angle_in_deg / 360. * 3.14159);

		//TODO implement momentum conservation correctly 
		Vector2D first_speed =  velocity;
		first_speed.x += velocity_gain * cos(fragment_emission_angle_in_deg / 360. * 3.14159);
		first_speed.y += velocity_gain * sin(fragment_emission_angle_in_deg / 360. * 3.14159);

		Vector2D second_speed = velocity;
		second_speed.x -= velocity_gain * cos(fragment_emission_angle_in_deg / 360. * 3.14159);
		second_speed.y -= velocity_gain * sin(fragment_emission_angle_in_deg / 360. * 3.14159);

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

		// draw velocity vector for debugging purposes
		//SDL_RenderDrawLine(renderer, 
		//				position.x, 
		//				position.y,
		//				position.x + velocity.x, 
		//				position.y + velocity.y);
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
