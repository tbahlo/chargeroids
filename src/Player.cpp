/*
 * Player.cpp
 *
 *  Created on: 12.08.2016
 *      Author: thore
 */

#define ROT_SPEED 360		// degree per second
#define ACCEL 500 			// pixel per second
#define MASS 100


#include "Player.h"
#include <iostream>

Player::Player(SDL_Renderer* renderer)
		: DrawableObject(renderer)
{
		character_class = 'P';
		mass = MASS;
		charge = 1;
		acceleration = ACCEL;
		rotation_speed = ROT_SPEED;
		orientation_angle = 45;
		is_boosting = false;
		rotation_direction = 0;   
}

Player::Player(Position pos, SDL_Renderer* renderer)
		: DrawableObject(pos, renderer)
{
		mass = MASS;
		character_class = 'P';
		charge = 1;
		acceleration = ACCEL;
		rotation_speed = ROT_SPEED;
		orientation_angle = 45; 
		is_boosting = false;
		rotation_direction = 0;   
}

Player::Player(Position pos, Velocity vel, SDL_Renderer* renderer)
		: DrawableObject(pos, vel, renderer)
{
		character_class = 'P';
		mass = MASS;
		charge = 1;
		acceleration = ACCEL;
		rotation_speed = ROT_SPEED;
		orientation_angle = 45; 
		is_boosting = false;
		rotation_direction = 0;   
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
		is_boosting = true;
}

void Player::rotate(int direction)
{
		rotation_direction = direction;
}

void Player::stop()
{
		is_boosting = false; 
}

void Player::update(float time_passed)
{
		// acceleration:
		if(is_boosting) {
				velocity.vx += acceleration * time_passed * cos(orientation_angle /360. * 2 * 3.14159);
				velocity.vy += acceleration * time_passed * sin(orientation_angle /360. * 2 * 3.14159);
		}

		// rotation
		orientation_angle += rotation_direction * rotation_speed * time_passed;
		
		//position update:
		position.x += velocity.vx * time_passed;
		position.y += velocity.vy * time_passed;
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
						position.x + velocity.vx, 
						position.y + velocity.vy);

}

