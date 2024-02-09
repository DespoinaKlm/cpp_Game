#include <sgg/graphics.h>
#include <stdio.h>
#include <string>
#include "GameState.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

//------------------------------------init()--------------------------------------------------------
void init() {
	GameState::get_Gamestate()->init();
}

//------------------------------------draw()--------------------------------------------------------
void draw() {
	GameState::get_Gamestate()->draw();
}

//------------------------------------update()------------------------------------------------------
void update(float dt) {
	GameState::get_Gamestate()->update(dt);
}

//------------------------------------main()------------------------------------------------------
int main(int argc, char** argv) {

	srand(time(NULL));
	graphics::createWindow(1200, 800, "Level1");

	GameState::get_Gamestate()->init();

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(GameState::get_Gamestate()->getCanvasWidth(), GameState::get_Gamestate()->getCanvasHeight());
	
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_STRETCH);
	
	graphics::startMessageLoop();
	graphics::destroyWindow();
	
	return 0;
}
