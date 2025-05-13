//#include"arcadeheaders.h"
#include<iostream>

#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_color.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_native_dialog.h>
#include"../PitchBlack/PitchBlack/AmoreGame.h"

#include"../PitchBlack/PitchBlack/Player.h"
#include"../PitchBlack/PitchBlack/EnemyShip.h"
#include"../PitchBlack/PitchBlack/Timer.h"

#define key_seen 1
#define key_pressed 2
#pragma once

class Window{
	private:
		int width,height;
		char* title;
		float fps;
		int window_state;
		bool run,render;

		double current_time;
		float prv_time, delta;
		ALLEGRO_DISPLAY* window = nullptr;
		ALLEGRO_EVENT eve;
		ALLEGRO_EVENT_QUEUE* que;
		//ALLEGRO_TIMER* frame_clock;
		Timer* main_clock = new Timer(60,true);
		Timer* player_fire_timer = new Timer(0.75,false);
		Timer* transition_clock = new Timer(5,false);
		AmoreGame game;
		Player player_one;
		std::vector<EnemyShip*> en_ship;
		EnemyShip* en;
		unsigned char key[ALLEGRO_KEY_MAX];



	public:

		void GameLogic();
		int SetWindowState(int state);
		void CreateWindow();
		void KeyBoard();
		//void WindowLoop(AmoreGame** game);
		void WindowLoop();
		void Mouse();


		Window(char* t); // sets up keyboard, and and display source connections
		~Window();
};
