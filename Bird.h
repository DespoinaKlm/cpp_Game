#pragma once
#include <vector>
#include <string>
#include "Enemy.h"
#include "GameObject.h"
using namespace std;

class Bird :public Enemy {

private:
	graphics::Brush br_enemy_birds;
	vector<string> bird_enemy;
	float indexBird;
	int reverse;
	int firstposition;
public:
	Bird(GameState* gs, float px, float py, const string& name, int health=300);
	~Bird();
	void update(float dt) override;
	void init() override;
	void draw() override;
	void debugDrawEnemy(float x, float y) override;
};