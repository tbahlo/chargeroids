#ifndef SRC_DRAWABLEOBJECT_H_
#define SRC_DRAWABLEOBJECT_H_
#include <SDL2/SDL.h>

class DrawableObject
{
public:
	DrawableObject(double x, double y, SDL_Renderer* given_renderer);
	DrawableObject(SDL_Renderer* given_renderer);
	virtual
	~DrawableObject ();

	void draw_myself();
<<<<<<< HEAD
	double get_x();
	double get_y();
	double get_x_velocity();
	double get_y_velocity();


	void set_x(double x);
	void set_y(double y);
	void set_x_velocity(double x_velocity);
	void set_y_velocity(double y_velocity);

private:
	SDL_Renderer* renderer;
	double x_position;
	double y_position;

	double x_velocity;
	double y_velocity;
=======
	float get_x();
	float get_y();
	void set_x(float x);
	void set_y(float y);

private:
	SDL_Renderer* renderer;
	float x_position;
	float y_position;


>>>>>>> 39749244dc714ccf55e697156dd30b35a5e89450

};

#endif /* SRC_DRAWABLEOBJECT_H_ */
