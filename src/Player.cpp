/*
 * Player.cpp
 *
 *  Created on: 12.08.2016
 *      Author: thore
 */

#include "Player.h"

Player::Player(SDL_Renderer* renderer)
: DrawableObject(renderer)
{
	character_class = 'P';
	mass = 100;
	charge = 100;
	acceleration = 0.1;
	rotation_speed = 10;
}

Player::Player(Position pos, SDL_Renderer* renderer)
: DrawableObject(pos, renderer)
{
	mass = 100;
	character_class = 'P';
	charge = 100;
	acceleration = 0.1;
	rotation_speed = 10;
}

Player::Player(Position pos, Velocity vel, SDL_Renderer* renderer)
: DrawableObject(pos, vel, renderer)
{
	character_class = 'P';
	mass = 100;
	charge = 100;
	acceleration = 0.1;
	rotation_speed = 10;
}

Player::~Player()
{
	// TODO Auto-generated destructor stub
}

void Player::kill()
{
	is_alive = false;
}

void Player::draw_myself()
{
		SDL_SetRenderDrawColor(renderer, 0x0, 0xFF, 0x0, 0x0);

		// draw "star" shape
		double radius = sqrt(mass);
		for (double angle = 0; angle < 360; angle += 360/20)
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
						position.x + 100 * velocity.vx, 
						position.y + 100 * velocity.vy);

}

