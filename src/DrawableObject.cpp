/*
 * DrawableObject.cpp
 *
 *  Created on: 05.08.2016
 *      Author: thore
 */

#include "DrawableObject.h"
#include <SDL2/SDL.h>

DrawableObject::DrawableObject(float x, float y, SDL_Renderer* given_renderer)
{
	x_position = x;
	y_position = y;
	renderer = given_renderer;
}

DrawableObject::DrawableObject(SDL_Renderer* given_renderer)
{
	x_position = 0;
	y_position = 0;
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
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF)
	SDL_RenderFillRect(renderer, &my_body);
}

float DrawableObject::get_x()
{
	return x_position;
}

float DrawableObject::get_y()
{
	return y_position;
}

void DrawableObject::set_x(float x)
{
	x_position = x;
}

void DrawableObject::set_y(float y)
{
	y_position = y;
}
