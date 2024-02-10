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
using namespace std;
//-----------------------------------Constructor----------------------------------------------------
GameState::GameState()
{
    nextLevel = false;
}
//------------------------------------init()--------------------------------------------------------
void GameState::init()
{
    cout << "pointerLevel " << pointerLevel << endl;
    if (pointerLevel == 1)
    {
        m_player = new Player(m_unique_state, "The-man", 1000);
        m_player->init();
        m_level = new Level(m_unique_state,level_map1, "level-1" );
        m_level->init();
        m_levels.push_back(m_level);
    }
    else if (pointerLevel == 2)
    {
        m_player->init();
        m_level = new Level(m_unique_state,level_map2 , "level-2", m_levels[0]->getScore());
        m_level->init();
        m_levels.push_back(m_level);
    }
    else if (pointerLevel == 3)
    {
        m_player->init();
        m_level = new Level(m_unique_state, level_map3,"level-3", m_levels[1]->getScore());
        m_level->init();
        m_levels.push_back(m_level);
    }
    graphics::preloadBitmaps(getAssetDir());
    graphics::setFont(m_asset_path + "OpenSans-Regular.ttf");
    graphics::playMusic(getFullAssetPath("TheRebelPath.wav"), 0.5f, true, 4000);

}
//------------------------------------draw()--------------------------------------------------------
void GameState::draw()
{
    if (!m_level) {
        return;
    }
    if (pointerLevel==1)
    {
        m_levels[0]->draw();
    }
    else if (pointerLevel == 2)
    {
        if (nextLevel)
        {
            init();
            nextLevel = false;
        }
        m_levels[1]->draw();
    }
    else if (pointerLevel == 3)
    {
        if (nextLevel)
        {
            init();
            nextLevel = false;
        }
        m_levels[2]->draw();
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

    if (!m_level) {
        return;
    }
    if (pointerLevel == 1)
    {
        m_levels[0]->update(dt);
    }
    else if(pointerLevel == 2)
    {
        m_levels[1]->update(dt);
    }
    else if(pointerLevel == 3)
    {
        m_levels[2]->update(dt);
    }
    m_debugging = graphics::getKeyState(graphics::SCANCODE_0);

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
GameState& GameState::AddIndex()
{
    cout << "before " << pointerLevel << endl;
    this->pointerLevel++;
    cout << "after " << pointerLevel << endl;
    return *this;
}
//--------------------------------------------------------------------------------------------------
GameState* GameState::m_unique_state = nullptr;