#pragma once
#include "Enemy.h"
#include "GameObject.h"

class Rock :public Enemy {

private:
	graphics::Brush br_enemy_rock;
	vector<string> rock_enemy;
	vector<vector<char>> levelMapHelp;
	vector<vector<Blocks>> m_blocksHelp;

	const float m_gravity = 9.8f;
	float enemy_size = 200;
	float enemy_speed_rock = 2.0;
public:
	Rock(GameState* gs, float px, float py,const string& name = "", int health = 300);
	~Rock();
	void update(float dt) override;
	void init() override;
	void draw() override;
	void debugDrawEnemy(float x, float y) override;
	void checkCollisionRock();
	void reverse();
	float getSpeed(){ return enemy_speed_rock; }
};