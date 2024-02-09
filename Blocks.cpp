#include "blocks.h"
#include <sgg/graphics.h>
#include "GameState.h"
#include "box.h"

Blocks::Blocks(float x, float y, float windth, float height):Box(x,y,windth,height)
{
	m_pos_x = x;
	m_pos_y = y;
	m_width = windth;
	m_height = height;
}

Blocks::Blocks() :Box()
{
}

Blocks::~Blocks()
{

}

void Blocks::update(float dt,float movement)
{
	
}

void Blocks::init()
{
}

void Blocks::draw()
{
}


