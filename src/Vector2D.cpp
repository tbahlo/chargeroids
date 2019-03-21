/*
 * Vector2D.cpp
 *
 *  Created on: 21.03.2019
 *      Author: thore
 */
#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D()
{
		x = 1;
		y = 1;
}

Vector2D::Vector2D(double xcoord, double ycoord)
{
		x = xcoord;
		y = ycoord;
}

double Vector2D::len()
{
		return std::sqrt(x*x + y*y);
}

Vector2D Vector2D::unit_vector()
{
		return Vector2D(x/len(), y/len());
}

double Vector2D::angle() {
		return atan(y/x) * 180 / M_PI;
}

void Vector2D::rotate(double angle)
{
		x = x * cos(angle/180*M_PI);
		y = y * sin(angle/180*M_PI);
}
