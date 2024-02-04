#include "Enemy.h"
#include <sgg/graphics.h>
#include <iostream>

using namespace std;
//---------------------------------------Constructor------------------------------------------------------
Enemy::Enemy(GameState* gs, const string& name ,int health) :GameObject(gs,name),m_attack(getAttack()), m_enemy_health(health)
{
    m_enemy_health = health;
}
//---------------------------------------update-----------------------------------------------------------
void Enemy::update(float dt)
{

    if (m_enemy_health <= 150 && isActive()) {
        strongerAttack = 2;
        graphics::playSound(m_state->getFullAssetPath("roar.wav"), 0.5f);
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

}
//---------------------------------------init-------------------------------------------------------------
Enemy::~Enemy()
{
}
//---------------------------------------getAttack--------------------------------------------------------
float Enemy::getAttack()
{
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
//---------------------------------------Damage------------------------------------------------------------
Enemy & Enemy::Damage(int damage)
{
    m_enemy_health -= damage;
    if (m_enemy_health <= 0) {
        m_enemy_health = 0;
        setActive(false);
    }
    return *this;
}
//---------------------------------------debugDrawEnemy----------------------------------------------------
void Enemy::debugDrawEnemy(float x,float y)
{
}

    