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

	graphics::Brush m_brush_bg;
	graphics::Brush m_brush_wasd;
	graphics::Brush m_brush_bgStart;
	graphics::Brush m_brush_pressSpace;
	graphics::Brush m_brush_exit;

	float m_wasd_pos_x;
	float m_wasd_pos_y;
	float m_wasd_size_x;
	float m_wasd_size_y = 0.2f;

	// position of "Press Space to start"
	float m_pressSpace_pos_x;
	float m_pressSpace_pos_y;
	float m_pressSpace_size_x;
	float m_pressSpace_size_y;

	// position of exit button
	float m_exit_pos_x;
	float m_exit_pos_y;
	float m_exit_size_x;
	float m_exit_size_y;


	bool pressed_space;
	bool game_over;
	//next level
	int pointerLevel=1;
	vector<Level*> m_levels;

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
	inline int getPointerLevel() { return pointerLevel; }
	inline void setPointerLevel(int i) { pointerLevel = i; }
	class Player * getPlayer() { return m_player; }
	class Level * getlevel() { return m_level;}
};
