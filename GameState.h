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

	graphics::Brush m_brush_wasd;
	graphics::Brush m_brush_bgStart;
	graphics::Brush m_brush_pressSpace;
	graphics::Brush m_playerBrush;
	graphics::Brush m_enemyBrush;

	bool nextLevel;
	int pointerLevel;

	vector<Level*> m_levels;
public:

	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;

	static GameState* get_Gamestate();
	bool m_debugging = false;
	~GameState();

	bool game_over;
	void init();
	void draw();
	void update(float dt);
	GameState &AddIndex();
	string getAssetDir();
	string getFullAssetPath(const string& asset);
	float getCanvasWidth();
	float getCanvasHeight();
	inline int getPointerLevel() const{ return pointerLevel;}
	inline void setNextLevel(bool answer) { nextLevel = answer; }
	inline bool getNextLevel()const { return nextLevel; }
	inline void setPointerLevel(int pointerLevel) { this->pointerLevel = pointerLevel; }
	class Player * getPlayer() { return m_player; }
	class Level * getlevel() { return m_level;}
};
