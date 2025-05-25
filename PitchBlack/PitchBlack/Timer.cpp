#include"Timer.h"





Timer::Timer(float fps, bool clock_type){
	al_init();
	my_min = 0.0;
	my_sec = 0.0;
	on = false;


	if(clock_type == true){
		adj_timer = 60;
		gm_timer = al_create_timer(1.0/adj_timer);
	}
	else if(clock_type == false){
		gm_timer = al_create_timer(fps);
	//	std::cout<<"FPS: "<<fps;
	}

}

Timer::~Timer(){
	al_destroy_timer(gm_timer);


}

double Timer::GetMin(){
    return my_min;
}

double Timer::GetSec(){
    return my_sec;
}

void Timer::ResetClock(){
    my_min = 0.0;
    my_sec = 0.0;

}

void Timer::StartClock(){
    this->on = true;
}

void Timer::PauseClock(){
    this->on = false;
}

double Timer::GetCurrentTime(){
    if(on == true){
        current = al_get_time();
        if(current >=5){
            //al_stop_timer(gm_timer);
            //al_rest(5);
            current = 0;

        }

        my_sec+= 1;
        if(my_sec >=60){
            my_min+=1;
            my_sec = 0.0;
        }
	}

	return my_min;
	//return current;
}

ALLEGRO_TIMER* Timer::GetClock(){
	return this->gm_timer;
}

double Timer::GetTimer(){
	current = adj_timer;
	return current;
}
