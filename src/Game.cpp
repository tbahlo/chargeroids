#include "Game.h"
#include "SDL2/SDL.h"
//#include "DrawableObject.h"

Game::Game() {
	is_Running = true;
	game_window = NULL;
	screen_surface = NULL;
	testbild = NULL;
	//input_event = NULL;
	renderer = NULL;
	active_player = NULL;
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

		printf("Creating a Player...\n");
		Player* player = new Player(300., 300., renderer);
		drawable_objects.push_back(player);
		active_player = player;

		printf("Creating 1. object...\n");
		first_test_object = new DrawableObject(renderer);
		drawable_objects.push_back(first_test_object);

		printf("Creating 2. object...\n");
		DrawableObject* second_test_object = new DrawableObject(250., 250., renderer);
		drawable_objects.push_back(second_test_object);

		printf("Creating 3. object...\n");
		DrawableObject* third_test_object = new DrawableObject(300., 10., renderer);
		drawable_objects.push_back(third_test_object);

		printf("Creating a chargeroid...\n");
		DrawableObject* chargeroid_test_object = new Chargeroid(300., 10., renderer);
		drawable_objects.push_back(chargeroid_test_object);


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
							{
								printf("UP\n");
								double old_speed = active_player->get_y_velocity();
								double new_speed = old_speed - active_player->acceleration;
								active_player->set_y_velocity(new_speed);
								break;
							}
					case SDLK_DOWN:
							{
								printf("DOWN\n");
								double old_speed = active_player->get_y_velocity();
								double new_speed = old_speed + active_player->acceleration;
								active_player->set_y_velocity(new_speed);
								break;
							}
					case SDLK_LEFT:
							{
								printf("LEFT\n");
								double old_speed = active_player->get_x_velocity();
								double new_speed = old_speed - active_player->acceleration;
								active_player->set_x_velocity(new_speed);
								break;
							}
					case SDLK_RIGHT:
							{
								printf("RIGHT\n");
								double old_speed = active_player->get_x_velocity();
								double new_speed = old_speed + active_player->acceleration;
								active_player->set_x_velocity(new_speed);
								break;
							}
					case SDLK_a:
						for (int counter = 0; counter < 2; counter++){
								Chargeroid* new_chargeroid;
								new_chargeroid = new Chargeroid(250., 250., renderer);
								drawable_objects.push_back(new_chargeroid);
								printf("a - add new chargeroid (charge %.2f, mass %.2f) - amount of objects: %i\n",
								       new_chargeroid->get_charge(),
								       new_chargeroid->get_mass(),
								       (int) drawable_objects.size());
						}
						break;
					case SDLK_o:
						for (int counter = 0; counter < 2; counter++){
								DrawableObject* new_object;
								new_object = new DrawableObject(250., 250., renderer);
								drawable_objects.push_back(new_object);
								printf("o - add new object - amount of objects: %i\n", (int) drawable_objects.size());
						}
						break;
					case SDLK_d:
						if(drawable_objects.size() > 0) drawable_objects.pop_back();
						printf("d - kill youngest object  - amount of objects: %i\n", (int) drawable_objects.size());
						break;
					case SDLK_k:
						if(drawable_objects.size() > 0) drawable_objects.front()->kill();
						printf("k - marked oldest object as dead  - amount of objects: %i\n", (int) drawable_objects.size());
						break;
					case SDLK_i:
						printf("i - printing informations of every object\n");
						for (list<DrawableObject*>::iterator current_object = drawable_objects.begin();
								current_object != drawable_objects.end();
								current_object++)
							{
								printf("%c: m=%.0f q=%.2f \n", (*current_object)->character_class, (*current_object)->get_mass(), (*current_object)->get_charge());
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
	//printf("Player speed before: %f\n", active_player->get_y_velocity());
}

void Game::let_all_objects_interact()
{
	// iterate through all objects:
	for (list<DrawableObject*>::iterator interacting_object = drawable_objects.begin();
			interacting_object != drawable_objects.end();
			interacting_object++)
	{
		// you do not have to interact with yourself and with none of the
		// elements coming before you because they will already have interacted
		// with you

		// the following line is a ugly hack to start from the "next" item
		// it is necessary because "interacting_object++" actually increments
		// the iterator
		list<DrawableObject*>::iterator dummy_iterator = interacting_object;
		dummy_iterator++;
		for (list<DrawableObject*>::iterator partner_object = dummy_iterator;
				partner_object != drawable_objects.end();
				partner_object++)
		{
			// get parameters
			double obj1_x = (*interacting_object)->get_x();
			double obj1_y = (*interacting_object)->get_y();
			double obj2_x = (*partner_object)->get_x();
			double obj2_y = (*partner_object)->get_y();
			double obj1_charge = (*interacting_object)->get_charge();
			double obj2_charge = (*partner_object)->get_charge();

			// calculate resulting vectors
			double diff_x = obj2_x - obj1_x;
			double diff_y = obj2_y - obj1_y;

			double distance = sqrt(
					pow(diff_x, 2)
					+ pow(diff_y, 2));
			// lower cap for distance to avoid division-by-(nearly)zero problems
			if (distance < 1) distance = 1;

			double force_magnitude = obj1_charge * obj2_charge / pow(distance, 2);
//			printf("obj1: x=%.2f, y=%.2f, charge=%.2f|| obj2: x=%.2f, y=%.2f, charge=%.2f\n",
//			       obj1_x,
//			       obj1_y,
//			       obj1_charge,
//			       obj2_x,
//			       obj2_y,
//			       obj2_charge);
			force_magnitude *= 0.01;
			double force_x = force_magnitude * diff_x / distance;
			double force_y = force_magnitude * diff_y / distance;
			//                                 ^^^^^^^^^^^^^^^^^^
			//   these are the unit vector components for (1)->(2)
//			printf("---ddist: %.2f, force_mag: %.2f, fx=%.2f, fy=%.2f\n",
//			       distance,
//			       force_magnitude,
//			       force_x,
//			       force_y);



			// apply force to objects
			(*interacting_object)->apply_x_force(-force_x);
			(*interacting_object)->apply_y_force(-force_y);
			(*partner_object)->apply_x_force(force_x);
			(*partner_object)->apply_y_force(force_y);

		}
	}



}

void Game::spawn_new_objects()
{
	for(list<DrawableObject*>::iterator current_object = drawable_objects.begin();
			current_object != drawable_objects.end();
			current_object++)
		{
			while ((*current_object)->has_child())
				{
					drawable_objects.push_back((*current_object)->get_child());
				}
		}
}

void Game::remove_dead_objects()
{
	for (list<DrawableObject*>::iterator current_object = drawable_objects.begin();
			current_object != drawable_objects.end();
			current_object++)
	{
		if ((*current_object)->is_dead())
		{
			//DrawableObject* object_to_kill = *current_object;
			current_object = drawable_objects.erase(current_object);
			current_object--;
			//delete object_to_kill;
		}
	}
}

void Game::update_positions() {
	for (list<DrawableObject*>::iterator iter = drawable_objects.begin();
			iter != drawable_objects.end();
			iter++)
	{
		(*iter)->update();
	}
}

void Game::apply_friction() {
	for (list<DrawableObject*>::iterator iter = drawable_objects.begin(); iter != drawable_objects.end(); iter++)
	{
		(*iter)->set_x_velocity((*iter)->get_x_velocity() * 0.99);
		(*iter)->set_y_velocity((*iter)->get_y_velocity() * 0.99);
	}
}

void Game::check_for_border_crossings()
{
	for (list<DrawableObject*>::iterator iter = drawable_objects.begin(); iter != drawable_objects.end(); iter++)
		{
			double vertical_position = (*iter)->get_y();
			double horizontal_position = (*iter)->get_x();

			if (vertical_position < -5)
			{
				(*iter)->set_y(505);
			}
			else if (vertical_position > 505)
			{
				(*iter)->set_y(-5);
			}

			if (horizontal_position <= -5)
			{
				(*iter)->set_x(505);
			}
			else if (horizontal_position > 505)
			{
				(*iter)->set_x(-5);
			}
		}
}


void Game::render_current_frame(){
	//clear screen
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	// draw all drawable objects:
	for (list<DrawableObject*>::iterator iter = drawable_objects.begin(); iter != drawable_objects.end(); iter++)
	{
		(*iter)->draw_myself();
	}

	//finally render the image!
	SDL_RenderPresent(renderer);
}

void Game::clean_up(){
	//TODO: sometimes there is an error while closing the prog
	// using the q button. I assume somethings wrong here.

	// remove all drawable objects
	for (list<DrawableObject*>::iterator current_object = drawable_objects.begin(); current_object != drawable_objects.end(); current_object++)
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
