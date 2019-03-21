/*
 * Projectile.h
 *
 *  Created on: 14.03.2019
 *      Author: thore
 */

#ifndef SRC_PROJECTILE_H_
#define SRC_PROJECTILE_H_

#include "DrawableObject.h"

class Projectile : public DrawableObject
{
public:
	Projectile(SDL_Renderer* renderer);
	Projectile(Vector2D pos, SDL_Renderer* renderer);
	Projectile(Vector2D pos, Vector2D vel, SDL_Renderer* renderer);

	virtual
	~Projectile();

	void kill() override;
	void draw_myself() override;
	void apply_force(Vector2D force) override;
	void update(float time_passed) override;


private:
	double lifetime_left;
};

#endif /* SRC_PROJECTILE_H_ */
