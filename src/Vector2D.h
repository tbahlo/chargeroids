/*
 * Vector2D.h
 *
 *  Created on: 21.03.2019
 *      Author: thore
 */

#ifndef SRC_VECTOR2D_H_
#define SRC_VECTOR2D_H_


class Vector2D
{
public:
	Vector2D();
	Vector2D(double x, double y);
	double x;
	double y;
	
	double len(void);
	Vector2D unit_vector(void);
	double angle(void);
	void rotate(double angle);
};

#endif /* SRC_VECTOR2D_H_ */
