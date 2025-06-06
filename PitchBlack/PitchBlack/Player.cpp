#include"Sprite.h"
#include"Player.h"



Player::Player(){
	sprite_sheet = nullptr;
	al_init();
	al_init_image_addon();
	pos_x = 250;
	pos_y = 450;
	vel_x = 140;
	vel_y = 140;

	LoadSpriteImg();
	life = 3;
	playerammo = 0;//-1
	fire_enabled = true;
	venerable = true;


	for(int i = 0; i<6; ++i){
		ammo.push_back(new Projectile);
		ammo[i]->LoadSubImgAsProjectile();
	}



}

Player::~Player(){

	sprite_sheet = nullptr;
	if(sprite_sheet == nullptr){
		delete this->sprite_sheet;
	}
	else{
		std::cout<<"THE FILE HAS BEEN DELETED ALREADY";
	}
	player_img = nullptr;
	al_destroy_bitmap(player_img);




}
void Player::RestTheGame(){

	pos_x = 250;
	pos_y = 450;
	vel_x = 140;
	vel_y = 140;
	life = 3;


	playerammo = 0;//-1
	fire_enabled = true;
	venerable = true;
	ammo[0]->SetPosY(9000);
	ammo[1]->SetPosY(9000);
	ammo[2]->SetPosY(9000);
	ammo[3]->SetPosY(9000);
	ammo[4]->SetPosY(9000);
	ammo[5]->SetPosY(9000);



}

void Player::Test(){

	//std::cout<<"TEST SIZE OF AMMO"<<ammo.size();


//	al_rest(1);
}

void Player::SetDamage(int val){
	this->life = val;
}
int Player::GetLife(){
	return life;
}

void Player::SetVulnerability(bool val){

	venerable = val;
}

bool Player::GetVulnerability(){
	return venerable;
}

void Player::VulClockTick(){

	double tick = vulnerability_clock->GetCurrentTime();
	if(tick >= 15){
		vulnerability_clock->ResetClock();
		vulnerability_clock->PauseClock();
		venerable = true;
	}
	//std::cout<<"Tick: "<<tick;
}

void Player::Damage(){
	life-=1;
	vulnerability_clock->StartClock();
	std::cout<<"\n";
	std::cout<<"Life: "<<life;
}

void Player::AddPlayerAmmo(){
	playerammo+= 1;
}

int Player::GetPlayerAmmo(){
	return playerammo;
}

void Player::SetPlayerAmmo(int var){
	playerammo = var;
}

Projectile* Player::AmmoVectorStorage(int index,bool val){
	ammo[index]->ActivateBullet();
	ammo[index]->SetPosX(GetPosX());
	ammo[index]->SetPosY(GetPosY());

	//ammo[index]->DeactivateBullet();

	fire_enabled = false;
	return ammo[index];

}

std::vector<Projectile*>  Player::AmmoGet(){
	return ammo;
}

void Player::SetAmmoX(int index, int num){
	ammo[index]->SetPosX(num);
}
void Player::SetAmmoY(int index, int num){
	ammo[index]->SetPosY(num);
}


int Player::AmmoVectoreSize(){
	return ammo.size();
}

bool Player::GetFireStatus(){
	return fire_enabled;
}

void Player::DeactivateBullet(){
	//ammo->DeactivateBullet();
	fire_enabled = false;
}

float Player::AmmoGetPositionY(int index){
	return ammo[index]->GetPosY();
}

void Player::ActivateBullet(){
	//ammo->ActivateBullet();
	fire_enabled = true;
}


void Player::LoadSpriteImg(){
	sprite_sheet = al_load_bitmap("atiship.png");
	player_img = al_create_sub_bitmap(sprite_sheet,0, 450, 50,50);
	if(sprite_sheet == nullptr){
		this->~Player();
		std::cout<<"The Player failed to load \n";
	}
	else{
		std::cout<<"The image has loaded!"<<std::endl;
	}

}

void Player::MoveRight( float delta){
//	std::cout<<"DELTA"<<delta;
	pos_x+= vel_x *delta;
	if(pos_x >=470)
        pos_x-=vel_x * delta;

}

void Player::MoveLeft(float delta){
	//std::cout<<"DELTA"<<delta;
	pos_x-= vel_x * delta;
	if(pos_x <=-14)
        pos_x+=vel_x * delta;


}

float Player::GetPosX(){
	return pos_x;
}

float Player::GetPosY(){
	return pos_y;
}

void Player::FireCannon(int index,float delta){
//	collision boxes fire as well we need to see these boxes

	ammo[index]->UpdateProjectilPosition(delta);

}

void KillBullet(){
	// destroy the projectile when it goes off screen.

}

bool Player::CheckCollision(){

	return true;
}

void Player::UpdatePlayerPosition(float delta){
	al_draw_bitmap(player_img,pos_x,pos_y,16);


}
