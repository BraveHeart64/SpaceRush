#include"Projectile.h"



Projectile::Projectile(){
	mainbmp = al_load_bitmap("projectile.png");
	pos_x = 4000;
	pos_y = 4000;
	vel_y = 300; //300
	al_init_primitives_addon();
}


Projectile::~Projectile(){
	mainbmp = nullptr;
	sub_proj_img = nullptr;

	this->active = false;
	delete mainbmp;
	delete sub_proj_img;

};


void Projectile::SetPosX(float var){
	pos_x = var;

}


void Projectile::SetPosY(float var){

	pos_y  = var;
}

float Projectile::GetPosY(){
	return pos_y;
}

float Projectile::GetPosX(){
	return pos_x;
}


void Projectile::DeactivateBullet(){
    this->SetPosY(4000);//4000
    this->SetPosY(4000);//4000
    std::cout<<"Disable Bullet: ";
	this->active = false;
}

void Projectile::ActivateBullet(){
	this->active = true;

}

bool Projectile::GetActive(){

	return active;
}

void Projectile::LoadSubImgAsProjectile(){
	sub_proj_img = al_create_sub_bitmap(mainbmp,0,250,50,50);


}

bool Projectile::CheckCollision(){

	return true;
}

void Projectile::UpdateProjectilPosition(float delta){
	//std::cout<<"Bullet pos_y:"<<pos_y;

	if(this->active == true){
		this->pos_y -= this->vel_y * delta;
		al_draw_bitmap(sub_proj_img,GetPosX(),GetPosY()-25,1);

	}

	 else if(pos_y <0){

		this->active = false;
		SetPosY(4000);

	}


	//else{

	//	al_draw_bitmap(sub_proj_img,pos_x,pos_y-25,1);
	//}



}
