#include"AmoreEngine.h"


Window::Window(char* t){

	al_init();
	al_install_joystick();
	al_install_keyboard();
	al_install_mouse();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	window_state = 0;
	height = 500;
	width = 500; // later createa menu to adjust this
	title = t;
	fps = 60;
	render = true;
	run = true;

	memset(key,0,sizeof(key));

	for(int i = 0; i<10; ++i){
			//pos *=10;
			EnemyShip* en = new EnemyShip();
			if(i<=2)
				en->LoadSpriteImg(0,350);//green ship
			else if(i<=5){
				en->LoadSpriteImg(0,50); //black ship
			}
			else if(i>8){
				en->LoadSpriteImg(0,150); // blue ship
			}
			else{
				en->LoadSpriteImg(0,250); // Saucer
			}
			en->SetPosX(i*50);
			en_ship.push_back(en);

	}

	al_get_display_event_source(window);

};

Window::~Window(){


	al_destroy_display(window);
	al_destroy_event_queue(que);


}



void Window::CreateWindow(){



	window = al_create_display(width,height);
	al_set_window_title(window,title);
	run = true;

	//eve = al_create_
	//frame_clock = al_create_timer(1.0/fps);
	que = al_create_event_queue();
	al_register_event_source(que,al_get_display_event_source(this->window));
	al_register_event_source(que,al_get_keyboard_event_source());
	al_register_event_source(que,al_get_joystick_event_source());
	al_register_event_source(que,al_get_mouse_event_source());


	al_register_event_source(que,al_get_timer_event_source(main_clock->GetClock()));
	al_register_event_source(que,al_get_timer_event_source(player_fire_timer->GetClock()));
	al_register_event_source(que,al_get_timer_event_source(transition_clock->GetClock()));
	//al_get_keyboard_event_source()

	prv_time = al_get_time();

	al_start_timer(main_clock->GetClock());
	//al_start_timer(test_time->GetClock());


}


int Window::SetWindowState(int state){


	window_state = state;
	return window_state;
}


void Window::WindowLoop(){//AmoreGame** game

	while(run == true){

        if(game.gamestate == 1){
           // transition_clock->StartClock();
            //std::cout<<"TIMER Convert"<<transition_clock->GetCurrentTime();
            //en_ship[0]->Movement();
		}
		else if(game.gamestate == 4){
            transition_clock->PauseClock();
		}

		al_wait_for_event(que,&eve);

		KeyBoard();
		Mouse();




		if(render && al_is_event_queue_empty(que)){

			al_clear_to_color(al_map_rgb(0,0,0));
			//std::cout<<"Window State = " << window_state;
			//window_state = (*game)->GameState();
			current_time = al_get_time();
			delta = current_time - prv_time;
			prv_time = current_time;


			game.BulletCollision(player_one,en_ship);
			game.PlayerBodyCollision(player_one,en_ship);
			game.GameState(player_one,en_ship,delta);



		//	std::cout<<"TIMER Convert"<<ALLEGRO_BPM_TO_SECS(al_get_time());


			std::cout<<std::endl;
			//en.UpdatePlayerPosition(delta);
			al_flip_display();
			render = false;

		}



	}
	delete main_clock;

}

void Window::KeyBoard(){

	switch(eve.type){

			case ALLEGRO_EVENT_TIMER:
				// game logic will go her in the end

				if(eve.timer.source == main_clock->GetClock()){
					render = true;
                    // Methods to move AI across the screen

						if(key[ALLEGRO_KEY_RIGHT]){
						//std::cout<<"I PRESSED RIGHT";
							player_one.MoveRight(delta);
						}

						else if(key[ALLEGRO_KEY_LEFT]){
							//std::cout<<"I PRESSED LEFT";
							player_one.MoveLeft(delta);
						}

				}





				if(eve.timer.source == player_fire_timer->GetClock()){
					//fire_enabled = true;
					player_one.ActivateBullet();
					al_stop_timer(player_fire_timer->GetClock());
				}


				if(key[ALLEGRO_KEY_ENTER]){

					if(player_one.GetPlayerAmmo() < 5){

						if(player_one.GetFireStatus() == true){

							player_one.AddPlayerAmmo();
							player_one.AmmoVectorStorage(player_one.GetPlayerAmmo(),false);

							al_start_timer(player_fire_timer->GetClock());

						}
					}
					else if(player_one.GetPlayerAmmo() >= 5){
						player_one.SetPlayerAmmo(0);
						//std::cout<<"Player AMMO is suppposed to be ZERO: "<<player_one.GetPlayerAmmo()<<std::endl;
					}


				}

				for(int i = 0 ; i< ALLEGRO_KEY_MAX; i++){
					key[i] &= ~key_seen;
				}



				game.SetGameState(window_state);



				render = true;
				break;

			case ALLEGRO_EVENT_KEY_DOWN:
				key[eve.keyboard.keycode] = key_seen | key_pressed;
				if (window_state == 0){
					window_state = 1;
				}


				//player_one.Test();
			break;


			case ALLEGRO_EVENT_KEY_UP:
				key[eve.keyboard.keycode] &= ~key_pressed;
			break;




			case ALLEGRO_EVENT_DISPLAY_CLOSE:

				run = false;
				break;


	}

	//game.GameControls(eve);


}


void Window::Mouse(){


}
