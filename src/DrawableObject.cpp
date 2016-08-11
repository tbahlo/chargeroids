/*
 * DrawableObject.cpp
 *
 *  Created on: 05.08.2016
 *      Author: thore
 */

#include "DrawableObject.h"
#include <SDL2/SDL.h>

DrawableObject::DrawableObject(double x, double y, SDL_Renderer* given_renderer)
{
	x_position = x;
	y_position = y;
<<<<<<< HEAD
	x_velocity = (random()-random()) * 0.000000001;
	y_velocity = (random()-random()) * 0.000000001;
	renderer = given_renderer;
	printf("created object at (%.0f, %.0f) with speed: (%.2f, %.2f)\n", x_position, y_position, x_velocity, y_velocity);
=======
	renderer = given_renderer;
>>>>>>> 39749244dc714ccf55e697156dd30b35a5e89450
}

DrawableObject::DrawableObject(SDL_Renderer* given_renderer)
{
<<<<<<< HEAD
	x_position = 10;
	y_position = 10;
	x_velocity = 0;
	y_velocity = 0;

=======
	x_position = 0;
	y_position = 0;
>>>>>>> 39749244dc714ccf55e697156dd30b35a5e89450
	renderer = given_renderer;
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
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &my_body);
}

<<<<<<< HEAD
double DrawableObject::get_x()
=======
float DrawableObject::get_x()
>>>>>>> 39749244dc714ccf55e697156dd30b35a5e89450
{
	return x_position;
}

<<<<<<< HEAD
double DrawableObject::get_y()
=======
float DrawableObject::get_y()
>>>>>>> 39749244dc714ccf55e697156dd30b35a5e89450
{
	return y_position;
}

<<<<<<< HEAD
double DrawableObject::get_x_velocity()
{
	return x_velocity;
}

double DrawableObject::get_y_velocity()
{
	return y_velocity;
}

void DrawableObject::set_x(double x)
=======
void DrawableObject::set_x(float x)
>>>>>>> 39749244dc714ccf55e697156dd30b35a5e89450
{
	x_position = x;
}

<<<<<<< HEAD
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
=======
void DrawableObject::set_y(float y)
{
	y_position = y;
}
>>>>>>> 39749244dc714ccf55e697156dd30b35a5e89450
