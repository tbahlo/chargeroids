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
#include "Particle.h"
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

Player::Player(Vector2D pos, SDL_Renderer* renderer)
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

Player::Player(Vector2D pos, Vector2D vel, SDL_Renderer* renderer)
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

void Player::shoot(){
		
		double radius = sqrt(mass);
		double projectile_speed = 1000;
		Vector2D proj_pos;
		proj_pos.x = position.x + radius * cos(orientation_angle /360. * 2 * 3.14159);
		proj_pos.y = position.y + radius * sin(orientation_angle /360. * 2 * 3.14159);

		Vector2D proj_speed;
		proj_speed.x = velocity.x + projectile_speed * cos(orientation_angle /360. * 2 * 3.14159);
		proj_speed.y = velocity.y + projectile_speed * sin(orientation_angle /360. * 2 * 3.14159);

		Projectile* new_projectile = new Projectile(proj_pos, proj_speed, renderer);
		children_objects.push_back(new_projectile);
}

void Player::update(float time_passed)
{
		// rotation
		orientation_angle += rotation_direction * rotation_speed * time_passed;
		
		//position update:
		position.x += velocity.x * time_passed;
		position.y += velocity.y * time_passed;

		// acceleration:
		if(is_boosting)
		{
				velocity.x += acceleration * time_passed * cos(orientation_angle /360. * 2 * 3.14159);
				velocity.y += acceleration * time_passed * sin(orientation_angle /360. * 2 * 3.14159);

				// create particle effects:
				double radius = 3;
				double projectile_speed = 300;
				double emission_angle_spread = 30;
				double emission_angle = orientation_angle + ((rand() % (int)(emission_angle_spread + 1)) - (emission_angle_spread / 2 + 1));
				Vector2D proj_pos;
				proj_pos.x = position.x - radius * cos(orientation_angle / 360. * 2 * 3.14159);
				proj_pos.y = position.y - radius * sin(orientation_angle / 360. * 2 * 3.14159);

				Vector2D proj_speed;
				proj_speed.x = velocity.x - projectile_speed * cos(emission_angle /360. * 2 * 3.14159);
				proj_speed.y = velocity.y - projectile_speed * sin(emission_angle /360. * 2 * 3.14159);

				Particle* new_particle = new Particle(proj_pos, proj_speed, renderer);
				children_objects.push_back(new_particle);
		}
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
		//SDL_RenderDrawLine(renderer, 
		//				position.x, 
		//				position.y,
		//				position.x + velocity.x,
		//				position.y + velocity.y);
		SDL_Rect my_body;
		my_body.x = position.x - radius;
		my_body.y = position.y - radius;
		my_body.w = 2;
		my_body.h = 2;

		// draw center mark
		SDL_SetRenderDrawColor(renderer,
			(int) (0xAA),
			(int) (0xAA),
			(int) (0xAA),
			0xFF); //eb8934
		SDL_RenderFillRect(renderer, &my_body);

		// draw bounding box
		my_body.w = 2 * radius;
		my_body.h = 2 * radius;
		SDL_RenderDrawRect(renderer, &my_body);

		// draw marking line to origin
		SDL_RenderDrawLine(renderer, position.x, position.y, 0, 0);

}

