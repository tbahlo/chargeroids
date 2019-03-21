#ifndef SRC_DRAWABLEOBJECT_H_
#define SRC_DRAWABLEOBJECT_H_
#include <SDL2/SDL.h>
#include <list>
#include "Vector2D.h"

using namespace std;

class DrawableObject
{
public:
	DrawableObject(Vector2D position, Vector2D velocity, SDL_Renderer* given_renderer);
	DrawableObject(Vector2D position, SDL_Renderer* given_renderer);
	DrawableObject(SDL_Renderer* given_renderer);
	virtual
	~DrawableObject ();

	virtual void draw_myself();
	virtual void kill();
	virtual void update(float time_passed);
	bool is_dead();
	bool has_child();
	virtual DrawableObject* get_child();

	char character_class;

	Vector2D get_pos();
	Vector2D get_velocity();
	double get_mass();
	double get_charge();


	void set_position(Vector2D position);
	void set_velocity(Vector2D velocity);
	virtual void apply_force(Vector2D force);	

protected:
	SDL_Renderer* renderer;
	bool is_alive;
	double mass;
	double charge;
	list<DrawableObject*> children_objects;

	Vector2D position;
	Vector2D velocity;
	Vector2D force;
};

#endif /* SRC_DRAWABLEOBJECT_H_ */
