#include "Game.h"
#include "SDL2/SDL.h"
#include "DrawableObject.h"

Game::Game() {
	is_Running = true;
	game_window = NULL;
	screen_surface = NULL;
	testbild = NULL;
	//input_event = NULL;
	renderer = NULL;
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

int Game::start(){
	//TODO: folgenden Code auf Exceptions statt ERROR codes umschreiben
	if (!initialize()){
		printf("Could not initialize => exit \n");
		SDL_Quit();
		return 1;
	}
	else {
		DrawableObject* first_test_object;
		first_test_object = new DrawableObject(renderer);
		drawable_objects.push_back(*first_test_object);

		DrawableObject* second_test_object = new DrawableObject(250., 250., renderer);
		drawable_objects.push_back(*second_test_object);

		DrawableObject* third_test_object = new DrawableObject(300., 10., renderer);
		drawable_objects.push_back(*third_test_object);

		while (is_Running){
			handle_input_events();
			update_game_state();
			render_current_frame();
		}
		clean_up();

		return 0;
	}
}

int Game::initialize(){
	// initialisiere SDL (gfx engine):
	bool success = false;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not be initialized! SDL_Error: %s\n ", SDL_GetError());
	}
	else {
		// create a Window:
		game_window = SDL_CreateWindow(
				"chargeroids v0.0",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				500,
				500,
				SDL_WINDOW_SHOWN);
		if (game_window == NULL) {
			printf("Window could not be created! SDL_Error: %s,\n", SDL_GetError());
		}
		else {
			// create Screen Surface (TODO: check for failing) :
			screen_surface = SDL_GetWindowSurface(game_window);

			// load image:
			testbild = SDL_LoadBMP("/home/thore/Dokumente/chargeroids/src/testbild.bmp");
			if(testbild == NULL){
				printf("Image could not be loaded! SDL_Error: %s\n", SDL_GetError());
			}
			renderer = SDL_CreateRenderer(game_window, -1, SDL_RENDERER_ACCELERATED);
			success = true;
		}
	}

	return success;
}

void Game::handle_input_events(){
	while (SDL_PollEvent(&input_event) != 0){
        // User requests to quit
		if(input_event.type == SDL_QUIT){
		    is_Running = false;
		}
        // User presses a key
        else if (input_event.type == SDL_KEYDOWN){
            printf("Key pressed: ");
            
            // check which key	 was pressed:
            switch ( input_event.key.keysym.sym ){
                case SDLK_UP:
                	printf("UP\n");
                	break;
                case SDLK_DOWN:
                	printf("DOWN\n");
                	break;
                case SDLK_LEFT:
                	printf("LEFT\n");
                	break;
                case SDLK_RIGHT:
                	printf("RIGHT\n");
                	break;
                case SDLK_q:
                	is_Running=false;
                	break;
                default:
                printf("Unknown\n");
            }
        }
	}
}

void Game::update_game_state(){

	let_all_objects_interact();
	spawn_new_objects();
	remove_dead_objects();
	update_positions();
	check_for_border_crossings();}

void Game::let_all_objects_interact()
{

}
void Game::spawn_new_objects()
{

}

void Game::remove_dead_objects()
{

}

void Game::update_positions() {

}

void Game::check_for_border_crossings()
{
	for (list<DrawableObject>::iterator iter = drawable_objects.begin(); iter != drawable_objects.end(); iter++)
		{
			float vertical_position = iter->get_y();
			float horizontal_position = iter->get_x();

			if (vertical_position <=0)
				{
					iter->set_y(500);
				}
			else if (vertical_position >= 500)
				{
					iter->set_y(0);
				}
			else{
					iter->set_y(vertical_position - 0.01);
			}

			if (horizontal_position <= 0)
							{
								iter->set_x(500);
							}
						else if (horizontal_position >= 500)
							{
								iter->set_x(0);
							}
						else{
								iter->set_x(vertical_position - 0.01);
						}

		}
}






void Game::render_current_frame(){
	//clear screen
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	// draw all drawable objects:
	for (list<DrawableObject>::iterator iter = drawable_objects.begin(); iter != drawable_objects.end(); iter++)
		{
			iter->draw_myself();
		}

	//finally render the image!
	SDL_RenderPresent(renderer);
}

void Game::clean_up(){
	// deallocate surface
	SDL_FreeSurface(screen_surface);
	screen_surface = NULL;

	// Destroy the window
	SDL_DestroyWindow(game_window);
	game_window = NULL;

	SDL_Quit();
}
