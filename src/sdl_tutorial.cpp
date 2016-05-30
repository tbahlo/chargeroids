#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int num_arguments, char* arguments[]) {

  //The window we'll be rendering to
  SDL_Window* window = NULL;

  //The surface contained by the window
  SDL_Surface* screenSurface = NULL;

  printf("return value of SDL_Init: %i \n", SDL_Init( SDL_INIT_VIDEO));

  return 0;
}
