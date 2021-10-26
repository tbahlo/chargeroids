#ifndef SRC_PARTICLE_H_
#define SRC_PARTICLE_H_

#include "DrawableObject.h"

class Particle : public DrawableObject
{
public:
	Particle(SDL_Renderer* renderer);
	Particle(Vector2D pos, SDL_Renderer* renderer);
	Particle(Vector2D pos, Vector2D vel, SDL_Renderer* renderer);

	virtual
	~Particle();

	void kill() override;
	void draw_myself() override;
	void update(float time_passed) override;


private:
	double lifetime_left;
};

#endif /* SRC_PARTICLE_H_ */
