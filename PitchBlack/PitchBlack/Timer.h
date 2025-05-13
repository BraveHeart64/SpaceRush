#include<iostream>
#include<allegro5/allegro.h>



#pragma once


class Timer{


	ALLEGRO_TIMER* gm_timer;
	double current;
	float adj_timer;
	double my_sec, my_min;
	bool on;


	public:

		double GetTimer();

		void StartClock();
		void PauseClock();
		double GetMin();
        double GetSec();
		ALLEGRO_TIMER* GetClock();
		void ResetClock();
		double GetCurrentTime();
		Timer(float fps, bool clock_type);
		~Timer();

};
