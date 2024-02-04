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
#include "Collision.h"

using namespace std;
class Poissons;
class Level : public GameObject {
	/*
	vector<vector<char>> level_map = {
		   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E',' ', 'P', ' ', ' ', 'P', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //1
		   {' ', ' ', ' ', ' ', ' ', 'X', 'X', ' ', ' ', ' ', ' ', ' ', 'X','X', 'X', 'X', 'X', 'X', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' '}, //2
		   {' ', ' ', ' ', 'X', 'X', 'X', 'X', 'X', ' ', ' ', ' ', 'X', 'X',' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', 'T'}, //3
		   {'T', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X', 'X',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'}, //4
		   {'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X', 'X', 'X', 'X',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' '}, //5
		   {'X', 'X', 'X', 'X', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', 'X', 'X', ' ', ' ', 'X', 'X', 'X', 'X', ' ', ' ', ' '}, //6
		   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' '}, //1
		   {' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'T'}, //2
		   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X','X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'}, //3
		   {'T', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', 'X', 'X', 'X','X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //4
		   {'X', 'X', ' ', ' ', ' ', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', 'E', ' ', ' ', 'X', ' ', 'X', ' ', ' ', ' '}, //5
		   {'X', 'X', ' ', ' ', 'X', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', 'X', 'X', 'X', 'X', ' ', ' ', ' ', ' ', ' ', 'T'}, //6
		   {' ', ' ', ' ', 'R', ' ', ' ', ' ', 'R', ' ', ' ', ' ', ' ', ' ',' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'}, //7
		   {' ', ' ', 'X', 'X', 'X', 'X', 'X', 'X', 'X', ' ', ' ', ' ', ' ',' ', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' '}, //8
		   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //9
		   {'T', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X', 'X',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' '}, //10
		   {'X', ' ', ' ', ' ', 'X', 'X', ' ', ' ', 'X', 'X', 'X', 'X', 'X','X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' '}, //11
		   {'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', 'R', ' ', ' ', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', 'T'}, //12
		   {'X', 'X', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X','X', 'X', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', 'X'}, //13
		   {'X', 'X', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X'}, //14
		   {' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', 'X', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //15
		   {' ', ' ', ' ', ' ', 'R', ' ', 'X', ' ', ' ', 'X', 'X', ' ', 'E',' ', 'R', ' ', 'R', ' ', ' ', ' ', ' ', ' ', 'E', ' ', ' ', ' '}, //16
		   {'T', 'P', ' ', 'X', 'X', 'X', 'X', ' ', ' ', 'X', 'X', 'X', 'X','X', 'X', 'X', 'X', 'X', 'X', ' ', ' ', 'X', 'X', ' ', 'G', 'T'}, //17
		   {'X', 'X', 'X', 'X', 'X', 'X', 'X', ' ', ' ', 'X', 'X', 'X', 'X','X', 'X', 'X', 'X', 'X', 'X', ' ', ' ', 'X', 'X', 'X', 'X', 'X'}, //18
	};
	//dipla apo to g to kontino eixa ena x mhn to jexaseis pigene san piramida
	*/
	vector<vector<char>> level_map = {
		   {' ', ' ', ' ', ' ', ' ', 'P', ' ', ' ', ' ', ' ', ' ', ' ', 'R',' ', ' ', ' ', ' ', 'E', ' ', 'R', ' ', ' ', ' ', ' ', ' ', ' '}, //1
		   {' ', ' ', ' ', ' ', ' ', 'X', 'X', ' ', ' ', ' ', ' ', ' ', 'X','X', 'X', 'X', 'X', 'X', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' '}, //2
		   {' ', ' ', ' ', 'X', 'X', 'X', 'X', 'X', ' ', ' ', ' ', 'X', 'X',' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', 'T'}, //3
		   {'T', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X', 'X',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'}, //4
		   {'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X', 'X', 'X', 'X',' ', ' ', ' ', ' ', ' ', ' ', 'R', ' ', 'E', 'R', ' ', ' ', ' '}, //5
		   {'X', 'X', 'X', 'X', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', 'X', 'X', ' ', ' ', 'X', 'X', 'X', 'X', ' ', ' ', ' '}, //6
		   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' '}, //1
		   {' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'T'}, //2
		   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X','X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'}, //3
		   {'T', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', 'X', 'X', 'X','X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //4
		   {'X', 'X', ' ', ' ', ' ', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', 'R', 'E', ' ', ' ', 'X', ' ', 'X', ' ', ' ', ' '}, //5
		   {'X', 'X', ' ', ' ', 'X', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', 'X', 'X', 'X', 'X', ' ', ' ', ' ', ' ', ' ', 'T'}, //6
		   {' ', ' ', ' ', 'R', ' ', ' ', ' ', 'R', ' ', ' ', ' ', ' ', ' ',' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'}, //7
		   {' ', ' ', 'X', 'X', 'X', 'X', 'X', 'X', 'X', ' ', ' ', ' ', ' ',' ', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' '}, //8
		   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //9
		   {'T', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X', 'X',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' '}, //10
		   {'X', ' ', ' ', ' ', 'X', 'X', ' ', ' ', 'X', 'X', 'X', 'X', 'X','X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' '}, //11
		   {'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', 'R', ' ', ' ', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', 'T'}, //12
		   {'X', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X','X', 'X', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', 'X'}, //13
		   {'X', 'X', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'X'}, //14
		   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //15
		   {' ', ' ', ' ', ' ', 'R', ' ', 'X', ' ', ' ', 'X', 'X', ' ', ' ',' ', 'R', ' ', 'R', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //16
		   {'T', 'P', 'E', 'P', 'X', 'X', 'X', ' ', ' ', 'X', 'X', 'X', 'X','X', 'X', 'X', 'X', 'X', 'X', ' ', ' ', 'X', 'X', ' ', 'G', 'T'}, //17
		   {'X', 'X', 'X', 'X', 'X', 'X', 'X', ' ', ' ', 'X', 'X', 'X', 'X','X', 'X', 'X', 'X', 'X', 'X', ' ', ' ', 'X', 'X', 'X', 'X', 'X'}, //18
	};//dipla apo to g to kontino eixa ena x mhn to jexaseis pigene san piramida

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

	// class collision
	class Collision* collisionInstance=0;
	Box m_weaponlevel;
	graphics::Brush br_weapon;
	
	//void checkCollisions();
	//void check_collision();
	
	//Code for the enemy bird
	Enemy* EnemyBird;
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
	vector<Enemy*> m_block_enemies;
	vector<Enemy*> m_birds;
	vector<Rock*> m_rocks;
	vector<Poissons*> m_poissons;
	//Code for the moving animation
	vector<string> m_gate;
	vector<string> m_poisson;


public:
	Level(GameState* gs, const string name = "Level0",float score=0);
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
	Level& updateScore(float score);

	//Code for the Collision class
	vector<vector<Blocks>> getBlock() { return m_blocks; }
	//Blocks& getBlockXY();
	vector<vector<char>> getLevelMap() { return level_map;}
};
