#pragma once
#include <stdio.h>
#include <tchar.h>
#include <sgg/graphics.h>
#include "GameState.h"
#include "Level.h"
#include "Player.h"
#include <thread>
#include <chrono>
#include <cstdio>
#include "Enemy.h"
#include "Rock.h"
#include "Bird.h"
#include "util.h"

using namespace std;
//-----------------------------------Constructor----------------------------------------------------
GameState::GameState()
{
    nextLevel = false;
    game_over = false;
    pointerLevel = 0;
}
//------------------------------------init()--------------------------------------------------------
void GameState::init()
{
    //brush background
    m_brush_bgStart.fill_opacity = 0.8f;
    m_brush_bgStart.outline_opacity = 0.0f;
    m_brush_bgStart.texture = m_asset_path + "background.png";

    //player brush 
    m_playerBrush.fill_opacity = 1.1f;
    m_playerBrush.outline_opacity = 0.0f;
    m_playerBrush.texture = getFullAssetPath("playerStanding1.png");

    //enemy brush
    m_enemyBrush.fill_opacity = 1.1f;
    m_enemyBrush.outline_opacity = 0.0f;
    m_enemyBrush.texture = getFullAssetPath("iceBlobDie.png");

    //movement
    m_brush_wasd.fill_opacity = 0.8f;
    m_brush_wasd.outline_opacity = 0.0f;
    m_brush_wasd.texture = m_asset_path + "movement.png";
    
    //press space
    m_brush_pressSpace.fill_opacity = 0.8f;
    m_brush_pressSpace.outline_opacity = 0.0f;
    m_brush_pressSpace.texture = m_asset_path + "PressSpace.png";

    //player init
     m_player = new Player(m_unique_state, "The-man", 1000);
     m_player->init();
     
     /*
     //first level init
     m_level = new Level(m_unique_state, "level-1" );
     m_level->init();
     m_levels.push_back(m_level);
   
     
      //second level init
     m_level = new Level(m_unique_state,level_map2 , "level-2", m_levels[0]->getScore());
     m_level->init();
     m_levels.push_back(m_level);

     //third level init
     m_level = new Level(m_unique_state, level_map3,"level-3", m_levels[1]->getScore());
     m_level->init();
     m_levels.push_back(m_level);
     */
    
    
     graphics::preloadBitmaps(getAssetDir());
     graphics::setFont(m_asset_path + "OpenSans-Regular.ttf");
     graphics::playMusic(getFullAssetPath("TheRebelPath.wav"), 0.5f, true, 4000);

}
//------------------------------------draw()--------------------------------------------------------
void GameState::draw()
{
    
    if (pointerLevel == 0)
    {
        // purple background 
        SETCOLOR(m_brush_bgStart.fill_color, 0.8f, 0.2f, 0.8f);
        graphics::drawRect(m_canvas_width / 2.0f, m_canvas_height / 2.0f,m_canvas_width * 1.5f, m_canvas_height * 1.0f,m_brush_bgStart);

        // Press Space to start 
        graphics::drawRect(m_canvas_width / 2.0f, m_canvas_height / 2.0f, 600.0f , 900.0f,m_brush_pressSpace);
    }
    if(pointerLevel == 1)
    {
        //blue background
        SETCOLOR(m_brush_bgStart.fill_color, 0.1f, 0.6f, 0.8f); 
        graphics::drawRect(m_canvas_width / 2.0f, m_canvas_height / 2.0f, m_canvas_width * 1.5f, m_canvas_height * 1.0f, m_brush_bgStart);

        //wasd
        graphics::drawRect(m_canvas_width / 2.0f, m_canvas_height / 2.0f, 700.0f, 1000.0f, m_brush_wasd);

        // Press Space to start 
        graphics::drawRect(m_canvas_width / 2.0f, m_canvas_height / 2.0f-600, 600.0f, 900.0f, m_brush_pressSpace);
    }
    if(pointerLevel == 2)
    {
        if (nextLevel)
        {
            nextLevel = false;
            cout << "was here 1" << endl;
        }
        if (!m_level)
        {
            return;
        }
        m_levels[0]->draw();
        
    }
    if(pointerLevel == 3) {
        if (nextLevel)
        {
            nextLevel = false;
            cout << "was here 2" << endl;
        }
        if (!m_level)
        {
            return;
        }

        m_levels[1]->draw();
    }
    if(pointerLevel == 4)
    {
        if (nextLevel)
        {
            cout << "was here 3" << endl;
            nextLevel = false;
        }
 
        m_levels[2]->draw();
    }
    if (pointerLevel==5)
    {
        //you won background
        m_brush_bgStart.texture = m_asset_path + "YouWon.png";
        graphics::drawRect(m_canvas_width / 2.0f, m_canvas_height / 2.0f, m_canvas_width * 1.5f, m_canvas_height * 1.0f, m_brush_bgStart);

        //player
        graphics::drawRect(m_canvas_width / 2.0f - 300, m_canvas_height / 2.0f + 270, 800, 800, m_playerBrush);
        //enemy
        graphics::drawRect(m_canvas_width / 2.0f + 300, m_canvas_height / 2.0f + 270, 500, 500, m_enemyBrush);
    }
    if (pointerLevel == 6)
    {
        if (game_over)
        {
            //Game over
            m_brush_bgStart.texture = m_asset_path + "GameOver.png";
            graphics::drawRect(m_canvas_width / 2.0f, m_canvas_height / 2.0f,m_canvas_width * 1.5f, m_canvas_height * 1.0f, m_brush_bgStart);

            //player
            m_playerBrush.texture = getFullAssetPath("playerDie5.png");
            graphics::drawRect(m_canvas_width / 2.0f + 300, m_canvas_height / 2.0f+270, 800, 800, m_playerBrush);

            //enemy
            m_enemyBrush.texture = getFullAssetPath("iceBlobAttack2.png");
            graphics::drawRect(m_canvas_width / 2.0f - 300, m_canvas_height / 2.0f+270, 500, 500, m_enemyBrush);
        }
    }
}
//------------------------------------update()------------------------------------------------------
void GameState::update(float dt)
{
    if (dt > 500) {
        return;
    }

    float sleep_time = max(0.0f, 17.0f - dt);

    if (sleep_time > 0.0f)
    {
        std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));
    }

    m_brush_pressSpace.fill_opacity = 0.4f + 0.4f * cos(graphics::getGlobalTime() / 200.0f); // "Press space to start" image blinks 

    float delta_time = dt / 1000.0f;
   
   if (pointerLevel == 0)
   {
        if (graphics::getKeyState(graphics::SCANCODE_SPACE)) 
        {
            nextLevel = true;
            AddIndex();
        }
        
   }
   if (pointerLevel == 1)
   {
       nextLevel = false;
       if (graphics::getKeyState(graphics::SCANCODE_SPACE))
       {
           nextLevel = true;
           AddIndex();
       }
       
   }
   if (pointerLevel == 2|| pointerLevel == 3 || pointerLevel == 4)
   {
       
       if (pointerLevel == 2) {
           if (nextLevel) {
               cout << "pointer " << pointerLevel << endl;
               m_player->init();
               m_level = new Level(m_unique_state, "level-1");
               m_level->init();
               m_levels.push_back(m_level);
               nextLevel = false;

           }
           m_levels[0]->update(dt);
       }
       
       if (pointerLevel == 3) {
           if (nextLevel) {
               cout << "pointer " << pointerLevel << endl;
               m_player->init();
               m_level = new Level(m_unique_state, "level-2", m_levels[0]->getScore());
               m_level->init();
               m_levels.push_back(m_level);
               nextLevel = false;
           }
           m_levels[1]->update(dt);
       }
       if (pointerLevel == 4) {
           if (nextLevel) {
               cout << "pointer " << pointerLevel << endl;
               m_player->init();
               m_level = new Level(m_unique_state, "level-3", m_levels[1]->getScore());
               m_level->init();
               m_levels.push_back(m_level);
               nextLevel = false;
           }
           m_levels[2]->update(dt);
       }
        if (!m_level)
        {
           return;
        }

        m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
   }
}
//------------------------------------get_Gamestate()-----------------------------------------------
GameState* GameState::get_Gamestate()
{
    if (m_unique_state == nullptr) {
        m_unique_state = new GameState();
    }
    return m_unique_state;
}
//------------------------------------Destructor----------------------------------------------------
GameState::~GameState()
{
    if (m_player) {
        delete m_player;
    }

    for (auto& levels : m_levels) {
        delete levels;
    }
    delete m_level;

}
//------------------------------------getAssetDir()-------------------------------------------------
string GameState::getAssetDir()
{
    return m_asset_path;
}
//------------------------------------getFullAssetPath()--------------------------------------------
string GameState::getFullAssetPath(const string& asset)
{
    return m_asset_path + asset;
}
//------------------------------------getCanvasWidth()----------------------------------------------
float GameState::getCanvasWidth()
{
    return m_canvas_width;
}
//------------------------------------getCanvasHeight()---------------------------------------------
float GameState::getCanvasHeight()
{
    return m_canvas_height;
}
//------------------------------------AddIndex()----------------------------------------------------
GameState& GameState::AddIndex()
{
    this->pointerLevel++;
    return *this;
}
//--------------------------------------------------------------------------------------------------
GameState* GameState::m_unique_state = nullptr;