/*
 * DrawableObject.cpp
 *
 *  Created on: 05.08.2016
 *      Author: thore
 */

#include "DrawableObject.h"
#include <SDL2/SDL.h>

DrawableObject::DrawableObject(
				Vector2D given_position,
				Vector2D given_velocity,
				SDL_Renderer* given_renderer)
{
		is_alive = true;
		character_class = 'D';
		mass = 100;
		charge = 0;


		position = given_position;
		velocity = given_velocity;

		force = {0, 0};

		renderer = given_renderer;

		printf("created object at (%.0f, %.0f) with speed: (%.2f, %.2f)\n", position.x, position.y, velocity.x, velocity.y);
}

DrawableObject::DrawableObject(
				Vector2D given_position, 
				SDL_Renderer* given_renderer)
{
		is_alive = true;
		character_class = 'D';
		mass = 100;
		charge = 0;

		position = given_position;

		velocity.x = double((rand()%200 - rand()%200)) / 100;
		velocity.y = double((rand()%200 - rand()%200)) / 100;

		force.x = 0;
		force.y = 0;

		renderer = given_renderer;
		printf("created object at (%.0f, %.0f) with speed: (%.2f, %.2f)\n", position.x, position.y, velocity.x, velocity.y);
}

DrawableObject::DrawableObject(SDL_Renderer* given_renderer)
{
		is_alive = true;
		character_class = 'D';
		mass = 100;
		charge = 0;
		position.x = 100.;
		position.y = 100.;
		velocity.x = 0.;
		velocity.y = 0.;
		force.x = 0;
		force.y = 0;


		renderer = given_renderer;
		printf("created std object at (%.0f, %.0f) with speed: (%.2f, %.2f)\n", position.x, position.y, velocity.x, velocity.y);

}

DrawableObject::~DrawableObject ()
{
		renderer = NULL;
}

void DrawableObject::apply_force(Vector2D given_force)
{
}

void DrawableObject::draw_myself()
{
		SDL_Rect my_body;
		my_body.x = position.x;
		my_body.y = position.y;
		my_body.w = 10;
		my_body.h = 10;
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF); //RGBA - Blue
		SDL_RenderFillRect(renderer, &my_body);
		
}

bool DrawableObject::has_child()
{
		return children_objects.size() != 0;
}

void DrawableObject::update(float time_passed)
{
		// acceleration:
		if(force.x != 0 || force.y != 0) {
				velocity.x += force.x / mass;
				velocity.y += force.y / mass;
		}

		//position update:
		position.x += velocity.x * time_passed;
		position.y += velocity.y * time_passed;
}

DrawableObject* DrawableObject::get_child()
{
		if (this->has_child()){
				DrawableObject* object_to_be_returned = children_objects.back();
				children_objects.pop_back();
				return object_to_be_returned;
		}
		else
		{
				return NULL;
		}
}

bool DrawableObject::is_dead()
{
		return !is_alive;
}

void DrawableObject::kill()
{
		is_alive = false;
}

double DrawableObject::get_charge()
{
		return charge;
}

double DrawableObject::get_mass()
{
		return mass;
}

Vector2D DrawableObject::get_pos()
{
		return position;
}

Vector2D DrawableObject::get_velocity()
{
		return velocity;
}

void DrawableObject::set_position(Vector2D pos)
{
		position = pos;
}

void DrawableObject::set_velocity(Vector2D vel){
		velocity = vel;
}

