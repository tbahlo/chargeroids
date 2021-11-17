/*
 * Projectile.cpp
 *
 *  Created on: 14.03.2019
 *      Author: thore
 */

#include "Projectile.h"
#define CHARGE 0
#define MAX_AGE_IN_S 1
#define PROJECTILE_MASS 50


Projectile::Projectile(SDL_Renderer* renderer)
: DrawableObject(renderer)
{
	character_class = 'P';
	mass = PROJECTILE_MASS;
	charge = CHARGE;
	lifetime_left = MAX_AGE_IN_S;
}

Projectile::Projectile(Vector2D pos, SDL_Renderer* renderer)
: DrawableObject(pos, renderer)
{
	mass = PROJECTILE_MASS;
	character_class = 'P';
	charge = CHARGE;
	lifetime_left = MAX_AGE_IN_S;
}

Projectile::Projectile(Vector2D pos, Vector2D vel, SDL_Renderer* renderer)
: DrawableObject(pos, vel, renderer)
{
	character_class = 'P';
	mass = PROJECTILE_MASS;
	charge = CHARGE;
	lifetime_left = MAX_AGE_IN_S;
}

Projectile::~Projectile()
{
	// TODO Auto-generated destructor stub
}

void Projectile::kill()
{
		is_alive = false;
}

void Projectile::update(float time_passed){
		// acceleration:
		if(force.x != 0 || force.y != 0) {
				velocity.x += force.x / mass;
				velocity.y += force.y / mass;
		}

		//position update:
		position.x += velocity.x * time_passed;
		position.y += velocity.y * time_passed;
		lifetime_left -= time_passed;
		if (lifetime_left < 0){
			is_alive = false;
		}
}
void Projectile::draw_myself()
{
		SDL_SetRenderDrawColor(renderer, 0x99, 0x99, 0xFF, 0xFF);

		// draw "star" shape
		double radius = 0.5 * sqrt(mass);
		double old_angle = 0;
		for (double angle = 0; angle <= 360; angle += 360/10)
		{
				SDL_RenderDrawLine(renderer,
								position.x,
								position.y,
								position.x + radius * cos(angle / 360. * 2 * 3.14159),
								position.y + radius * sin(angle / 360. * 2 * 3.14159));

				SDL_RenderDrawLine(renderer,
								position.x,
								position.y,
								position.x + radius * cos(angle / 360. * 2 * 3.14159),
								position.y + radius * sin(angle / 360. * 2 * 3.14159));
				SDL_RenderDrawLine(renderer,
								position.x + radius * cos(angle / 360. * 2 * 3.14159),
								position.y + radius * sin(angle / 360. * 2 * 3.14159),
								position.x + radius * cos(old_angle / 360. * 2 * 3.14159),
								position.y + radius * sin(old_angle / 360. * 2 * 3.14159));
				old_angle = angle;
		}


		SDL_SetRenderDrawColor(renderer, 0x0, 0xFF, 0x0, 0x0);

		// draw velocity vector
		//SDL_RenderDrawLine(renderer, 
		//				position.x, 
		//				position.y,
		//				position.x + velocity.x, 
		//				position.y + velocity.y);
}

void Projectile::apply_force(Vector2D ext_force)
{
	this->force.x += ext_force.x;
	this->force.y += ext_force.y;
}

