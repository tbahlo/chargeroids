/*
 * Particle.cpp
 *
 *  Created on: 25.10.2021
 *      Author: thore
 */

#include "Particle.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

#define MASS 0
#define CHARGE 0
#define LIFETIME 0.3

Particle::Particle(
				Vector2D given_position,
				Vector2D given_velocity,
				SDL_Renderer* given_renderer) :
				DrawableObject(given_position, given_velocity, given_renderer)
{
		character_class = 'p';
		mass = MASS;
		charge = CHARGE;
		lifetime_left = LIFETIME;
}

Particle::Particle(
				Vector2D given_position, 
				SDL_Renderer* given_renderer)
				: DrawableObject(given_position, given_renderer)
{
		character_class = 'p';
		mass = MASS;
		charge = CHARGE;
		lifetime_left = LIFETIME;
}

Particle::Particle(SDL_Renderer* given_renderer)
: DrawableObject(given_renderer)
{
		character_class = 'p';
		mass = MASS;
		charge = CHARGE;
		lifetime_left = LIFETIME;
}

Particle::~Particle ()
{
		renderer = NULL;
}

void Particle::draw_myself()
{
	SDL_Rect my_body;
	my_body.x = position.x;
	my_body.y = position.y;
	my_body.w = 3;
	my_body.h = 3;

	double timescaler = lifetime_left/ ((double) LIFETIME);

	SDL_SetRenderDrawColor(renderer,
		(int) (0xEB * timescaler),
		(int) (0x89 * timescaler),
		(int) (0x34 * timescaler),
		0xFF); //eb8934

	SDL_RenderFillRect(renderer, &my_body);
		
}

void Particle::update(float time_passed)
{
		// acceleration:
		//if(force.x != 0 || force.y != 0) {
		//		velocity.x += force.x / mass;
		//		velocity.y += force.y / mass;
		//}

		//position update:
		position.x += velocity.x * time_passed;
		position.y += velocity.y * time_passed;

		lifetime_left -= time_passed;
		if (lifetime_left < 0){
			is_alive = false;
		}
		//printf("[%d][%d] reduced lifetime by (%2.2f) - it is now: (%2.2f)\n", is_alive, this->is_dead(), time_passed, lifetime_left);
}

void Particle::kill()
{
		is_alive = false;
}