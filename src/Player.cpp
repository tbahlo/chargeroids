/*
 * Player.cpp
 *
 *  Created on: 12.08.2016
 *      Author: thore
 */

#include "Player.h"
#include <iostream>

Player::Player(SDL_Renderer* renderer)
: DrawableObject(renderer)
{
	character_class = 'P';
	mass = 100;
	charge = 1;
	acceleration = 0.1;
	rotation_speed = 10;
	orientation_angle = 45; 
}

Player::Player(Position pos, SDL_Renderer* renderer)
: DrawableObject(pos, renderer)
{
	mass = 100;
	character_class = 'P';
	charge = 1;
	acceleration = 0.1;
	rotation_speed = 10;
	orientation_angle = 45; 
}

Player::Player(Position pos, Velocity vel, SDL_Renderer* renderer)
: DrawableObject(pos, vel, renderer)
{
	character_class = 'P';
	mass = 100;
	charge = 1;
	acceleration = 0.1;
	rotation_speed = 10;
	orientation_angle = 45; 
}

Player::~Player()
{
	// TODO Auto-generated destructor stub
}

void Player::kill()
{
	is_alive = false;
}

void Player::boost()
{
	velocity.vx += acceleration * cos(orientation_angle /360. * 2 * 3.14159);
	velocity.vy += acceleration * sin(orientation_angle /360. * 2 * 3.14159);
}

void Player::draw_myself()
{
		SDL_SetRenderDrawColor(renderer, 0x0, 0xFF, 0x0, 0x0);

		// draw triangular shape
		double radius = sqrt(mass);
		double tip_point_x = position.x + radius * cos(orientation_angle /360. * 2 * 3.14159);
		double tip_point_y = position.y + radius * sin(orientation_angle /360. * 2 * 3.14159);
		double right_tail_point_x = position.x + radius * cos((orientation_angle+120) /360. * 2 * 3.14159);
		double right_tail_point_y = position.y + radius * sin((orientation_angle+120) /360. * 2 * 3.14159);
		double left_tail_point_x = position.x + radius * cos((orientation_angle-120) /360. * 2 * 3.14159);
		double left_tail_point_y = position.y + radius * sin((orientation_angle-120) /360. * 2 * 3.14159);

		// top => right
		SDL_RenderDrawLine(renderer,
						tip_point_x,
						tip_point_y,
						right_tail_point_x,
						right_tail_point_y);		
		
		// top => left
		SDL_RenderDrawLine(renderer,
						tip_point_x,
						tip_point_y,
						left_tail_point_x,
						left_tail_point_y);		

		// center => right
		SDL_RenderDrawLine(renderer,
						position.x,
						position.y,
						right_tail_point_x,
						right_tail_point_y);		
		
		// center => right
		SDL_RenderDrawLine(renderer,
						position.x,
						position.y,
						left_tail_point_x,
						left_tail_point_y);		
		
		// draw velocity vector
		SDL_RenderDrawLine(renderer, 
						position.x, 
						position.y,
						position.x + 100 * velocity.vx, 
						position.y + 100 * velocity.vy);

}

