
#pragma once
#include "Rock.h"
#include "GameObject.h"
#include "GameState.h"
#include "Level.h"

Rock::Rock(GameState* gs, float px, float py, const string& name, int health) :Enemy(gs, name, health)
{
    m_pos_x = px;
    m_pos_y = py;
    m_width = enemy_size*0.7;
    m_height = enemy_size*0.9;
    init();
}

Rock::~Rock()
{
}

void Rock::update(float dt)
{
    m_pos_x += enemy_speed_rock;
    checkCollisionRock();
    Enemy::update(dt);
}

void Rock::init()
{
    //Brush
    br_enemy.fill_opacity = 1.1f;
    br_enemy.outline_opacity = 0.0f;
    br_enemy.texture = m_state->getFullAssetPath("rockEnemyWalking1.png");

    rock_enemy.push_back(m_state->getFullAssetPath("rockEnemyWalking1.png"));
    rock_enemy.push_back(m_state->getFullAssetPath("rockEnemyWalking2.png"));
    rock_enemy.push_back(m_state->getFullAssetPath("rockEnemyWalking3.png"));
    rock_enemy.push_back(m_state->getFullAssetPath("rockEnemyWalking4.png"));
    rock_enemy.push_back(m_state->getFullAssetPath("rockEnemyWalking5.png"));
    rock_enemy.push_back(m_state->getFullAssetPath("rockEnemyWalking6.png"));
    rock_enemy.push_back(m_state->getFullAssetPath("rockEnemyWalking7.png"));
    rock_enemy.push_back(m_state->getFullAssetPath("rockEnemyWalking8.png"));
    rock_enemy.push_back(m_state->getFullAssetPath("rockEnemyWalking9.png"));
    rock_enemy.push_back(m_state->getFullAssetPath("rockEnemyWalking10.png"));
    rock_enemy.push_back(m_state->getFullAssetPath("rockEnemyWalking11.png"));

    Enemy::init();
}

void Rock::draw()
{
    float x = m_pos_x + m_state->m_global_offset_x;
    float y = m_pos_y + m_state->m_global_offset_y;
    int s = (int)fmod(1000.0f - m_pos_x * 0.025f, rock_enemy.size());
    br_enemy.texture = rock_enemy[s];
    if (enemy_speed_rock <= 0) {
        graphics::setScale(-1.0f, 1.0f);
    }
    if (enemy_speed_rock > 0)
    {
        graphics::resetPose();
    }
    graphics::drawRect(x, y, m_width, m_height, br_enemy);

    if (m_state->m_debugging)
    {
       debugDrawEnemy(x, y);
    }
    
}

void Rock::debugDrawEnemy(float x, float y)
{
    graphics::Brush br_enemy_birdsD;
    br_enemy_birdsD.outline_opacity = 1.0f;
    br_enemy_birdsD.fill_opacity = 0.2f;
    br_enemy_birdsD.fill_color[0] = 1.0f;
    br_enemy_birdsD.fill_color[1] = 0.3f;
    br_enemy_birdsD.fill_color[2] = 0.0f;
    br_enemy_birdsD.outline_color[0] = 0.2f;
    br_enemy_birdsD.outline_color[1] = 1.2f;
    br_enemy_birdsD.outline_color[2] = 0.3f;

    graphics::drawRect(x, y, enemy_size, enemy_size, br_enemy_birdsD);
}

void Rock::checkCollisionRock()
{
    levelMapHelp =m_state->getlevel()->getLevelMap();
    m_blocksHelp = m_state->getlevel()->getBlock();
    for (int row = 0; row < levelMapHelp.size(); row++) {
        for (int col = 0; col < levelMapHelp[row].size(); col++) {
            float offset = 0.0f;
            Blocks block = m_blocksHelp[row][col];
            if (levelMapHelp[row][col] == 'X') {
                
                if (offset = intersectDown(block))
                {
                    m_pos_y += offset;
                    break;
                }
            }
            if (levelMapHelp[row][col] == 'X' || levelMapHelp[row][col] == 'T' || levelMapHelp[row][col] == 'R')
            {
                if (offset = intersectSideways(block))
                {
                    if (enemy_speed_rock > 0) {
                        m_pos_x += offset;
                        reverse();
                    }
                    else {
                        m_pos_x += offset;
                        reverse();
                    }
                    break;
                }
            }
        }
    }
}

void Rock::reverse()
{
    enemy_speed_rock *= -1;
}

