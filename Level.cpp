#pragma once
#include "GameState.h"
#include "Level.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "Enemy.h"
#include "Rock.h"
#include "Bird.h"
#include "Poissons.h"

using namespace std;
//------------------------------------Constructor---------------------------------------------------
Level::Level(GameState* gs,const string name,float score):GameObject(gs, name)
{
	m_score = score;
}
//------------------------------------update()--------------------------------------------------------
void Level::update(float dt)
{
	
	float offset_x = ((m_state->m_global_offset_x / 2.0f) + (m_state->getCanvasWidth() / 2.0f));
	float offset_y = ((m_state->m_global_offset_y / 2.0f) + (m_state->getCanvasHeight() / 2.0f));

	if (m_state->getPlayer()->isActive())
	{
		m_state->getPlayer()->update(dt);
	}

	updateEnemies(dt);
	checkCollisions();
	checkCollisionWithEnemies(dt);

	if (m_state->getPlayer()->isActive() && m_state->getPlayer()->get_Health() <= 250) {
		float p = 0.5f + fabs(cos(graphics::getGlobalTime() / 1000.0f));
		br_background.fill_color[0] = 1.0f;
		br_background.fill_color[1] = p;
		br_background.fill_color[2] = p;
	}
	else
	{
		br_background.fill_color[0] = 1.0f;
		br_background.fill_color[1] = 1.0f;
		br_background.fill_color[2] = 1.0f;
	}

	if (m_state->getPlayer()->isActive() && m_state->getPlayer()->isAttacking() && m_state->getPlayer()->get_Attack() >= 75) {

		float p = 0.5f + fabs(cos(graphics::getGlobalTime() / 1000.0f));
		br_background.fill_color[0] = 1.0f; 
		br_background.fill_color[1] = 0.0f; 
		br_background.fill_color[2] = p; 

	}

	for (auto& p : m_dynamic_objects) {
		if (p)
		{
			p->update(dt);
		}
	}

	if (!m_state->getPlayer()->isRight()) {
		m_weaponlevel.m_pos_x = m_state->getPlayer()->m_pos_x - 10;
		boxmove = -10;
	}
	if (m_state->getPlayer()->isRight()) {
		m_weaponlevel.m_pos_x = m_state->getPlayer()->m_pos_x +20;
		boxmove = 20;
	}
	
	m_weaponlevel.m_pos_y = m_state->getPlayer()->m_pos_y;
	GameObject::update(dt);
	
}
//------------------------------------init()----------------------------------------------------------
void Level::init()
{
	//brush background
	br_background.fill_color[0] = 1.0f;
	br_background.fill_color[1] = 1.0f;
	br_background.fill_color[2] = 1.0f;
	br_background.fill_opacity = 0.5f;
	br_background.texture = m_state->getFullAssetPath("background.png");

	level_map = loadFileMap(m_state->getPointerLevel());
	
	//for flying enemies
	this->enemySpawnTimerMax = 400.0f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;

	//blocks
	m_blocks.resize((level_map.size()));
	m_block_names.resize(level_map.size());

	for (int row = 0; row < level_map.size(); row++)
	{
		m_blocks[row].resize(level_map[row].size());
		m_block_names[row].resize(level_map[row].size());
		for (int col = 0; col < level_map[row].size(); col++)
		{
			if ((level_map[row][col])=='X')
			{
				float pos_x = col * m_block_size-1850;
				float pos_y = row * m_block_size;
				m_blocks[row][col] = Box(pos_x, pos_y, m_block_size, m_block_size);
				m_block_names[row][col] = "ground.png";
			}
			else if (level_map[row][col] == 'T')
			{
				float pos_x;
				if (col >= level_map.size() - 4) {
					pos_x = col * m_block_size - 1850 + 100;
				}
				else
				{
					pos_x = col * m_block_size - 1850 - 100;
				}
				float pos_y = row * m_block_size - 160;
				m_blocks[row][col] = Box(pos_x, pos_y, m_block_size, m_block_size * 3);
				m_block_names[row][col] = "tree_1.png";
			}
			else if (level_map[row][col] == 'R')
			{
				float pos_x = col * m_block_size - 1850;
				float pos_y = row * m_block_size+50 ;
				m_blocks[row][col] = Box(pos_x, pos_y, m_block_size, m_block_size);
				m_block_names[row][col] = "rock1.png";
			}
			else if (level_map[row][col] == 'G')
			{
				float pos_x = col * m_block_size - 1750;
				float pos_y = row * m_block_size;
				float pos_w_h = m_block_size / 2;
				m_blocks[row][col] = Box(pos_x, pos_y, m_block_size, m_block_size);
				m_block_names[row][col] = "gate1.png";
				indexframeGate = 0;
			}
			else if(level_map[row][col] == 'P')
			{
				float pos_x = col * m_block_size - 1850;
				float pos_y = row * m_block_size;
				float pw_h = m_block_size / 2.2;
				m_blocks[row][col] =Box(pos_x , pos_y, pw_h, pw_h);
				poisontype = new Poissons(m_state, rand() % PoisonType::NROFTYPES, pos_x, pos_y, pw_h, pw_h, "Poison");
				m_dynamic_objects.push_back(poisontype);
				m_block_names[row][col] ="poison1.png";
			}
			else if (level_map[row][col] == 'E') {
				float pos_x = col * m_block_size - 1850;
				float pos_y = row * m_block_size + 30 ;
				EnemyRock = new Rock(m_state, rand() % RockTyoe::NROFTYPES1, pos_x, pos_y, "RockEnemy", 600);
				m_Enemies.push_back(EnemyRock);
				m_blocks[row][col] = Box(pos_x, pos_y, EnemyRock->m_width, EnemyRock->m_height);
				m_block_names[row][col] = "rockEnemy1.png";
			}
			else if (level_map[row][col] == 'B') {
				
				float pos_x;
				if (col== (level_map[row].size()-1))
				{
					//RIGHT
					pos_x = col * m_block_size;
				}
				else 
				{
					//LEFT
					pos_x = col * m_block_size - 2000;
				}
				cout << "m_pos_x 1: " << pos_x << endl;
				float pos_y = row * m_block_size + 30;
				EnemyBird = new Bird(m_state, pos_x, pos_y, "Bird", 100);
				m_Enemies.push_back(EnemyBird);
				m_blocks[row][col] = Box(pos_x, pos_y, EnemyBird->m_width, EnemyBird->m_height);
				m_block_names[row][col] = "bird1.png";
			}
			else
			{
				m_blocks[row][col] = Box();
				m_block_names[row][col] = "";
			}
		}
	}
	
	for (auto& p : m_dynamic_objects)
	{
		if (p) {
			p->init();
		}
	}

	m_block_brush.outline_opacity = 0.0f;
	m_block_brush_debug.fill_opacity = 0.1f;
	m_block_brush_debug.fill_color[0] = 0.9f;
	m_block_brush_debug.fill_color[1] = 0.0f;
	m_block_brush_debug.fill_color[2] = 0.2f;
	m_block_brush_debug.outline_color[0] = 0.3f;
	m_block_brush_debug.outline_color[1] = 1.0f;
	m_block_brush_debug.outline_color[2] = 0.2f;

	//Animation gate
	m_gate= loadFileGameObject("gate");

	//brush for the weapon of the player	
	m_weaponlevel.m_pos_x = m_state->getPlayer()->m_pos_x;
	m_weaponlevel.m_pos_y = m_state->getPlayer()->m_pos_y;
	m_weaponlevel.m_width=90;
	m_weaponlevel.m_height=m_state->getPlayer()->m_height ;
	
	// Pink fill color
	br_weapon.fill_color[0] = 1.0f;
	br_weapon.fill_color[1] = 0.5f;
	br_weapon.fill_color[2] = 0.5f;
	br_weapon.fill_opacity = 0.2f;

	// Yellow outline color
	br_weapon.outline_opacity = 1.0f;
	br_weapon.outline_color[0] = 1.0f;
	br_weapon.outline_color[1] = 1.0f;
	br_weapon.outline_color[2] = 0.0f;


}
//------------------------------------draw()----------------------------------------------------------
void Level::draw()
{
	//background
	float offset_x = (m_state->m_global_offset_x / 2.0f) + (m_state->getCanvasWidth() / 2.0f);
	float offset_y = (m_state->m_global_offset_y / 2.0f) + (m_state->getCanvasHeight() / 2.0f);
	graphics::drawRect(offset_x, offset_y, m_state->getCanvasWidth() * 4.0f, m_state->getCanvasHeight() * 3.0f, br_background);

	//draw map
	for (int row = 0; row < level_map.size(); row++)
	{
		for (int col = 0; col < level_map[row].size(); col++)
		{
			drawBlock(row, col);
		}
	}
	
	for (auto& p : m_dynamic_objects)
	{
		//objects
		if (p->isActive())
		{
			p->draw();
		}
	}

	if (m_state->getPlayer()->isActive())
	{
		m_state->getPlayer()->draw();

	}

	for (auto& p : m_Enemies)
	{
		// enemies
		if (p->isActive())
		{
			p->draw();
		}
	}

	drawScore();

	if (m_state->m_debugging)
	{
		graphics::drawRect(m_state->getCanvasWidth() * 0.5f + boxmove, m_state->getCanvasHeight() * 0.5f, m_weaponlevel.m_width, m_weaponlevel.m_height, br_weapon);
	}
	
	
}
//------------------------------------loadFileMap()---------------------------------------------------
vector<vector<char>> Level::loadFileMap(int pointer)
{
	vector<vector<char>> level_map;
	std::ifstream inputFile(m_state->getFullAssetPath("Level" + std::to_string(pointer) + ".txt"));

	if (!inputFile.is_open()) {
		std::cerr << "Error opening the file." << std::endl;
	}

	std::string line;
	while (std::getline(inputFile, line)) {
		std::vector<char> row;

		for (char ch : line) {
			row.push_back(ch);
		}

		level_map.push_back(row);
	}
	inputFile.close();
	return level_map;

}
//------------------------------------drawBlock-------------------------------------------------------
void Level::drawBlock(int i, int j)
{
	if (m_block_names[i][j] != "")
	{
		Box& box = m_blocks[i][j];
		float x = box.m_pos_x + m_state->m_global_offset_x;
		float y = box.m_pos_y + m_state->m_global_offset_y;
		m_block_brush.texture = m_state->getFullAssetPath(m_block_names[i][j]);
		string path = "";
		for (char& c : m_block_names[i][j])
		{
			if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9' && c != '_') {
				path += c;
			}
			else
			{
				break;
			}
		}
		const char* paths = path.c_str();
		if (strcmp(paths, "poison") != 0 && strcmp(paths, "rockEnemy") != 0 && strcmp(paths, "bird") != 0)
		{

			if (strcmp(paths, "tree") == 0)
			{
				graphics::drawRect(x, y, m_block_size, m_block_size * 3, m_block_brush);
			}
			else if (strcmp(paths, "rock") == 0)
			{
				graphics::drawRect(x, y, m_block_size, m_block_size * 2, m_block_brush);
			}
			else if (strcmp(paths, "gate") == 0)
			{
				indexframeGate += 0.15;
				if (indexframeGate >= m_gate.size()) {
					indexframeGate = 0;
				}
				m_block_brush.texture = m_gate[int(indexframeGate)];
				graphics::drawRect(x, y, m_block_size * 2, m_block_size * 3, m_block_brush);
			}
			else
			{
				graphics::drawRect(x, y, m_block_size * 2.5, m_block_size * 11, m_block_brush);
			}
		}
		if (m_state->m_debugging)
		{
			if (strcmp(paths, "poison") != 0 && strcmp(paths, "rockEnemy") != 0 && strcmp(paths, "bird") != 0)
			{
				graphics::drawRect(x, y, box.m_width, box.m_height, m_block_brush_debug);
			}
		}
	}
}
//---------------------------------------updateEnemies------------------------------------------------
void Level::updateEnemies(float dt)
{
	if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
	{
		this->SpawnEnemy();
		this->enemySpawnTimer = 0.0f;
	}
	else
	{
		this->enemySpawnTimer += 1.f;
	}
}
//----------------------------------SpawnEnemy--------------------------------------------------------
void Level::SpawnEnemy()
{
	for (int row = 0; row < level_map.size(); row++)
	{
		for (int col = 0; col < level_map[row].size(); col++)
		{
			if (level_map[row][col] == 'B')
			{
				float pos_x = col * m_block_size - 2500;
				float pos_y = row * m_block_size + 30;
				EnemyBird = new Bird(m_state, pos_x, pos_y, "Bird", 50);
				this->m_Enemies.push_back(this->EnemyBird);
				m_dynamic_objects.push_back(EnemyBird);
				m_Enemies.push_back(EnemyBird);
			}
		}
	}
}
//----------------------------------checkCollisions---------------------------------------------------
void Level::checkCollisions()
{	
	
	//Floor
	for (int row = 0; row < level_map.size(); row++)
	{
		for (int col = 0; col < level_map[row].size(); col++)
		{
			float offset = 0.0f;
			if (level_map[row][col] == 'X')
			{
				Box block = m_blocks[row][col];
				if (offset = m_state->getPlayer()->intersectDown(block))
				{
					m_state->getPlayer()->m_pos_y += offset;
					
					if (m_state->getPlayer()->m_vy > 5.0f)
						graphics::playSound(m_state->getFullAssetPath("big_impact.wav"), 0.7f);
					m_state->getPlayer()->m_vy = 0.0f;
					break;
				}
			}
		}
	}
	//Gate
	for (int row = 0; row < level_map.size(); row++)
	{
		for (int col = 0; col < level_map[row].size(); col++)
		{
			float offset = 0.0f;
			if (level_map[row][col] == 'G') {
				Box block = m_blocks[row][col];
				if (offset = m_state->getPlayer()->intersect(block) && m_state->getPlayer()->isPickingUp())
				{
					if (m_state->getNextLevel())
					{
						break;
					}
					m_state->AddIndex();
					m_state->setNextLevel(true);
					break;
				}
			}
		}
	}
	//SideWays
	for (int row = 0; row < level_map.size(); row++) {
		for (int col = 0; col < level_map[row].size(); col++) {
			float offset = 0.0f;
			if(level_map[row][col] == 'T' || level_map[row][col] == 'X') {
				Box block = m_blocks[row][col];
				if(offset = m_state->getPlayer()->intersectSideways(block))
				{
					m_state->getPlayer()->m_pos_x += offset;
					m_state->getPlayer()->m_vx = 0.0f;
					break;
				}
			}
		}
	}
	//wall
	for (int row = 0; row < level_map.size(); row++) {
		for (int col = 0; col < level_map[row].size(); col++) {
			float offset = 0.0f;
			if (level_map[row][col] == 'X') {
				Box block = m_blocks[row][col];
				if ((m_state->getPlayer()->insertUp(block) && !m_state->getPlayer()->intersectSideways(block)) && ((m_state->getPlayer()->insertUp(block) && !m_state->getPlayer()->intersectDown(block)))){
					if (m_state->getPlayer()->m_vy > -85)
					{
						m_state->getPlayer()->m_pos_y = block.m_pos_y + block.m_height - 0.1;
						m_state->getPlayer()->m_vy += m_state->getPlayer()->delta_time * m_state->getPlayer()->getGravity();
						m_state->getPlayer()->m_pos_y += m_state->getPlayer()->m_vy * m_state->getPlayer()->delta_time;
						break;
					}
				}
			}
		}
	}

}
//----------------------------------checkCollisionWithEnemies-----------------------------------------
void Level::checkCollisionWithEnemies(float dt)
{
	for (int i = 0; i < this->m_Enemies.size(); i++)
	{
		this->m_Enemies[i]->update(dt);
		float offset = 0.0f;
		if (this->m_Enemies[i]->isActive() && m_state->getPlayer()->isAttacking())
		{
			if (m_weaponlevel.intersect(*(m_Enemies[i]))) {
				updateScore(100 + rand() % 251);
				if (m_state->getPlayer()->isRight()) {
					//left
					this->m_Enemies[i]->m_pos_x += offset + 50;
				}
				else
				{
					//right
					this->m_Enemies[i]->m_pos_x += offset - 50;
				}
				graphics::playSound(m_state->getFullAssetPath("Attack.wav"), 1.0f);
				if (m_state->getPlayer()->PlusAttack()) {
					this->m_Enemies[i]->Damage(m_state->getPlayer()->get_Attack() * 2);
					m_state->getPlayer()->setPlusAttack(false);
				}
				else {
					if (m_state->getPlayer()->isActive()) {
						this->m_Enemies[i]->Damage(m_state->getPlayer()->get_Attack());
					}
				}
				if (this->m_Enemies[i]->getDead())
				{
					updateScore(250 + rand() % 501);
					graphics::playSound(m_state->getFullAssetPath("death_enemy.wav"), 1.0f);
				}
			}
		}
	}
}
//-----------------------------------------------drawScore()------------------------------------------
void Level::drawScore()
{
	graphics::resetPose();
	graphics::drawText(45, 200, 50, "Score: ", br_background);
	char score[20];
	sprintf_s(score, "( %5.2f )", getScore());
	graphics::drawText(265, 200, 50, score, br_background);
}
//------------------------------------setScore()------------------------------------------------------
void Level::setScore(float score)
{
	m_score = score;
}
//------------------------------------getScore()------------------------------------------------------
float Level::getScore()
{
	return m_score;
}
//-------------------------------------updateScore()--------------------------------------------------
Level& Level::updateScore(float score)
{
	m_score += score;
	return *this;
}
//--------------------------------Destructor----------------------------------------------------------
Level::~Level()
{
	// Delete static objects
	for (auto& blocks : m_blocks) 
	{
		blocks.clear();
	}
	m_blocks.clear();

	// Delete char 
	for (auto& map : level_map)
	{
		map.clear();
	}
	level_map.clear();

	// Delete string names
	for (auto& blocks_n: m_block_names)
	{
		blocks_n.clear();
	}
	m_block_names.clear();

	// Delete dynamic objects
	for (auto& dynamicObj : m_dynamic_objects)
	{
		delete dynamicObj;
	}
	m_dynamic_objects.clear();

	// Delete birds
	for (auto& enemies : m_Enemies) {
		delete enemies;
	}
	m_Enemies.clear();

	delete poisontype;
	delete EnemyBird;
	delete EnemyRock;
}
//----------------------------------------------------------------------------------------------------