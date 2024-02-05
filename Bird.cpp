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
Bird::Bird(GameState* gs, const string& name, int health):Enemy(gs,name,health), m_filename("Bird.txt")
{
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
//----------------------------loadFileIntoVector---------------------------------
vector<string> Bird::loadFileIntoVector(const std::string& filePath)
{
    vector<std::string> fileContents;
    ifstream inputFile(filePath);
   
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line))
        {
            fileContents.push_back(m_state->getFullAssetPath(line));
            cout << m_state->getFullAssetPath(line);
        }
        inputFile.close();
    }
    else {
        cerr << "failed to open the file" << endl;
    }
    return fileContents;
}
//----------------------------update---------------------------------------------
void Bird::update(float dt)
{
    if (!dead) {
        if (reverse > 5)
        {
            m_pos_x -= speed_enemy * graphics::getDeltaTime();
        }
        else
        {
            m_pos_x += speed_enemy * graphics::getDeltaTime();
        }
   
        if (m_pos_x < -enemy_size && reverse>5)
        {
            setActive(false);
        }
        if ( m_pos_x>CANVAS_WIDTH&& reverse<=5) 
        {
            setActive(false);
        }
    }
    
    //if (m_enemy_health <= 0) {

    //    bird_enemy = loadFileGameObject("pouf");
    //    enemyDrawDeath(bird_enemy,m_pos_x,m_pos_y,m_width,m_height);
    //}
    Enemy::update(dt);
}
//----------------------------init-----------------------------------------------
void Bird::init()
{
    //Brush bird
    br_enemy_birds.fill_opacity = 1.1f;
    br_enemy_birds.outline_opacity = 0.0f;
    br_enemy_birds.texture = m_state->getFullAssetPath("bird1.png");

    reverse = rand() % 10 + 1;
    if (reverse >5) {
        m_pos_x = CANVAS_WIDTH + enemy_size * 1.1f;
    }
    else
    {
        m_pos_x =enemy_size * ( - 1)*1.1f;
    }
    
    m_pos_y = CANVAS_HEIGHT * rand() / (float)RAND_MAX ;
    
    //Animation
    bird_enemy = loadFileGameObject("bird");
    Enemy::init();
}
//----------------------------draw-----------------------------------------------
void Bird::draw()
{
    //float x = m_pos_x + m_state->m_global_offset_x;
    //float y = m_pos_y + m_state->m_global_offset_y;
    //cout << "M_state : " << m_state->m_global_offset_x << "             " << m_state->m_global_offset_y<<endl;
    if (!dead) {
        int s = int(fmodf(1000.0f - m_pos_x * 0.05f, bird_enemy.size()));
        br_enemy_birds.texture = bird_enemy[s];
        if (reverse>5)
        {
            graphics::setScale(-1.0f, 1.0f);
        }
        else {
            graphics::resetPose();
        }
        graphics::drawRect(m_pos_x, m_pos_y, enemy_size *0.8, enemy_size * 0.8, br_enemy_birds);
    
        //cout <<"Position : " << m_pos_x << "               " << m_pos_y << endl;
        //cout << "x,y : " << x << "                 " << y << endl;
        //graphics::drawRect(x, y, enemy_size / 2, enemy_size / 2, br_enemy_birds);
        graphics::resetPose();

        if (m_state->m_debugging)
        {
            debugDrawEnemy(m_pos_x, m_pos_y);
            //debugDrawEnemy(x, y);
        }
    }
    
    Enemy::draw();
}
//----------------------------debugDrawEnemy-------------------------------------
void Bird::debugDrawEnemy(float x, float y)
{
    Enemy::debugDrawEnemy(m_pos_x,m_pos_y);
}