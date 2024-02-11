#pragma once
#include "Enemy.h"
#include "GameObject.h"

enum RockTyoe { ROCK = 0, GOBLIN, IceBlOb, NROFTYPES1 };
class Rock :public Enemy {

private:
	//help for the collision with static objects
	vector<string> rock_enemy;
	vector<vector<char>> levelMapHelp;
	vector<vector<Box>> m_blocksHelp;

	//animattion attack
	bool AttackingAnimation;
	float indexAttackAnimation;
	int type_enemy;
public:
	Rock(GameState* gs, int type, float px, float py,const string& name = "", int health = 300);
	~Rock();
	void update(float dt) override;
	void init() override;
	void draw() override;
	void debugDrawEnemy(float x, float y) override;
	const int& getType() const;
	void checkCollisionRock();
	void reverse();
};