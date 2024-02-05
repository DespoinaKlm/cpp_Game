#pragma once
#include <fstream>
#include <iostream>
#include <sgg/graphics.h>
#include "GameObject.h"
#include "GameState.h"
#include "box.h"

using namespace std;

class Blocks:public Box{
private:

	graphics::Brush m_blocks;
	graphics::Brush m_blockDebug;
	
public:
	Blocks(float x, float y, float windth, float heigh);
	Blocks();
	~Blocks();
	inline float getBlockX() {return m_pos_x;}
	inline float getBlockY() { return m_pos_x; }
	inline float getBlockW() { return m_width; }
	inline float getBlockH() { return m_height; }
	void update(float dt, float movement);
	void init() ;
	void draw() ;
};