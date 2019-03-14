/*
 * Projectile.h
 *
 *  Created on: 14.03.2019
 *      Author: thore
 */

#ifndef SRC_PROJECTILE_H_
#define SRC_PROJECTILE_H_

#include "types.h"
#include "DrawableObject.h"

class Projectile : public DrawableObject
{
public:
	Projectile(SDL_Renderer* renderer);
	Projectile(Position pos, SDL_Renderer* renderer);
	Projectile(Position pos, Velocity vel, SDL_Renderer* renderer);

	virtual
	~Projectile();

	void kill() override;
	void draw_myself() override;
	void apply_force(Force force) override;
	void update(float time_passed) override;


private:
	double lifetime_left;
};

#endif /* SRC_PROJECTILE_H_ */
