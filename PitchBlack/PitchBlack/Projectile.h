#include"Sprite.h"
#include<iostream>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_color.h>
#pragma once


class Projectile: public Sprite{

	private:
		char* id;
		float pos_x, pos_y,pos_z;
		float vel_x, vel_y;
		float left,right,bottom, top;




		bool active;
		ALLEGRO_BITMAP* mainbmp;
		ALLEGRO_BITMAP* sub_proj_img; //


	public:

		void LoadSubImgAsProjectile();
		bool CheckCollision();
		void UpdateProjectilPosition(float delta);
		void SetPosX(float var);
		void SetPosY(float var);
		float GetPosY();
		float GetPosX();
		bool GetActive();
		//void Fired(bool active);
		void DeactivateBullet();
		void ActivateBullet();

		Projectile();
		~Projectile();
};
