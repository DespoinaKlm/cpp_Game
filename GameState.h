#pragma once
#include "sgg/graphics.h"
#include <string>

#define CANVAS_WIDTH 1200
#define CANVAS_HEIGHT 1800

using namespace std;

class GameState{

private:
	string m_asset_path = "assets\\";
	float m_canvas_width = CANVAS_WIDTH;
	float m_canvas_height = CANVAS_HEIGHT;
	
	static GameState* m_unique_state;
	GameState();

	class Player * m_player = 0;
	class Level * m_level = 0;
	class Rock * m_enemy = 0;
	class Bird * m_enemy_bird = 0;

public:

	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;

	static GameState* get_Gamestate();
	bool m_debugging = false;
	~GameState();

	void init();
	void draw();
	void update(float dt);
	
	string getAssetDir();
	string getFullAssetPath(const string& asset);
	float getCanvasWidth();
	float getCanvasHeight();

	class Player * getPlayer() { return m_player; }
	class Level * getlevel() { return m_level;}
	class Rock * getEnemy(){return m_enemy; }
	class Bird * getEnemyBird() { return m_enemy_bird; }
};
