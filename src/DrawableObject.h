#ifndef SRC_DRAWABLEOBJECT_H_
#define SRC_DRAWABLEOBJECT_H_
#include <SDL2/SDL.h>

class DrawableObject
{
public:
	DrawableObject(float x, float y, SDL_Renderer* given_renderer);
	DrawableObject(SDL_Renderer* given_renderer);
	virtual
	~DrawableObject ();

	void draw_myself();
	float get_x();
	float get_y();
	void set_x(float x);
	void set_y(float y);

private:
	SDL_Renderer* renderer;
	float x_position;
	float y_position;



};

#endif /* SRC_DRAWABLEOBJECT_H_ */
