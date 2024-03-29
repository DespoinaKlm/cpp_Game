#pragma once
#include "Bird.h"
#include <sgg/graphics.h>
#include "GameObject.h"
#include "GameState.h"
#include "Level.h"

using namespace std;
//----------------------------Constructor-------------------------------------
Bird::Bird(GameState* gs, float px, float py, const string& name, int health):Enemy(gs,name,health)
{
    m_pos_x = px;
    m_pos_y = py;
    m_width = enemy_size;
    m_height = enemy_size;
    dead = false;
    speed_enemy = 1.5;
    m_active = true;
    init();
    
}
//----------------------------Destructor-------------------------------------
Bird::~Bird()
{
}
//----------------------------update---------------------------------------------
void Bird::update(float dt)
{
    if (!dead) {
        if (firstposition<0)
        {
            //from left to right
            m_pos_x += speed_enemy;
            
        }
        else
        {
            //from right to left
            m_pos_x -= speed_enemy;
        }
        //pros dejia
        if (m_pos_x < -2600 )
        {
            m_active=false;
        }
        if (m_pos_x >5200)
        {
            m_active =false;
        }
    }
    Enemy::update(dt);

}
//----------------------------init-----------------------------------------------
void Bird::init()
{
    //Brush bird
    br_enemy.fill_opacity = 1.1f;
    br_enemy.outline_opacity = 0.0f;
    br_enemy.texture = m_state->getFullAssetPath("bird1.png");

    firstposition = m_pos_x;
    bird_enemy = loadFileGameObject("bird");
    
    Enemy::init();
}
//----------------------------draw-----------------------------------------------
void Bird::draw()
{
    //not dead
    if (!dead) {
        float x = m_pos_x + m_state->m_global_offset_x;
        float y = m_pos_y + m_state->m_global_offset_y;
        int s = (int)fmod(1000.0f - m_pos_x * 0.025f, bird_enemy.size());
        br_enemy.texture = bird_enemy[s];
        //draw right direction
        if (firstposition > 0)
        {
            graphics::setScale(-1.0f, 1.0f);
        }
        else
        {
            graphics::resetPose();
        }
        graphics::drawRect(x, y, m_width, m_height, br_enemy);

        if (m_state->m_debugging)
        {
            debugDrawEnemy(x, y);
        }
    }
    Enemy::draw();
   
}
//----------------------------debugDrawEnemy-------------------------------------
void Bird::debugDrawEnemy(float x, float y)
{
    Enemy::debugDrawEnemy(x,y);
}