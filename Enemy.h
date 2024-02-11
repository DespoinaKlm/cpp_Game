#pragma once
#include <sgg/graphics.h>
#include "GameObject.h"
#include "GameState.h"
#include "box.h"
#include "Blocks.h"

class Enemy : public GameObject, public Box {
private:
	vector<string> enemy_death;
	const char* str2= "RockEnemy";
	const char* str3 = "Goblin";
	const char* str4 = "iceBlob";
	const char* str1 = m_name.c_str();
	
protected:
	bool cantAttack;
	bool dead;
	bool attack;
	bool canAttack;
	int m_enemy_health;
	int m_attack;
	
	float indexDrawDeath=0;
	float speed_enemy = 5.0f;
	float enemy_size = 200;
	
	void setHealth(int health);
	void setAttack();
	
	int strongerAttack = 1;
	graphics:: Brush br_enemy;
	graphics::Brush br_enemyD;
	Box m_weaponlevel;

	
public:
	Enemy(GameState* gs, const string& name = "", int health = 300);
	virtual ~Enemy();
	virtual void update(float dt);
	virtual void init();
	virtual void draw();
	virtual void debugDrawEnemy(float x, float y);
	float getAttack();
	float getHealth();
	inline bool getCantAttack() const { return cantAttack; };
	inline int getStrongerAttack() const { return strongerAttack;}
	inline void setDead(bool answer) { dead = answer; }
	inline bool getDead() const{ return dead; }
	void enemyDrawDeath(vector<string> draw_death, float px, float py, float pw, float ph);
	void checkCollisionWithPlayer(float dt);
	Enemy& Damage(int damage);
};
