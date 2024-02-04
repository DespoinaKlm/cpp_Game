#pragma once
#include <stdio.h>
#include <tchar.h>
#include <sgg/graphics.h>
#include "GameState.h"
#include "Level.h"
#include "Player.h"
#include <thread>
#include <chrono>
#include "Vector2D.h"
#include <cstdio>
#include "Enemy.h"
#include "Rock.h"
#include "Bird.h"
using namespace std;
//-----------------------------------Constructor----------------------------------------------------
GameState::GameState()
{
}
//------------------------------------init()--------------------------------------------------------
void GameState::init()
{
   
    m_player = new Player(m_unique_state, "The-man",1000);
    m_player->init();

    m_level = new Level(m_unique_state,"level-1");
    m_level->init();

    graphics::preloadBitmaps(getAssetDir());
    graphics::setFont(m_asset_path+"OpenSans-Regular.ttf");
    graphics::playMusic(getFullAssetPath("TheRebelPath.wav"), 0.5f,true,4000);

}
//------------------------------------draw()--------------------------------------------------------
void GameState::draw()
{
    if (!m_level) {
        return;
    }
    
    m_level->draw();

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
    
    m_level->update(dt);
    m_debugging = graphics::getKeyState(graphics::SCANCODE_0);

}
//------------------------------------get_Gamestate()-----------------------------------------------
GameState* GameState::get_Gamestate()
{
    if (m_unique_state==nullptr) {
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
    if (m_level) {
        // an exoume ki alla levels prepei na pame na kanoume delete ta levels kai oxi ton prointer kapoiou apo auta diladi se for loop
        delete m_level;
    }
    if (m_enemy) {
        delete m_enemy;
    }

    if (m_enemy_bird) {
        delete m_enemy_bird;
    }
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

//------------------------------------getCanvasWidth()---------------------------------------------
float GameState::getCanvasWidth()
{
    return m_canvas_width;
}
//------------------------------------getCanvasHeight()---------------------------------------------
float GameState::getCanvasHeight()
{
    return m_canvas_height;
}

GameState * GameState :: m_unique_state = nullptr;
