#include<iostream>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_color.h>
#include<ctime>
#include"Timer.h"
#include"random"
#include"Projectile.h"
#include<string>
#include<vector>


#pragma once



class EnemyShip : Sprite{

	private:
		std::string enemy_name;
		float vel_x, vel_y,pos_x,pos_y;
		float speed;
		float left,right,bottom,top;
		int life;
		bool active;
		bool reset_clock;

		int rnd;
		std::vector<Projectile*> ammo;
		ALLEGRO_BITMAP* sprite_sheet;
		ALLEGRO_BITMAP* enemy_img;
		Timer* active_clock = new Timer(1,true);;
		ALLEGRO_BITMAP* ani[5];

	public:
		void SetPosX(int pos);
		float GetPosY();
		float GetPosX();
		void Movement();
		void ActivateShip(bool val);
		void Destroyed();
		void Revived();
		void ResetPosition();
		void StartActiveClock();
		void InitActiveClock();
		void LoadSpriteImg(int img_x, int img_y);
		void UpdatePlayerPosition(float delta);
		bool CheckCollision();
		void TestClock();

	public:
		EnemyShip();
		~EnemyShip();


};
