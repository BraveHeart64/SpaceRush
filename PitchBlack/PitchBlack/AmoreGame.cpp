#include"AmoreGame.h"


AmoreGame::AmoreGame(){
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	ft = al_load_font("DSChocolade.ttf",32,0);
	score_ft = al_load_font("DSChocolade.ttf",20,0);

	//memset(key,0,sizeof(key));
	gamestate = 0;
	//player_one.LoadSpriteImg();



	if (ft == nullptr || score_ft == nullptr){
		//run = false;
		//render = false;
		std::cout<<"Font failed to load";
		this->~AmoreGame();
	}
	else{
		std::cout<<"Font has loaded into memory";
	}

	gamestate = 0;


}


AmoreGame::~AmoreGame(){
	al_destroy_font(ft);
    al_destroy_font(score_ft);
}

void AmoreGame::SetGameState(int val){
	gamestate = val;

}
bool AmoreGame::PlayerCollision(Player p, std::vector<EnemyShip*> en){

}

bool AmoreGame::OverLapping(float min_one,float max_one, float min_two, float max_two ){
	return min_two <= max_one && min_one <= max_two;

}

bool AmoreGame::BulletCollision(Player& p, std::vector<EnemyShip*>& en){

	float bullet_left;
	float bullet_right;
	float left_ship;
	float right_ship;

	float bullet_bottom;
	float bullet_top;
	float ship_bottom;
	float ship_top;


	for(auto* bullet :p.AmmoGet()){


		float col_width = 10.0;
		float col_height = 15.0;
		const float offsetx = (50.0-col_width)/2.0;
		const float offsety = (50.0-col_height)/2.0;
		bool checkhit;

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
                score+=5;
                bullet->DeactivateBullet();

                std::cout<<"The bullet has hit its target"<<std::endl;
				return true;
		 }


		}

	}
	return false;


}


int AmoreGame::GameState(Player p,std::vector<EnemyShip*> en,float delta){
    string data =  to_string(score);
    char const *datacon = data.c_str();

	switch(gamestate){
		case 0:	// main menu
				al_draw_text(ft,al_map_rgb(255,255,255),245,0,ALLEGRO_ALIGN_CENTER,"PitchBlack");
				al_draw_text(ft,al_map_rgb(255,255,255),245,50,ALLEGRO_ALIGN_CENTER,"Press Any key to Start the game!");
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


			break;

	//	case 1: // game setup



		//	break;


		case 1://  Game Start

				std::cout<<p.GetPlayerAmmo();
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
			break;

	}

		return gamestate;

}
