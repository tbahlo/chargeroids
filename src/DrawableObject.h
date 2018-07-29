#ifndef SRC_DRAWABLEOBJECT_H_
#define SRC_DRAWABLEOBJECT_H_
#include <SDL2/SDL.h>
#include <list>
#include "types.h"

using namespace std;

class DrawableObject
{
public:
	DrawableObject(Position position, Velocity velocity, SDL_Renderer* given_renderer);
	DrawableObject(Position position, SDL_Renderer* given_renderer);
	DrawableObject(SDL_Renderer* given_renderer);
	virtual
	~DrawableObject ();

	virtual void draw_myself();
	virtual void kill();
	void update();
	bool is_dead();
	bool has_child();
	virtual DrawableObject* get_child();

	char character_class;

	Position get_pos();
	Velocity get_velocity();
	double get_mass();
	double get_charge();


	void set_position(Position position);
	void set_velocity(Velocity velocity);
	virtual void apply_force(Force force);	

protected:
	SDL_Renderer* renderer;
	bool is_alive;
	double mass;
	double charge;
	list<DrawableObject*> children_objects;

	Position position;
	Velocity velocity;
	Force force;
};

#endif /* SRC_DRAWABLEOBJECT_H_ */
