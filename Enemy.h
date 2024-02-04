#pragma once
#include "GameObject.h"
#include "box.h"
#include <sgg/graphics.h>
#include "GameState.h"
#include "Blocks.h"

class Enemy : public GameObject, public Box {
private:
	vector<string> rock_enemy;
	vector<string> bird_enemy;
protected:

	int m_enemy_health;
	int m_attack;
	float speed_enemy = 0.3f;
	float enemy_size = 200;
	
	void setHealth(int health);
	void setAttack();
	int strongerAttack = 1;
	graphics:: Brush br_enemy;
	
public:
	Enemy(GameState* gs, const string& name = "", int health = 300);
	virtual ~Enemy();
	virtual void update(float dt);
	virtual void init();
	virtual void draw();
	virtual void debugDrawEnemy(float x, float y);
	//virtual float getSpeed();
	float getAttack();
	float getHealth();
	inline int getStrongerAttack() { return strongerAttack; }
	Enemy& Damage(int damage);

};
