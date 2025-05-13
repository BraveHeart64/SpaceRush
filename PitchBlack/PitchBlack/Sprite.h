
#include<iostream>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_color.h>
#pragma once

class Sprite{

	private:
		int width, hight;
		char* id;
		float vel_x, vel_y;
		float pos_x,pos_y,pos_z;


	public:

		void LoadSpriteImg();
		virtual bool CheckCollision() = 0;




};
