/*
 * DrawableObject.cpp
 *
 *  Created on: 05.08.2016
 *      Author: thore
 */

#include "DrawableObject.h"
#include <SDL2/SDL.h>

DrawableObject::DrawableObject(double x, double y, double velocity_x, double velocity_y, SDL_Renderer* given_renderer)
{
	is_alive = true;
	character_class = 'D';

	x_position = x;
	y_position = y;

	x_velocity = velocity_x;
	y_velocity = velocity_y;
	renderer = given_renderer;

	printf("created object at (%.0f, %.0f) with speed: (%.2f, %.2f)\n", x_position, y_position, x_velocity, y_velocity);
}

DrawableObject::DrawableObject(double x, double y, SDL_Renderer* given_renderer)
{
	is_alive = true;
	character_class = 'D';
	x_position = x;
	y_position = y;

	x_velocity = double((rand()%200 - rand()%200)) / 100;
	y_velocity = double((rand()%200 - rand()%200)) / 100;
	renderer = given_renderer;
	printf("created object at (%.0f, %.0f) with speed: (%.2f, %.2f)\n", x_position, y_position, x_velocity, y_velocity);
}

DrawableObject::DrawableObject(SDL_Renderer* given_renderer)
{
	is_alive = true;
	character_class = 'D';
	x_position = 100.;
	y_position = 100.;
	x_velocity = 0.;
	y_velocity = 0.;

	renderer = given_renderer;
	printf("created std object at (%.0f, %.0f) with speed: (%.2f, %.2f)\n", x_position, y_position, x_velocity, y_velocity);

}

DrawableObject::~DrawableObject ()
{
	renderer = NULL;
}

void DrawableObject::draw_myself()
{
	SDL_Rect my_body;
	my_body.x = x_position;
	my_body.y = y_position;
	my_body.w = 10;
	my_body.h = 10;
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &my_body);
}

bool DrawableObject::has_child()
{
	return children_objects.size() != 0;
}

DrawableObject DrawableObject::get_child()
{
	if (this->has_child()){
			DrawableObject object_to_be_returned = *children_objects.end();
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

double DrawableObject::get_x()
{
	return x_position;
}

double DrawableObject::get_y()
{
	return y_position;
}

double DrawableObject::get_x_velocity()
{
	return x_velocity;
}

double DrawableObject::get_y_velocity()
{
	return y_velocity;
}

void DrawableObject::set_x(double x)
{
	x_position = x;
}

void DrawableObject::set_y(double y)
{
	y_position = y;
}

void DrawableObject::set_x_velocity(double x_vel){
	x_velocity = x_vel;
}

void DrawableObject::set_y_velocity(double y_vel){
	y_velocity = y_vel;
}
