#include"EnemyShip.h"




EnemyShip::EnemyShip(){
	al_init();
	al_init_image_addon();
	pos_x = 0;
	pos_y = 0;

	life = 1;
	active = true;
	reset_clock = false;
	//srand((float)time(0));
	//
	speed = (rand()%4)+1;
	//speed=speed +.5;

//	LoadSpriteImg(0,50);

}

EnemyShip::~EnemyShip(){
	//al_destroy_bitmap();
	al_destroy_bitmap(sprite_sheet);
	al_destroy_bitmap(enemy_img);
	delete active_clock;

};

void EnemyShip::TestClock(){
//	std::cout<< "test";

}

void EnemyShip::ResetPosition(){
	pos_x = 0;
	pos_y = 0;

	life = 1;
	active = true;
	reset_clock = false;
	//srand((float)time(0));
	//
	speed = (rand()%4)+1;

}


void EnemyShip::LoadSpriteImg(int img_x, int img_y){
	sprite_sheet = al_load_bitmap("atiship.png");
	enemy_img = al_create_sub_bitmap(sprite_sheet,img_x, img_y, 50,50);

	if(sprite_sheet == nullptr){
		this->~EnemyShip();
		std::cout<<"The Enemy failed to load \n";
	}
	else{
		std::cout<<"The image has loaded!"<<std::endl;
	}

	top = al_get_bitmap_height(enemy_img);
	bottom = al_get_bitmap_width(enemy_img);
	//std::cout<<"Top Data now:" <<top;
	//std::cout<<"Bottom Data, now:"<<bottom;
}



void EnemyShip::ActivateShip(bool val){
	active = val;
	al_start_timer(active_clock->GetClock());
}

bool EnemyShip::CheckCollision(){

	return true;
}

void EnemyShip::SetPosX(int pos){
	pos_x+= pos;
}

void EnemyShip::Movement(){
    pos_y+= speed;
    //std::cout<<std::endl;
	//std::cout<<speed;
    if(pos_y >500){
        pos_y = 0;
        speed = (rand()%4)+1;

    }
}

float EnemyShip::GetPosX(){
	return pos_x;
}

float EnemyShip::GetPosY(){
	return pos_y;
}

void EnemyShip::Destroyed(){
	active = false;
	this->pos_y = -3000;
	life = 0;
}

void EnemyShip::Revived(){
	life = 1;
	active = true;
}

void EnemyShip::UpdatePlayerPosition(float delta){
	if(life > 0){
		active = true;
		reset_clock = false;
		Movement();
		al_draw_bitmap(enemy_img,pos_x,pos_y,16);
	}
	else {
		active = false;
		if(reset_clock == false){
            active_clock->ResetClock();
        //    std::cout<<"Clock is reset";
          //  std::cout<<"\n";
            reset_clock = true;
            active_clock->StartClock();
         //   std::cout<<active_clock->GetCurrentTime();
        }

        if(active_clock->GetMin() >= 2 && active_clock->GetSec() >= .5){
            active = true;
            life = 1;
			pos_y = -105;
			speed = (rand()%4)+1;
			pos_x = (rand()%473)+1;
          //  std::cout<<"TEST";



            // code to reset the position will be added
        }else{

            al_draw_bitmap(enemy_img,-3000,-3000,16);
        }
        active_clock->GetCurrentTime();
       // std::cout<<active_clock->GetCurrentTime();

	}


	//live_ammo[0]->UpdateProjectilPosition(delta);

}

