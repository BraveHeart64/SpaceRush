#include<iostream>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_color.h>
#include"Projectile.h"
#include"Timer.h"
#include<vector>

#pragma once

//static int ammo_counter = 0;

class Player : public Sprite{

	private:

		int playerammo;
		int  life;
		char* id;
		float vel_x, vel_y;
		float pos_x,pos_y,pos_z;
		float left,right,bottom,top;
		bool venerable;





		bool fire_enabled = false;
		ALLEGRO_TIMER* cooldown_clock;
		Timer* vulnerability_clock = new Timer(0.75,false); // this clock is diabled until you get hit.
		std::vector<Projectile*> ammo;

		ALLEGRO_BITMAP* sprite_sheet;
		ALLEGRO_BITMAP* player_img;
		ALLEGRO_BITMAP* ani[5];







	public:

		void	LoadSpriteImg();
		void	AmmoCreation();
		bool	CheckCollision();
		Timer*	GetVulClock();
		Timer*	SetVulClock();
		void 	VulClockTick();

		void 	Test();

		bool	GetFireStatus();
		void	ResetFireStatus(int index,bool var);
		void	DeactivateBullet();
		void	ActivateBullet();
		void	AddPlayerAmmo();
		void	Damage();
		void	SetDamage(int val);
		void	SetVulnerability(bool val);
		bool	GetVulnerability();
		void	RestTheGame();

		void 	SetAmmoX(int index,int num);
		void	SetAmmoY(int index, int num);

		float	AmmoGetPositionY(int index);
		int		GetPlayerAmmo();
		void	SetPlayerAmmo(int var);



		int		AmmoVectoreSize();
		int		GetLife();
		void	UpdateProjectile(float delta);

		void 	MoveRight(float delta);
		void 	MoveLeft(float delta);
		float	GetPosX();
		float	GetPosY();
		void	UpdatePlayerPosition(float delta);

		void	FireCannon(int index,float delta);
		Projectile* AmmoVectorStorage(int index,bool val);
		std::vector<Projectile*>  AmmoGet();

		Player();
		~Player();


};


