#include<iostream>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_color.h>
#include"Projectile.h"
#include<vector>

#pragma once

//static int ammo_counter = 0;

class Player : public Sprite{

	private:

		int playerammo;
		char* id;
		float vel_x, vel_y;
		float pos_x,pos_y,pos_z;
		float left,right,bottom,top;





		bool fire_enabled = false;
		ALLEGRO_TIMER* cooldown_clock;
		std::vector<Projectile*> ammo;

		ALLEGRO_BITMAP* sprite_sheet;
		ALLEGRO_BITMAP* player_img;
		ALLEGRO_BITMAP* ani[5];







	public:

		void LoadSpriteImg();
		void AmmoCreation();
		bool CheckCollision();
		std::vector<Projectile*>  AmmoGet();

		void Test();

		bool GetFireStatus();
		void ResetFireStatus(int index,bool var);
		void DeactivateBullet();
		void ActivateBullet();
		void AddPlayerAmmo();


		void SetAmmoX(int index,int num);
		void SetAmmoY(int index, int num);

		float AmmoGetPositionY(int index);
		int GetPlayerAmmo();
		void SetPlayerAmmo(int var);
		Projectile* AmmoVectorStorage(int index,bool val);
		int AmmoVectoreSize();
		void UpdateProjectile(float delta);

		void MoveRight(float delta);
		void MoveLeft(float delta);
		float GetPosX();
		float GetPosY();
		void UpdatePlayerPosition(float delta);

		void FireCannon(int index,float delta);

		Player();
		~Player();


};


