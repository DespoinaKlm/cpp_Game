#pragma once
#include <sgg/graphics.h>
#include "GameObject.h"
#include <list>
#include "box.h"
#include "Enemy.h"
#include "Poissons.h"
#include "Bird.h"
#include "Rock.h"

class Poissons;
using namespace std;
class Level : public GameObject
{
	//Poison
	Poissons* poisontype;
	float indexframeGate;

	//Code for blocks and names
	vector<vector<string>> m_block_names;
	vector<vector<Box>> m_blocks;
	const float m_block_size = 200.0f;
	graphics::Brush m_block_brush;
	graphics::Brush m_block_brush_debug;
	void drawBlock(int i, int j);

	//here is the score and the level
	int m_score;

	//brush for the background 
	graphics::Brush br_background;

	//player weapon
	graphics::Brush br_weapon;
	Box m_weaponlevel;
	int boxmove;

	//Code for the enemy bird
	Bird* EnemyBird;
	Rock* EnemyRock;
	void updateEnemies(float sdt);
	void SpawnEnemy();
	float enemySpawnTimer;
	float enemySpawnTimerMax;

	// static and dynamic objects
	vector<vector<char>> level_map;
	list <GameObject*>m_dynamic_objects;
	vector<Enemy*> m_Enemies;
	vector<string> m_gate;

public:
	
	Level(GameState* gs,const string name = "Level0",float score=0);
	~Level();

	//Inheritance from GameObject
	void update(float dt) override;
	void init() override;
	void draw() override;

	//Collisions for the player
	void checkCollisions();
	void checkCollisionWithEnemies(float dt);
	
	
	//Code for the score 
	void setScore(float score);
	float getScore();
	void drawScore();
	Level& updateScore(float score);

	//Vectors for the enem
	vector<vector<char>> loadFileMap(int pointer );
	vector<vector<Box>> getBlock() const { return m_blocks; }
	vector<vector<char>> getLevelMap() const{ return level_map;}
};
