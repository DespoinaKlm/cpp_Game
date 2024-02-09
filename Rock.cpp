#pragma once
#include "Rock.h"
#include "GameObject.h"
#include "GameState.h"
#include "Level.h"
//----------------------------------Rock------------------------------------------------------
Rock::Rock(GameState* gs, int type, float px, float py, const string& name, int health) :Enemy(gs, name, health)
{
    m_pos_x = px;
    m_pos_y = py;
    m_width = enemy_size*0.7;
    m_height = enemy_size*0.9;
    type_enemy = type;
    speed_enemy = 2.0f;
    AttackingAnimation = false;
    attack = false;
    setDead(false);
    init();
}
//----------------------------------Rock------------------------------------------------------
Rock::~Rock()
{
}
//----------------------------------update----------------------------------------------------
void Rock::update(float dt)
{
    m_pos_x += speed_enemy;
    checkCollisionRock();
    Enemy::update(dt);
}
//----------------------------------init------------------------------------------------------
void Rock::init()
{
    //Brush
    br_enemy.fill_opacity = 1.1f;
    br_enemy.outline_opacity = 0.0f;
    br_enemy.texture = m_state->getFullAssetPath("rockEnemyWalking1.png");

    
    //Animation
    switch (type_enemy)
    {
        case RockTyoe::ROCK:
            br_enemy.texture = m_state->getFullAssetPath("rockEnemyWalking1.png");
            rock_enemy= loadFileGameObject("rockEnemyWalking");
            break;
        case RockTyoe::GOBLIN:
            br_enemy.texture = m_state->getFullAssetPath("greenGoblinWalking1.png");
            rock_enemy = loadFileGameObject("greenGoblinWalking");
            setName("Goblin");
            break;
        case RockTyoe::IceBlOb:
            br_enemy.texture = m_state->getFullAssetPath("iceBlobWalking1.png");
            rock_enemy = loadFileGameObject("iceBlobWalking");
            setName("iceBlob");
            break;
    }
}
//----------------------------------draw------------------------------------------------------
void Rock::draw()
{
    if (!dead) {
        float x = m_pos_x + m_state->m_global_offset_x;
        float y = m_pos_y + m_state->m_global_offset_y;
        int s = (int)fmod(1000.0f - m_pos_x * 0.025f, rock_enemy.size());
        br_enemy.texture = rock_enemy[s];
        if (speed_enemy <= 0) {
            graphics::setScale(-1.0f, 1.0f);
        }
        if (speed_enemy >0)
        {
            graphics::resetPose();
        }
        if (attack)
        {
            switch (type_enemy)
            {
            case RockTyoe::ROCK:
                rock_enemy = loadFileGameObject("rockEnemyAttack");
                break;
            case RockTyoe::GOBLIN:
                rock_enemy = loadFileGameObject("greenGoblinAttack");
                break;
            case RockTyoe::IceBlOb:
                rock_enemy = loadFileGameObject("iceBlobAttack");
                break;
            }
            AttackingAnimation = true;
            attack = false;
            
        }
        else
        {
            if (!AttackingAnimation) {
                switch (type_enemy)
                {
                case RockTyoe::ROCK:
                    rock_enemy = loadFileGameObject("rockEnemyWalking");
                    break;
                case RockTyoe::GOBLIN:
                    rock_enemy = loadFileGameObject("greenGoblinWalking");
                    break;
                case RockTyoe::IceBlOb:
                    rock_enemy = loadFileGameObject("iceBlobWalking");
                    break;
                }
            }
        }
        if (AttackingAnimation) {
            indexAttackAnimation += 0.25;
            if (indexAttackAnimation >= rock_enemy.size())
            {
                AttackingAnimation = false;
                indexAttackAnimation = 0;
            }
            else
            {
                br_enemy.texture = rock_enemy[int(indexAttackAnimation)];
            }
        }
        if (getName()=="iceBlob")
        {
            graphics::drawRect(x, y, m_width, m_height, br_enemy);
        }
        else
        {
            graphics::drawRect(x, y, m_width * 1.5, m_height*1.5, br_enemy);
        }
        

        if (m_state->m_debugging)
        {
           debugDrawEnemy(x, y);
        }
    }
    Enemy::draw();
}
//----------------------------------debugDrawEnemy--------------------------------------------
void Rock::debugDrawEnemy(float x, float y)
{
    Enemy::debugDrawEnemy(x, y);

}
//----------------------------------getType()-------------------------------------------------
const int& Rock::getType() const
{
    return type_enemy;
}
//----------------------------------checkCollisionRock----------------------------------------
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
                    if (speed_enemy > 0) {
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
//----------------------------------reverse---------------------------------------------------
void Rock::reverse()
{
    speed_enemy *= -1;
}
//--------------------------------------------------------------------------------------------
