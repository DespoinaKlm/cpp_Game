#include <sgg/graphics.h>
#include <stdio.h>
#include <string>
#include "GameState.h"
#include <iostream>
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
	
	//graphics::setFont(GameState::get_Gamestate()->getAssetDir()+"OpenSans-Regular.ttf");
	graphics::setFont(GameState::get_Gamestate()->getAssetDir() + "DrawSketchDemo.ttf");
	graphics::Brush br_font;
	//br_font.fill_color[0] = 1.0f;
	//br_font.fill_color[1] = 2.7f;
	//br_font.fill_color[2] = 3.9f;
	//br_font.outline_opacity = 0.0f;
	
	//graphics::drawText(GameState::get_Gamestate()->getCanvasWidth(), GameState::get_Gamestate()->getCanvasHeight(), 1000, "kwnna", br_font);
	
	return 0;
}
