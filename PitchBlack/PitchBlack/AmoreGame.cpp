#include"AmoreGame.h"


AmoreGame::AmoreGame(){
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(16);

	ft = al_load_font("DSChocolade.ttf",32,0);
	score_ft = al_load_font("DSChocolade.ttf",20,0);

	main_song = al_load_sample("main.ogg");
	laser = al_load_sample("laser.ogg");
	en_beam = al_load_sample("cannon.ogg");
	explosion = al_load_sample("explosion.ogg");

	if (ft == nullptr || score_ft == nullptr){
		//run = false;
		//render = false;
		std::cout<<"Font failed to load";
		this->~AmoreGame();
	}
	else{
		std::cout<<"Font has loaded into memory"<<endl;
	}


	if(main_song == nullptr){
		std::cout<<"Song failed to load"<<endl;

	}
	else{

		al_play_sample(main_song,1.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
	}




	if(explosion == nullptr){
		std::cout<<"Explosion Sound has failed to load"<<endl;
	}
	else{
		std::cout<<"Explosion Sound has been loaded"<<endl;
	}



	gamestate = 0;


}


AmoreGame::~AmoreGame(){
	al_destroy_font(ft);
    al_destroy_font(score_ft);
    al_destroy_sample(main_song);
    al_destroy_sample(laser);
    al_destroy_sample(en_beam);
    al_destroy_sample(explosion);

}

void AmoreGame::SetGameState(int val){
	gamestate = val;

}
bool AmoreGame::PlayerBodyCollision(Player& p, std::vector<EnemyShip*>& en){

	float ship_left;
	float ship_right;
	float ship_bottom;
	float ship_top;

	float player_left;
	float player_right;
	float player_bottom;
	float player_top;

	for(auto* en_ship: en){
		float col_width = 10.0;
		float col_height = 15.0;
		const float offsetx = (50.0-col_width)/2.0;
		const float offsety = (50.0-col_height)/2.0;


		ship_left =  en_ship->GetPosX()+offsetx;
		ship_right = ship_left +col_width; // 50 stand for size later make it a variable it for x size
		ship_bottom = en_ship->GetPosY()+offsety;
		ship_top = ship_bottom +col_height; //50


		player_left = p.GetPosX()+offsetx;
		player_right  = player_left+col_width;
		player_bottom = p.GetPosY()+offsety;
		player_top = player_bottom+col_height;

		if(p.GetVulnerability() == true){
			if( OverLapping(player_left,player_right,ship_left,ship_right) &&
				OverLapping(player_bottom,player_top,ship_bottom,ship_top)){
				//en_ship->Destroyed();
               // enemy->Destroyed();
                //score+=5;
                //bullet->DeactivateBullet();

                std::cout<<"Kamikazi Attack!"<<std::endl;
                p.Damage();
                en_ship->Destroyed();
                p.SetVulnerability(false);
                PlayExplosion();

				return true;
			}
		}
		else{
			p.VulClockTick();
				if(p.GetLife() <= 0){
					gamestate = 7;
				}
		}


	}
	return false;
}

bool AmoreGame::OverLapping(float min_one,float max_one, float min_two, float max_two ){
	return min_two <= max_one && min_one <= max_two;

}

bool AmoreGame::BulletCollision(Player& p, std::vector<EnemyShip*>& en){

	float bullet_left;
	float bullet_right;
	float bullet_bottom;
	float bullet_top;

	float left_ship;
	float right_ship;
	float ship_bottom;
	float ship_top;


	for(auto* bullet :p.AmmoGet()){


		float col_width = 10.0;
		float col_height = 15.0;
		const float offsetx = (50.0-col_width)/2.0;
		const float offsety = (50.0-col_height)/2.0;
		//bool checkhit;

		bullet_left =  bullet->GetPosX()+offsetx;
		bullet_right = bullet_left +col_width; // 50 stand for size later make it a variable it for x size
		bullet_bottom = bullet->GetPosY()+offsety;
		bullet_top = bullet_bottom +col_height; //50




		 for(auto* enemy: en){
			left_ship = enemy->GetPosX()+offsetx;
			right_ship = left_ship+col_width;// 50


			ship_bottom = enemy->GetPosY()+offsety;
			ship_top = ship_bottom+col_height; //50

			if( OverLapping(bullet_left,bullet_right,left_ship,right_ship) &&
			OverLapping(bullet_bottom,bullet_top,ship_bottom,ship_top)){
                enemy->Destroyed();
                PlayExplosion();
                score+=5;
                bullet->DeactivateBullet();

             //   std::cout<<"The bullet has hit its target"<<std::endl;
				return true;
		 }


		}

	}
	return false;


}

void AmoreGame::PlayPlayerLaser(){

	//laser = al_load_sample("laser.ogg");
	if(laser  == nullptr){
		std::cout<<"Laser Sound has failed to load"<<endl;
		return;
	}
	else{
		std::cout<<"The Laser sound has been loaded"<<endl;
		al_play_sample(laser,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

	}

}

void AmoreGame::PlayEnemyLaster(){

	if(en_beam  == nullptr){
		std::cout<<"Enemy Laser Sound has failed to load"<<endl;
		return;
	}
	else{
		al_play_sample(en_beam,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
	}

}

void AmoreGame::PlayExplosion(){
	al_play_sample(explosion,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
}

int AmoreGame::GameState(Player p,std::vector<EnemyShip*> en,float delta){
    string data =  to_string(score);
    char const *datacon = data.c_str();

	switch(gamestate){
		case 0:	// main menu
				al_draw_text(ft,al_map_rgb(255,255,255),245,0,ALLEGRO_ALIGN_CENTER,"PitchBlack");
				al_draw_text(ft,al_map_rgb(255,255,255),245,50,ALLEGRO_ALIGN_CENTER,"Press q to quit the game!");
				al_draw_text(ft,al_map_rgb(255,255,255),245,90,ALLEGRO_ALIGN_CENTER,"Press Any key to Start the game!");

				en[0]->ActivateShip(false);
				en[1]->ActivateShip(false);
				en[2]->ActivateShip(false);
				en[3]->ActivateShip(false);
				en[4]->ActivateShip(false);
				en[5]->ActivateShip(false);
				en[6]->ActivateShip(false);
				en[7]->ActivateShip(false);
				en[8]->ActivateShip(false);
				en[9]->ActivateShip(false);
				/*

				en[0]->ActivateShip(true);
				en[0]->TestClock();

				*/

				//al_play_sample(main_song, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

			break;

	//	case 1: // game setup



		//	break;


		case 1://  Game Start

				//std::cout<<p.GetPlayerAmmo();
				if(p.GetPlayerAmmo() >= 5){
						p.SetPlayerAmmo(0);
				}

				for(int i = 0; i<p.AmmoVectoreSize(); ++i){
						p.FireCannon(i,delta);

				}

				p.UpdatePlayerPosition(delta);
				for(int i =0; i<en.size(); ++i){
					en[i]->UpdatePlayerPosition(delta);
                }

                al_draw_text(score_ft,al_map_rgb(255,255,255),50,430,ALLEGRO_ALIGN_CENTER,"Score:");
                al_draw_text(score_ft,al_map_rgb(255,255,255),100,430,ALLEGRO_ALIGN_CENTER,datacon);

			break;



		case 3: // main game scene

			break;

		case 4:		// pause

			break;

		case 5:	// cut scene

			break;

		case 6: // player die show blow up animation

			break;

		case 7: // show game over screen
				al_draw_text(ft,al_map_rgb(255,255,255),245,0,ALLEGRO_ALIGN_CENTER,"Game Over");
				al_draw_text(ft,al_map_rgb(255,255,255),245,50,ALLEGRO_ALIGN_CENTER,"Press enter to Play Again!");
				p.RestTheGame();


				en[0]->ResetPosition();
				en[1]->ResetPosition();
				en[1]->SetPosX(50);
				en[2]->ResetPosition();
				en[2]->SetPosX(100);
				en[3]->ResetPosition();
				en[3]->SetPosX(150);
				en[4]->ResetPosition();
				en[4]->SetPosX(200);
				en[5]->ResetPosition();
				en[5]->SetPosX(250);
				en[6]->ResetPosition();
				en[6]->SetPosX(300);
				en[7]->ResetPosition();
				en[7]->SetPosX(350);
				en[8]->ResetPosition();
				en[8]->SetPosX(400);
				en[9]->ResetPosition();
				score=0;



			break;

	}

		return gamestate;

}
