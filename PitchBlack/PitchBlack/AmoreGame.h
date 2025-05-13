#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro.h>
#include"EnemyShip.h"
#include"Sprite.h"
#include"Player.h"
#include"Projectile.h"

#include<vector>
#include<iostream>
//#include"../../AmoreEngine/AmoreEngine.cpp"
#define key_seen 1
#define key_pressed 2
#pragma once


class AmoreGame  {

	private:

		ALLEGRO_FONT* ft;
		bool fire_enabled;
		Player player_one;

		unsigned char key[ALLEGRO_KEY_MAX];


	protected:


	public:

		int gamestate;
		int GameState(Player p,std::vector<EnemyShip*> en ,float delta);
		bool PlayerCollision(Player p, std::vector<EnemyShip*> en);
		bool BulletCollision(Player& p, std::vector<EnemyShip*>& en);
		bool OverLapping(float min_one,float max_one, float min_two, float max_two );

		void SetGameState(int val);
		ALLEGRO_TIMER* CoolOff();


		AmoreGame();
		~AmoreGame();

};
