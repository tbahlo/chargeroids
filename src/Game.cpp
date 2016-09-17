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

		printf("Creating 1. object...\n");
		first_test_object = new DrawableObject(renderer);
		drawable_objects.push_back(*first_test_object);

		printf("Creating 2. object...\n");
		DrawableObject* second_test_object = new DrawableObject(250., 250., renderer);
		drawable_objects.push_back(*second_test_object);

		printf("Creating 3. object...\n");
		DrawableObject* third_test_object = new DrawableObject(300., 10., renderer);
		drawable_objects.push_back(*third_test_object);

		printf("Creating an chargeroid...\n");
		DrawableObject* chargeroid_test_object = new Chargeroid(300., 10., renderer);
		drawable_objects.push_back(*chargeroid_test_object);


		// MAIN GAME LOOP
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
					case SDLK_a:
						for (int counter = 0; counter < 2; counter++){
								Chargeroid* new_chargeroid;
								new_chargeroid = new Chargeroid(250., 250., renderer);
								drawable_objects.push_back(*new_chargeroid);
								printf("a - add new chargeroid - amount of objects: %i\n", (int) drawable_objects.size());
						}
						break;
					case SDLK_d:
						if(drawable_objects.size() > 0) drawable_objects.pop_back();
						printf("d - kill youngest object  - amount of objects: %i\n", (int) drawable_objects.size());
						break;
					case SDLK_k:
						if(drawable_objects.size() > 0) drawable_objects.begin()->kill();
						printf("k - marked oldest object as dead  - amount of objects: %i\n", (int) drawable_objects.size());
						break;
					case SDLK_i:
						printf("i - printing informations of every object\n");
						for (list<DrawableObject>::iterator current_object = drawable_objects.begin();
								current_object != drawable_objects.end();
								current_object++)
							{
								printf("%c \n", current_object->character_class);
							}
						break;

					case SDLK_q:
						printf("q - quitting \n");
						is_Running = false;
						break;
					default:
						printf("Unknown\n");
				}
		}
	}
}


void Game::update_game_state()
{
	let_all_objects_interact();
	spawn_new_objects();
	remove_dead_objects();
	apply_friction();
	update_positions();
	check_for_border_crossings();
}

void Game::let_all_objects_interact()
{

}

void Game::spawn_new_objects()
{
	for(list<DrawableObject>::iterator current_object = drawable_objects.begin();
			current_object != drawable_objects.end();
			current_object++)
		{
			while (current_object->has_child())
				{
					drawable_objects.push_back(current_object->get_child());
				}
		}
}

void Game::remove_dead_objects()
{
	for (list<DrawableObject>::iterator current_object = drawable_objects.begin();
			current_object != drawable_objects.end();
			current_object++)
	{
		if (current_object->is_dead())
		{
			current_object = drawable_objects.erase(current_object);
			current_object--;
		}
	}
}

void Game::update_positions() {
	for (list<DrawableObject>::iterator iter = drawable_objects.begin();
			iter != drawable_objects.end();
			iter++)
	{
		iter->set_x(iter->get_x()+iter->get_x_velocity());
		iter->set_y(iter->get_y()+iter->get_y_velocity());
	}
}

void Game::apply_friction() {
	for (list<DrawableObject>::iterator iter = drawable_objects.begin(); iter != drawable_objects.end(); iter++)
	{
		iter->set_x_velocity(iter->get_x_velocity() * 0.999);
		iter->set_y_velocity(iter->get_y_velocity() * 0.999);
	}
}

void Game::check_for_border_crossings()
{
	for (list<DrawableObject>::iterator iter = drawable_objects.begin(); iter != drawable_objects.end(); iter++)
		{
			double vertical_position = iter->get_y();
			double horizontal_position = iter->get_x();

			if (vertical_position < -5)
				{
					iter->set_y(505);
				}
			else if (vertical_position > 505)
				{
					iter->set_y(-5);
				}

			if (horizontal_position <= -5)
							{
								iter->set_x(505);
							}
						else if (horizontal_position > 505)
							{
								iter->set_x(-5);
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
	//TODO: sometimes there is an error while closing the prog
	// using the q button. I assume somethings wrong here.

	// remove all drawable objects
	for (list<DrawableObject>::iterator current_object = drawable_objects.begin(); current_object != drawable_objects.end(); current_object++)
	{
		if(drawable_objects.size() > 0)
			{
			current_object = drawable_objects.erase(current_object);
			current_object--;
			}

	}

	// deallocate surface
	SDL_FreeSurface(screen_surface);
	screen_surface = NULL;

	// Destroy the window
	SDL_DestroyWindow(game_window);
	game_window = NULL;

	SDL_Quit();
}
