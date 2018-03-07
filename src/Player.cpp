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
	charge = 0;
	acceleration = 0.1;
	rotation_speed = 10;
}

Player::Player(double x, double y, SDL_Renderer* renderer)
: DrawableObject(x, y, renderer)
{
	mass = 100;
	character_class = 'P';
	charge = 0;
	acceleration = 0.1;
	rotation_speed = 10;
}

Player::Player(double x, double y, double velocity_x, double velocity_y, SDL_Renderer* renderer)
: DrawableObject(x, y, velocity_x, velocity_y, renderer)
{
	character_class = 'P';
	mass = 100;
	charge = 0;
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
	SDL_Rect my_body;
	my_body.x = x_position;
	my_body.y = y_position;
	my_body.w = sqrt(mass);
	my_body.h = sqrt(mass);
	SDL_SetRenderDrawColor(renderer, 0x0, 0xFF, 0x0, 0x0);
	SDL_RenderFillRect(renderer, &my_body);
}

