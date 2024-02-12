#include "Enemy.h"
#include <sgg/graphics.h>
#include <iostream>
#include "GameObject.h"
#include "GameState.h"
#include "Player.h"
#include "Level.h"
#include "box.h"

using namespace std;
//---------------------------------------Constructor------------------------------------------------------
Enemy::Enemy(GameState* gs, const string& name ,int health) :GameObject(gs,name),m_attack(getAttack()), m_enemy_health(health)
{
    m_enemy_health = health;
    cantAttack = false;
}
//---------------------------------------update-----------------------------------------------------------
void Enemy::update(float dt)
{
    if (m_enemy_health <= 150 && !dead)
    {
        if (strongerAttack == 1) {
            if (strcmp(str1, "Bird") != 0 ) {
                graphics::playSound(m_state->getFullAssetPath("roar.wav"), 0.5f);
                strongerAttack = 4;
            }
            else
            {
                strongerAttack = 2;
            }
        }
    }
    checkCollisionWithPlayer(dt);
    GameObject::update(dt);
}
//---------------------------------------init-------------------------------------------------------------
void Enemy::init()
{
    br_enemy.fill_opacity = 1.1f;
    br_enemy.outline_opacity = 0.0f;
}
//---------------------------------------draw-------------------------------------------------------------
void Enemy::draw()
{
    if (dead)
    {
        float x = m_pos_x + m_state->m_global_offset_x;
        float y = m_pos_y + m_state->m_global_offset_y;
        if (strcmp(str1, "RockEnemy") == 0 || strcmp(str1, "Goblin") == 0 || strcmp(str1, "iceBlob") == 0) {
            
            if (speed_enemy <= 0) {
                graphics::setScale(-1.0f, 1.0f);
            }
            if (speed_enemy > 0)
            {
                graphics::resetPose();
            }
            if (strcmp(str1, "iceBlob") == 0)
            {
                enemyDrawDeath(enemy_death, x, y, this->m_width, this->m_height);
            }
            else
            {
                enemyDrawDeath(enemy_death, x, y, this->m_width * 1.6, this->m_height * 1.5);
            }

        }
        else
        {
            enemyDrawDeath(enemy_death, x, y, this->m_width, this->m_height);
        }
        
    }

}
//---------------------------------------getAttack--------------------------------------------------------
float Enemy::getAttack()
{
   this->attack = true;
   return (20 + rand() % 41)* getStrongerAttack();
}
//---------------------------------------getHealth--------------------------------------------------------
float Enemy::getHealth()
{
    return m_enemy_health;
}
//---------------------------------------setHealth--------------------------------------------------------
void Enemy::setHealth(int health)
{
    m_enemy_health = health;
}
//---------------------------------------setAttack--------------------------------------------------------
void Enemy::setAttack()
{
    m_attack= 20 + rand() % 41;
    
}
//---------------------------------------enemyDrawDeath---------------------------------------------------
void Enemy::enemyDrawDeath(vector<string> draw_death, float px, float py,float pw, float ph)
{
    indexDrawDeath += 0.15;
    if (indexDrawDeath >=draw_death.size()) {
        indexDrawDeath = draw_death.size()-1;
        m_active=false;
    }
    br_enemy.texture = draw_death[int(indexDrawDeath)];
    if (getName() == "iceBlob")
    {
        graphics::drawRect(px, py, this->m_width * 1.5, this->m_height * 1.5, br_enemy);
    }
    else if(getName() == "Bird")
    {
        graphics::drawRect(px, py, pw, ph, br_enemy);
        graphics::playSound(m_state->getFullAssetPath("boom.wav"), 1.0f);
    }
    else
    {
        graphics::drawRect(px, py, this->m_width * 2, this->m_height * 2, br_enemy);
    }
    
}
//---------------------------------------checkCollisionWithPlayer-----------------------------------------
void Enemy::checkCollisionWithPlayer(float dt)
{
    //when the player hasnt attacked
    if (isActive())
    {
        if (m_state->getPlayer()->isActive()) {
            float offset = 0.0f;
            if (offset = intersectSideways(*m_state->getPlayer()))
            {
                m_state->getlevel()->updateScore((10 + rand() % 50) * -1);
                //moves backwards
                if (m_state->getPlayer()->isRight()){
                    
                    m_pos_x += offset + 20;
                   
                    m_state->getPlayer()->m_pos_x += offset - 50;
                }
                else
                {
                    m_state->getPlayer()->m_pos_x += offset + 50;
                    m_pos_x += offset - 50;

                }
                if (!getCantAttack() && !m_state->getPlayer()->isAttacking())
                {
                    graphics::playSound(m_state->getFullAssetPath("notAttack.wav"), 1.0f);
                    m_state->getPlayer()->Damage(getAttack());
                }
                m_state->getPlayer()->m_vx = 0.0f;
                //break;
            }
        }
    }
    //player hit enemy head
    if (isActive())
    {
        float offset = 0.0f;
        
        if (m_state->getPlayer()->intersectDown(*this))
        {
                m_state->getPlayer()->m_pos_y += offset - 70;
                m_state->getlevel()->updateScore(10 + rand() % 151);
                graphics::playSound(m_state->getFullAssetPath("Attack.wav"), 1.0f);
                //plus attack 
                if (m_state->getPlayer()->PlusAttack())
                {
                    Damage(m_state->getPlayer()->get_Attack() * 2);
                    m_state->getPlayer()->setPlusAttack(false);
                }
                else
                {
                    Damage(m_state->getPlayer()->get_Attack());
                }
                //sound of death
                if (dead)
                {
                    if (strcmp(str1,"Bird") != 0)
                    {
                        graphics::playSound(m_state->getFullAssetPath("death_enemy.wav"), 1.0f);
                    }
                    else {
                        graphics::playSound(m_state->getFullAssetPath("bird.wav"), 1.0f);
                    }
                    m_state->getlevel()->updateScore(100 + rand() % 350);
                
                }
                m_state->getPlayer()->m_vy = 0.0f;
        }
    }
}
//---------------------------------------Damage------------------------------------------------------------
Enemy & Enemy::Damage(int damage)
{
    m_enemy_health -= damage;
    if (m_enemy_health <= 0)
    {
        m_enemy_health = 0;
        dead = true;
        cantAttack = true;
        //enemy death animation
        if (strcmp(str1, "RockEnemy") == 0)
        {
            enemy_death=loadFileGameObject("rockEnemyDies");
        }
        else if (strcmp(str1, "Goblin") == 0) {
            enemy_death = loadFileGameObject("greenGoblinDie");
        }
        else if (strcmp(str1, "iceBlob") == 0) {
            enemy_death = loadFileGameObject("iceBlobDie");
        }
        else
        {
            enemy_death = loadFileGameObject("pouf");
        }
    }
    return *this;
}
//---------------------------------------debugDrawEnemy----------------------------------------------------
void Enemy::debugDrawEnemy(float x,float y)
{
    br_enemyD.outline_opacity = 1.0f;
    br_enemyD.fill_opacity = 0.2f;
    br_enemyD.fill_color[0] = 1.0f;
    br_enemyD.fill_color[1] = 0.3f;
    br_enemyD.fill_color[2] = 0.0f;
    br_enemyD.outline_color[0] = 0.2f;
    br_enemyD.outline_color[1] = 1.2f;
    br_enemyD.outline_color[2] = 0.3f;
    graphics::drawRect(x, y, enemy_size, enemy_size, br_enemyD);

}
//---------------------------------------Enemy-------------------------------------------------------------
Enemy::~Enemy()
{
}
//---------------------------------------------------------------------------------------------------------    