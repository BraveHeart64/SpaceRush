#include<iostream>
#include"../../AmoreEngine/AmoreEngine.h"
#include"AmoreGame.h"

using namespace std;

//$39.23 Get from dad

int main(int argc, char **args){
	char* title = "PitchBlack";

	Window gamewindow(title);
	gamewindow.CreateWindow();
	gamewindow.WindowLoop();


	return 0;
}
