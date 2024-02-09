#include "Enemy.h"
#include <sgg/graphics.h>
#include <iostream>

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

    if (m_enemy_health <= 150 && isActive()) {
        if (strongerAttack==1) {
            graphics::playSound(m_state->getFullAssetPath("roar.wav"), 0.5f);
        }
        strongerAttack = 2;
        
    }
    GameObject::update(dt);
}
//---------------------------------------init-------------------------------------------------------------
void Enemy::init()
{
    
}
//---------------------------------------init-------------------------------------------------------------
void Enemy::draw()
{
    
    if (dead)
    {
        if (strcmp(str1, str2) == 0) {
            float x = m_pos_x + m_state->m_global_offset_x;
            float y = m_pos_y + m_state->m_global_offset_y;
            if (speed_enemy <= 0) {
                graphics::setScale(-1.0f, 1.0f);
            }
            if (speed_enemy > 0)
            {
                graphics::resetPose();
            }
            enemyDrawDeath(enemy_death, x, y, this->m_width, this->m_height);

        }
        //bird
        else
        {
            enemyDrawDeath(enemy_death, this->m_pos_x, this->m_pos_y, this->m_width, this->m_height);
        }
        
    }
}
//---------------------------------------getAttack--------------------------------------------------------
float Enemy::getAttack()
{
   this->attack = true;
   return (40 + rand() % 81)* getStrongerAttack();
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
    indexDrawDeath += 0.2;
    if (indexDrawDeath >=draw_death.size()) {
        indexDrawDeath = draw_death.size()-1;
        setActive(false);
        
    }
    br_enemy.texture = draw_death[int(indexDrawDeath)];
    graphics::drawRect(px, py, pw, ph, br_enemy);
}
//---------------------------------------Damage------------------------------------------------------------
Enemy & Enemy::Damage(int damage)
{
    //cout << getHealth() << endl;
    m_enemy_health -= damage;
    if (m_enemy_health <= 0)
    {
        m_enemy_health = 0;
        dead = true;
        cantAttack = true;
        if (strcmp(str1, str2) == 0)
        {
            enemy_death=loadFileGameObject("rockEnemyDies");
        }
        else if (strcmp(str1, str3) == 0) {
            enemy_death = loadFileGameObject("greenGoblinDie");
        }
        else if (strcmp(str1, str4) == 0) {
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
//---------------------------------------init-------------------------------------------------------------
Enemy::~Enemy()
{
}
//---------------------------------------------------------------------------------------------------------    