#include "Game.h"
#include "SDL2/SDL.h"
#include <ctime>
#include <stdlib.h>

#define C_WORLD_SIZE_X 1000
#define C_WORLD_SIZE_Y 1000
#define C_TOLERANCE 5
#define C_FRICTION_LOSS_IN_PERC 0.1

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

		printf("Creating a Player...\n");
		Vector2D player_pos;
		player_pos.x = C_WORLD_SIZE_X / 2.;
		player_pos.y = C_WORLD_SIZE_Y / 2.;
		Player* player = new Player(renderer);
		player->set_position(player_pos);
		drawable_objects.push_back(player);
		active_player = player;

		//printf("Creating 1. object...\n");
		//DrawableObject* first_test_object;
		//first_test_object = new DrawableObject(renderer);
		//drawable_objects.push_back(first_test_object);

		//printf("Creating a chargeroid...\n");
		//Chargeroid* chargeroid_test_object = new Chargeroid(renderer);
		//drawable_objects.push_back(chargeroid_test_object);
		//printf("Creating a second chargeroid...\n");
		//Chargeroid* chargeroid_test_object2 = new Chargeroid(renderer);
		//drawable_objects.push_back(chargeroid_test_object2);


		// MAIN GAME LOOP
		float last_time_in_s = get_current_time_in_s();
		float last_dbg_msg_time_in_s = get_current_time_in_s();
		float dbg_msg_delay = 1;

		int current_level = 0;
		while (is_Running){
			float current_time_in_s = get_current_time_in_s();
			float time_passed = (current_time_in_s - last_time_in_s);
			if (time_passed > 1./60.) // framerate limit
			{
				handle_input_events();
				update_game_state(time_passed);
				render_current_frame();
				last_time_in_s = current_time_in_s;
				if ((current_time_in_s - last_dbg_msg_time_in_s) > dbg_msg_delay)
				{
					printf("[%.2f] FPS: %f \nDrawable_objects list: \n", current_time_in_s, 1./time_passed);
					for (list<DrawableObject*>::iterator current_object = drawable_objects.begin();
							current_object != drawable_objects.end();
							++current_object)
					{
						printf("%c[ m= %02.1f | q= %02.1f | pos= (%03.1f;%03.1f) ] [%d]\n",
								(*current_object)->character_class,
								(*current_object)->get_mass(),
								(*current_object)->get_charge(),
								(*current_object)->get_pos().x,
								(*current_object)->get_pos().y,
								(int)(*current_object)->is_dead());
					};
					last_dbg_msg_time_in_s = current_time_in_s;
					printf("\n");
					printf("Shot cooldown: %f\n", player->shot_cooldown);
				}
				if (get_amount_of_alive_chargeroids() <= 0)
				{
					current_level += 1;
					initialize_level(current_level);
				}
			}
		}
		clean_up();

		return 0;
	}
}

/**
 *  \brief Inititalisiert die SDL Engine und erzeugt ein Fenster
 */
bool Game::initialize(){
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
				C_WORLD_SIZE_X,
				C_WORLD_SIZE_Y,
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

float Game::get_current_time_in_s(){
	return float(clock()) / float(CLOCKS_PER_SEC);
}


void Game::handle_input_events(){
	while (SDL_PollEvent(&input_event) != 0){
	// User requests to quit
		if(input_event.type == SDL_QUIT){
		    is_Running = false;
		}
		// User releases a key
		else if (input_event.type == SDL_KEYUP){
				//printf("Key released: ");
				switch ( input_event.key.keysym.sym ){
						case SDLK_UP:
								{
										active_player->stop();
										break;
								}
						case SDLK_LEFT:
								{
										active_player->rotate(0);
										break;
								}
						case SDLK_RIGHT:
								{
										active_player->rotate(0);
										break;
								}
				}
		}
		// User presses a key
		else if ((input_event.type == SDL_KEYDOWN) || (input_event.type == SDL_PRESSED)) {
				//printf("Key pressed: ");

				// check which key	 was pressed:
				switch ( input_event.key.keysym.sym ){
						case SDLK_UP:
						{
								active_player->boost();
								break;
						}
					case SDLK_DOWN:
							{
								//printf("DOWN\n");
								active_player->stop();
								break;
							}
					case SDLK_LEFT:
							{
								//printf("LEFT\n");
								active_player->rotate(-1);
								break;
							}
					case SDLK_RIGHT:
							{
								//printf("RIGHT\n");
								active_player->rotate(1);
								break;
							}
					case SDLK_SPACE:
							{
								//printf("SPACE\n");
								active_player->shoot();
								break;
							}
					case SDLK_a:
						for (int counter = 0; counter < 1; ++counter){
								Chargeroid* new_chargeroid;
								Vector2D chargeroid_pos;
								chargeroid_pos.x = rand() % C_WORLD_SIZE_X;
								chargeroid_pos.y = rand() % C_WORLD_SIZE_X;
								new_chargeroid = new Chargeroid(chargeroid_pos, renderer);
								drawable_objects.push_back(new_chargeroid);
								/*printf("a - add new chargeroid (charge %.2f, mass %.2f) - amount of objects: %i\n",
								       new_chargeroid->get_charge(),
								       new_chargeroid->get_mass(),
								       (int) drawable_objects.size());*/
						}
						break;
					case SDLK_o:
						for (int counter = 0; counter < 2; ++counter){
								DrawableObject* new_object;
								Vector2D object_position = {250., 250.}; 
								new_object = new DrawableObject(object_position, renderer);
								drawable_objects.push_back(new_object);
								//printf("o - add new object - amount of objects: %i\n", (int) drawable_objects.size());
						}
						break;
					case SDLK_d:
						if(drawable_objects.size() > 0) drawable_objects.pop_back();
						//printf("d - kill youngest object  - amount of objects: %i\n", (int) drawable_objects.size());
						break;
					case SDLK_k:
						if(drawable_objects.size() > 0) drawable_objects.front()->kill();
						//printf("k - marked oldest object as dead  - amount of objects: %i\n", (int) drawable_objects.size());
						break;
					case SDLK_i:
						//printf("i - printing informations of every object\n");
						for (list<DrawableObject*>::iterator current_object = drawable_objects.begin();
								current_object != drawable_objects.end();
								++current_object)
							{
								//printf("%c: m=%.0f q=%.2f \n", (*current_object)->character_class, (*current_object)->get_mass(), (*current_object)->get_charge());
							}
						break;

					case SDLK_q:
						//printf("q - quitting \n");
						is_Running = false;
						break;
					default:
						//printf("Unknown\n");
						break;
				}
		}
	}
}

void Game::update_game_state(float time_passed)
{
	let_all_objects_interact();
	spawn_new_objects();
	remove_dead_objects();
	apply_friction();
	update_positions(time_passed);
	check_for_border_crossings();
	//printf("Player speed before: %f\n", active_player->get_y_velocity());
}

void Game::let_all_objects_interact()
{
	// iterate through all objects:
	for (list<DrawableObject*>::iterator interacting_object = drawable_objects.begin();
			interacting_object != drawable_objects.end();
			++interacting_object)
	{
		// you do not have to interact with yourself and with none of the
		// elements coming before you because they will already have interacted
		// with you

		// the following line is a ugly hack to start from the "next" item
		// it is necessary because "interacting_object++" actually increments
		// the iterator
		list<DrawableObject*>::iterator dummy_iterator = interacting_object;
		++dummy_iterator;
		for (list<DrawableObject*>::iterator partner_object = dummy_iterator;
				partner_object != drawable_objects.end();
				++partner_object)
		{
			// get parameters
			Vector2D obj1_pos = (*interacting_object)->get_pos();
			Vector2D obj2_pos = (*partner_object)->get_pos();
			double obj1_charge = (*interacting_object)->get_charge();
			double obj2_charge = (*partner_object)->get_charge();

			// calculate resulting vectors
			double diff_x = obj2_pos.x - obj1_pos.x;
			double diff_y = obj2_pos.y - obj1_pos.y;

			double distance = sqrt(
					pow(diff_x, 2)
					+ pow(diff_y, 2));
			// lower cap for distance to avoid division-by-(nearly)zero problems
			if (distance < 1) distance = 1;

			// calculate charge-force
			double force_magnitude = obj1_charge * obj2_charge / pow(distance, 2);
			double force_x = force_magnitude * diff_x / distance;
			double force_y = force_magnitude * diff_y / distance;
			//                                 ^^^^^^^^^^^^^^^^^^
			//   these are the unit vector components for (1)->(2)
			Vector2D force = {force_x, force_y};

			// apply force to objects
			(*partner_object)->apply_force(force);
			Vector2D inv_force = Vector2D(-force.x, -force.y);
			(*interacting_object)->apply_force(inv_force);

			// Collision detection - kill both if they collide:
			//if (distance <= (*interacting_object)->get_mass() + (*partner_object)->get_mass()) {
			if (((*interacting_object)->character_class == 'p') || ((*partner_object)->character_class == 'p'))
			{
				// do nothing - particles do not interact
			}
			else
			{
				double radius_interacting_object = sqrt((*interacting_object)->get_mass());
				double radius_partner_object = sqrt((*partner_object)->get_mass());

				double combined_radius = radius_interacting_object + radius_partner_object; 
				if (distance <= 20) {
					(*interacting_object)->kill();
					(*partner_object)->kill();
				}
			}

		}
	}
}

void Game::spawn_new_objects()
{
	for(list<DrawableObject*>::iterator current_object = drawable_objects.begin();
			current_object != drawable_objects.end();
			++current_object)
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
			++current_object)
	{
		if ((*current_object)->is_dead())
		{
			printf("this object is dead: \n");
			printf("%c[ m= %2.1f | q= %2.1f | pos= (%3.1f;%3.1f) ]\n",
									(*current_object)->character_class,
									(*current_object)->get_mass(),
									(*current_object)->get_charge(),
									(*current_object)->get_pos().x,
									(*current_object)->get_pos().y);

			Vector2D explosion_pos = (*current_object)->get_pos();
			Vector2D explosion_velocity = (*current_object)->get_velocity();

			// create explosion particle effects:
			// Projectiles (p) and Particles (P) shall not create particle effects
			if ((*current_object)->character_class != 'p' && (*current_object)->character_class != 'P')
			{
				double fragment_speed = 600;
				double emission_angle_spread = 30;

				int amount_of_fragments = 20;
				for (int fragment_iter = 0; fragment_iter <= amount_of_fragments; ++fragment_iter)
				{
					double emission_angle = (((double) fragment_iter) / ((double) amount_of_fragments)) * 360.;
					emission_angle += ((rand() % (int)(emission_angle_spread + 1)) - (emission_angle_spread / 2 + 1));

					Vector2D proj_speed;
					proj_speed.x = explosion_velocity.x - (fragment_speed * (1 + ((double)(rand() % 50))/100.)) * cos(emission_angle /360. * 2 * 3.14159);
					proj_speed.y = explosion_velocity.y - (fragment_speed * (1 + ((double)(rand() % 50))/100.)) * sin(emission_angle /360. * 2 * 3.14159);

					Particle* new_particle = new Particle(explosion_pos, proj_speed, renderer);
					drawable_objects.push_back(new_particle);
				}

			}

			current_object = drawable_objects.erase(current_object);
			--current_object;

		}
	}
}

void Game::update_positions(float time_passed) {
	for (list<DrawableObject*>::iterator iter = drawable_objects.begin();
			iter != drawable_objects.end();
			++iter)
	{
		(*iter)->update(time_passed);
	}
}

void Game::apply_friction() {
	for (list<DrawableObject*>::iterator iter = drawable_objects.begin(); iter != drawable_objects.end(); ++iter)
	{
			Vector2D speed = (*iter)->get_velocity();
			speed.x *= (100. - C_FRICTION_LOSS_IN_PERC) / 100.;
			speed.y *= (100. - C_FRICTION_LOSS_IN_PERC) / 100.;
			(*iter)->set_velocity(speed);
	}
}

void Game::check_for_border_crossings()
{
	for (list<DrawableObject*>::iterator iter = drawable_objects.begin(); iter != drawable_objects.end(); ++iter)
		{
			Vector2D iter_pos = (*iter)->get_pos();
				
			if (iter_pos.y < -C_TOLERANCE)
			{
				iter_pos.y += C_WORLD_SIZE_Y;
			}
			else if (iter_pos.y > C_WORLD_SIZE_Y + C_TOLERANCE)
			{
				iter_pos.y -= C_WORLD_SIZE_Y;
			}

			if (iter_pos.x < -C_TOLERANCE)
			{
				iter_pos.x += C_WORLD_SIZE_X;
			}
			else if (iter_pos.x > C_WORLD_SIZE_X + C_TOLERANCE)
			{
				iter_pos.x -= C_WORLD_SIZE_X;
			}
			(*iter)->set_position(iter_pos);
		}
}


void Game::render_current_frame(){
	//clear screen
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	// draw all drawable objects:
	for (list<DrawableObject*>::iterator iter = drawable_objects.begin(); iter != drawable_objects.end(); ++iter)
	{
		(*iter)->draw_myself();
	}

	//finally render the image!
	SDL_RenderPresent(renderer);
}

uint32_t Game::get_amount_of_alive_chargeroids()
{
	uint32_t amount = 0;
	for (list<DrawableObject*>::iterator current_object = drawable_objects.begin();
							current_object != drawable_objects.end();
							++current_object)
	{
		if ((*current_object)->character_class == 'C')
		{
			amount += 1;
		}
	};
	return amount;
}

void Game::initialize_level(uint32_t level)
{
	for (uint32_t iter = 0; iter <= level; iter++)
	{
		Chargeroid* chargeroid_test_object = new Chargeroid(renderer);
		drawable_objects.push_back(chargeroid_test_object);
	}
}

void Game::clean_up(){
	//TODO: sometimes there is an error while closing the prog
	// using the q button. I assume somethings wrong here.

	// remove all drawable objects
	for (list<DrawableObject*>::iterator current_object = drawable_objects.begin(); current_object != drawable_objects.end(); ++current_object)
	{
		if(drawable_objects.size() > 0)
			{
			current_object = drawable_objects.erase(current_object);
			--current_object;
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
