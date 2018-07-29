/*
 * DrawableObject.cpp
 *
 *  Created on: 05.08.2016
 *      Author: thore
 */

#include "DrawableObject.h"
#include <SDL2/SDL.h>

DrawableObject::DrawableObject(
				Position given_position,
				Velocity given_velocity,
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

		printf("created object at (%.0f, %.0f) with speed: (%.2f, %.2f)\n", position.x, position.y, velocity.vx, velocity.vy);
}

DrawableObject::DrawableObject(
				Position given_position, 
				SDL_Renderer* given_renderer)
{
		is_alive = true;
		character_class = 'D';
		mass = 100;
		charge = 0;

		position = given_position;

		velocity.vx = double((rand()%200 - rand()%200)) / 100;
		velocity.vy = double((rand()%200 - rand()%200)) / 100;

		force.fx = 0;
		force.fy = 0;

		renderer = given_renderer;
		printf("created object at (%.0f, %.0f) with speed: (%.2f, %.2f)\n", position.x, position.y, velocity.vx, velocity.vy);
}

DrawableObject::DrawableObject(SDL_Renderer* given_renderer)
{
		is_alive = true;
		character_class = 'D';
		mass = 100;
		charge = 0;
		position.x = 100.;
		position.y = 100.;
		velocity.vx = 0.;
		velocity.vy = 0.;
		force.fx = 0;
		force.fy = 0;


		renderer = given_renderer;
		printf("created std object at (%.0f, %.0f) with speed: (%.2f, %.2f)\n", position.x, position.y, velocity.vx, velocity.vy);

}

DrawableObject::~DrawableObject ()
{
		renderer = NULL;
}

void DrawableObject::apply_force(Force given_force)
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

void DrawableObject::update()
{
		// acceleration:
		if(force.fx != 0 || force.fy != 0) {
				velocity.vx += force.fx / mass;
				velocity.vy += force.fy / mass;
		}

		//position update:
		position.x += velocity.vx;
		position.y += velocity.vy;
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

Position DrawableObject::get_pos()
{
		return position;
}

Velocity DrawableObject::get_velocity()
{
		return velocity;
}

void DrawableObject::set_position(Position pos)
{
		position = pos;
}

void DrawableObject::set_velocity(Velocity vel){
		velocity = vel;
}

