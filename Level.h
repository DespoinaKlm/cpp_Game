#pragma once
#include <sgg/graphics.h>
#include "GameObject.h"
#include <list>
#include "box.h"
#include "Enemy.h"
#include "Blocks.h"
#include "Poissons.h"
#include "Bird.h"
#include "Rock.h"

class Poissons;
using namespace std;
class Level : public GameObject {
	
	vector<vector<char>> &level_map;
	Poissons* poisontype;
	float indexframeGate;
	bool next_level = false;

	//Code for blocks
	vector<vector<string>> m_block_names;
	vector<vector<Blocks>> m_blocks;
	const float m_block_size = 200.0f;
	graphics::Brush m_block_brush;
	graphics::Brush m_block_brush_debug;
	void drawBlock(int i, int j);

	//here is the score and the level
	string namelevel;
	int m_score;

	//brush for the background 
	graphics::Brush br_background;

	Box m_weaponlevel;
	int boxmove;
	graphics::Brush br_weapon;
	
	//Code for the enemy bird
	Bird* EnemyBird;
	Rock* EnemyRock;
	void drawEnemies();
	void updateEnemies(float sdt);
	void SpawnEnemy();
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	// static and dynamic objects
	vector <GameObject*> m_static_objects;
	list <GameObject*>m_dynamic_objects;
	vector<Enemy*> m_birds;
	vector<Rock*> m_rocks;
	vector<string> m_gate;

public:
	Level(GameState* gs,vector<vector<char>>& map ,const string name = "Level0",float score=0);
	~Level();
	void checkCollisions();
	void checkCollisionWithEnemies(float dt);
	void update(float dt) override;
	void init() override;
	void draw() override;
	inline string getLevelName() { return namelevel; }
	void drawScore();
	//Code for the score 
	void setScore(float score);
	float getScore();
	void NextLevel(float score,float health);
	Level& updateScore(float score);
	inline bool getNextLevel() const { return next_level;}
	
	vector<vector<Blocks>> getBlock() { return m_blocks; }
	vector<vector<char>> getLevelMap() { return level_map;}
};
