/*
 * Projectile.cpp
 *
 *  Created on: 14.03.2019
 *      Author: thore
 */

#include "Projectile.h"
#define CHARGE 0
#define MAX_AGE 1


Projectile::Projectile(SDL_Renderer* renderer)
: DrawableObject(renderer)
{
	character_class = 'P';
	mass = rand()%90 + 10;
	charge = CHARGE;
	lifetime_left = MAX_AGE;
}

Projectile::Projectile(Position pos, SDL_Renderer* renderer)
: DrawableObject(pos, renderer)
{
	mass = rand()%90 + 10;
	character_class = 'C';
	charge = CHARGE;
	lifetime_left = MAX_AGE;
}

Projectile::Projectile(Position pos, Velocity vel, SDL_Renderer* renderer)
: DrawableObject(pos, vel, renderer)
{
	character_class = 'C';
	mass = rand()%90 + 10;
	charge = CHARGE;
	lifetime_left = MAX_AGE;
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
		if(force.fx != 0 || force.fy != 0) {
				velocity.vx += force.fx / mass;
				velocity.vy += force.fy / mass;
		}

		//position update:
		position.x += velocity.vx * time_passed;
		position.y += velocity.vy * time_passed;
		lifetime_left -= time_passed;
		if (lifetime_left < 0){
			is_alive = false;
		}
}
void Projectile::draw_myself()
{
		SDL_SetRenderDrawColor(renderer, 0xFF, int(0xFF * charge/5), int(0xFF * charge/5), 0xFF);

		// draw "star" shape
		double radius = sqrt(mass);
		for (double angle = 0; angle <= 360; angle += 360/10)
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

void Projectile::apply_force(Force ext_force)
{
	this->force.fx += ext_force.fx;
	this->force.fy += ext_force.fy;
}

