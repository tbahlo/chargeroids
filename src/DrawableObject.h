#ifndef SRC_DRAWABLEOBJECT_H_
#define SRC_DRAWABLEOBJECT_H_
#include <SDL2/SDL.h>
#include <list>

using namespace std;

class DrawableObject
{
public:
	DrawableObject(double x, double y, double velocity_x, double velocity_y, SDL_Renderer* given_renderer);
	DrawableObject(double x, double y, SDL_Renderer* given_renderer);
	DrawableObject(SDL_Renderer* given_renderer);
	virtual
	~DrawableObject ();

	virtual void draw_myself();
	virtual void kill();
	bool is_dead();
	bool has_child();
	virtual DrawableObject get_child();

	char character_class;

	double get_x();
	double get_y();
	double get_x_velocity();
	double get_y_velocity();


	void set_x(double x);
	void set_y(double y);
	void set_x_velocity(double x_velocity);
	void set_y_velocity(double y_velocity);

protected:
	SDL_Renderer* renderer;
	bool is_alive;
	list<DrawableObject> children_objects;

	//TODO: change to structures - might be a lot of work
	double x_position;
	double y_position;

	double x_velocity;
	double y_velocity;
};

#endif /* SRC_DRAWABLEOBJECT_H_ */
