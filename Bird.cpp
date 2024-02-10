#pragma once
#include "Bird.h"
#include <sgg/graphics.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring> 
#include <cerrno> 
#include "GameState.h"
#include "GameObject.h"
#include <vector>
#include <string>
#include <filesystem>

using namespace std;
//----------------------------Constructor-------------------------------------
Bird::Bird(GameState* gs, float px, float py, const string& name, int health):Enemy(gs,name,health)
{
    m_pos_x = px;
    m_pos_y = py;
    m_width = enemy_size;
    m_height = enemy_size;
    dead = false;
    //cout << dead;
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
        if (m_pos_y==4430)
        {
            //dejia
            m_pos_x += speed_enemy /** graphics::getDeltaTime()*/;
            
        }
        else
        {
            //aristera
            m_pos_x -= speed_enemy /** graphics::getDeltaTime()*/;
        }
        //pros dejia
        if (m_pos_x < -2600 )
        {
            
            setActive(false);
        }
        if ( m_pos_x>3600 )
        {
            setActive(false);
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
    
    bird_enemy = loadFileGameObject("bird");
    Enemy::init();
}
//----------------------------draw-----------------------------------------------
void Bird::draw()
{
    
    if (!dead) {
        float x = m_pos_x + m_state->m_global_offset_x;
        float y = m_pos_y + m_state->m_global_offset_y;
        int s = (int)fmod(1000.0f - m_pos_x * 0.025f, bird_enemy.size());
        br_enemy.texture = bird_enemy[s];
        if (m_pos_y != 4430) {
            graphics::setScale(-1.0f, 1.0f);
        }
        if (m_pos_y == 4430)
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