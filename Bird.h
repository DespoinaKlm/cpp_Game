#pragma once
#include <vector>
#include <string>
#include "Enemy.h"
#include "GameObject.h"
using namespace std;

class Bird :public Enemy {

	//Code for Bird Enemies
private:
	graphics::Brush br_enemy_birds;
	vector<string> bird_enemy;
	float indexBird;
	int reverse;
	//vector<string> loadFileIntoVector(const std::string& filePath);
public:
	const string m_filename;
	Bird(GameState* gs, const string& name = "", int health = 300);
	~Bird();
	vector<string>loadFileIntoVector(const string& movement);
	void update(float dt) override;
	void init() override;
	void draw() override;
	void debugDrawEnemy(float x, float y) override;
};