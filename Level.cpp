#pragma once
#include "GameState.h"
#include "Level.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include "Enemy.h"
#include "Blocks.h"
#include "Rock.h"
#include "Bird.h"
class Poissons;

using namespace std;
//------------------------------------Constructor---------------------------------------------------
Level::Level(GameState* gs, const string name,float score) :GameObject(gs, name)
{
	namelevel = name;
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
	//collisionInstance->DownCollision();
	//collisionInstance->SideCollision();

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

	//ANGRY ENEMY
	if (m_state->getPlayer()->isActive() && m_state->getPlayer()->isAttacking() && m_state->getPlayer()->get_Attack() >= 75) {

		//flash
		float p = 0.5f + fabs(cos(graphics::getGlobalTime() / 1000.0f));
		br_background.fill_color[0] = p;
		br_background.fill_color[1] = p;
		br_background.fill_color[2] = 0.5f;
	}

	for (auto& p : m_dynamic_objects) {
		//objects
		if (p) {
			p->update(dt);
		}
	}

	GameObject::update(dt);
}
//------------------------------------init()--------------------------------------------------------
void Level::init()
{
	//brush background
	br_background.fill_color[0] = 1.0f;
	br_background.fill_color[1] = 1.0f;
	br_background.fill_color[2] = 1.0f;
	br_background.fill_opacity = 0.5f;
	br_background.texture = m_state->getFullAssetPath("background.png");

	//keep score
	if (m_name == "level-1") {
		this->m_score = 0;
	}

	//for flying enemies
	this->enemySpawnTimerMax = 10.0f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 20;

	//blocks
	m_blocks.resize(level_map.size());
	m_block_names.resize(level_map.size());

	for (int row = 0; row < level_map.size(); row++)
	{
		m_blocks[row].resize(level_map[row].size());
		m_block_names[row].resize(level_map[row].size());
		for (int col = 0; col < level_map[row].size(); col++)
		{
			if (level_map[row][col] == 'X')
			{
				float pos_x = col * m_block_size-1850;
				float pos_y = row * m_block_size;
				m_blocks[row][col] = Blocks(pos_x, pos_y, m_block_size, m_block_size);
				m_block_names[row][col] = "ground.png";
			}
			else if (level_map[row][col] == 'T')
			{
				float pos_x;
				if (col >= level_map.size() - 4){
					pos_x = col * m_block_size - 1850 +100;
				}
				else {
					pos_x = col * m_block_size - 1850 -170;
				}
				float pos_y = row * m_block_size  -150;
				m_blocks[row][col] = Blocks(pos_x, pos_y, m_block_size, m_block_size*3);
				m_block_names[row][col] = "tree_1.png";
			}
			else if (level_map[row][col] == 'R')
			{
				float pos_x = col * m_block_size - 1850;
				float pos_y = row * m_block_size+70 ;
				m_blocks[row][col] = Blocks(pos_x, pos_y, m_block_size, m_block_size);
				m_block_names[row][col] = "rock1.png";
			}
			else if (level_map[row][col] == 'G')
			{
				float pos_x = col * m_block_size - 1750;
				float pos_y = row * m_block_size;
				float pos_w_h = m_block_size / 2;
				m_blocks[row][col] = Blocks(pos_x, pos_y, m_block_size, m_block_size);
				m_block_names[row][col] = "gate1.png";
				indexframeGate = 0;
			}
			else if(level_map[row][col] == 'P')
			{
				float pos_x = col * m_block_size - 1850;
				float pos_y = row * m_block_size+50;
				m_blocks[row][col] =Blocks(pos_x , pos_y, m_block_size, m_block_size);
				poisontype = new Poissons(m_state, rand() % PoisonType::NROFTYPES, pos_x, pos_y, m_block_size,m_block_size , "Poison");
				m_dynamic_objects.push_back(poisontype);
				m_poissons.push_back(poisontype);
				m_block_names[row][col] ="poison1.png";
			}
			else if (level_map[row][col] == 'E') {
				float pos_x = col * m_block_size - 1850;
				float pos_y = row * m_block_size + 30 ;
				EnemyRock = new Rock(m_state, pos_x, pos_y, "RockEnemy", 500);
				m_dynamic_objects.push_back(EnemyRock);
				m_rocks.push_back(EnemyRock);
				m_blocks[row][col] = Blocks(pos_x, pos_y, EnemyRock->m_width, EnemyRock->m_height);
				m_block_names[row][col] = "rockEnemy1.png";
			}
			else
			{
				m_blocks[row][col] = Blocks();
				m_block_names[row][col] = "";
			}
		}
	}
	for (auto& p : m_static_objects) {
		if (p) {
			//objects
			p->init();
		}
	}
	
	for (auto& p : m_dynamic_objects) {
		//objects
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

	//try animation gate 
	m_gate.push_back(m_state->getFullAssetPath("gate1.png"));
	m_gate.push_back(m_state->getFullAssetPath("gate2.png"));
	m_gate.push_back(m_state->getFullAssetPath("gate3.png"));
	m_gate.push_back(m_state->getFullAssetPath("gate4.png"));
	m_gate.push_back(m_state->getFullAssetPath("gate5.png"));
	m_gate.push_back(m_state->getFullAssetPath("gate6.png"));
	m_gate.push_back(m_state->getFullAssetPath("gate7.png"));
	m_gate.push_back(m_state->getFullAssetPath("gate8.png"));
	m_gate.push_back(m_state->getFullAssetPath("gate9.png"));
	m_gate.push_back(m_state->getFullAssetPath("gate10.png"));
	m_gate.push_back(m_state->getFullAssetPath("gate11.png"));
	m_gate.push_back(m_state->getFullAssetPath("gate12.png"));

	//brush for the weapon of the player
	m_weaponlevel = Box(m_state->getCanvasWidth() * 0.5f + 40, m_state->getCanvasHeight() * 0.5f, 90, m_state->getPlayer()->m_height*2);
	//pink
	br_weapon.fill_color[0] = 1.0f;
	br_weapon.fill_color[1] = 0.5f;
	br_weapon.fill_color[2] = 0.5f;
	br_weapon.fill_opacity = 0.2f;

	//white
	br_weapon.outline_opacity = 0.0f;
	br_weapon.outline_color[0] = 1.0f;
	br_weapon.outline_color[1] = 1.0f;
	br_weapon.outline_color[2] = 1.0f;

	graphics::drawRect(m_state->getCanvasWidth() * 0.5f + 40, m_state->getCanvasHeight() * 0.5f, 75, m_state->getPlayer()->m_height, br_weapon);

}
//------------------------------------draw()--------------------------------------------------------
void Level::draw()
{
	//background
	float offset_x = (m_state->m_global_offset_x / 2.0f) + (m_state->getCanvasWidth() / 2.0f);
	float offset_y = (m_state->m_global_offset_y / 2.0f) + (m_state->getCanvasHeight() / 2.0f);
	graphics::drawRect(offset_x, offset_y, m_state->getCanvasWidth() * 4.0f, m_state->getCanvasHeight()*3.0f, br_background);
	
	//draw map
	for (int row = 0; row < level_map.size(); row++)
	{
		for (int col = 0; col < level_map[row].size(); col++)
		{
			drawBlock(row, col);
		}
	}

	for (auto& p : m_static_objects)
	{
		if (p)
		{
			//objects
			p->draw();
		}
	}
	for (auto& p : m_poissons)
	{
		//objects
		if (p->isActive())
		{
			p->draw();
		}
	}
	//player 
	if (m_state->getPlayer()->isActive())
	{
		m_state->getPlayer()->draw();
		char s[20];
		sprintf_s(s, "(%5.2f, %5.2f)", m_state->getPlayer()->getPosX(), m_state->getPlayer()->getPosY());
		graphics::drawText(45, 200, 50, "Position: ", br_background);
		graphics::drawText(240, 200, 50, s, br_background);
		
	}

	for (auto& p : m_dynamic_objects)
	{
		//objects
		if (p->isActive())
		{
			p->draw();
		}
	}

	//enemies
	drawEnemies();
	
	for (auto& p : m_rocks)
	{
		//rocks enemies
		if (p->isActive())
		{
			p->draw();
		}
	}
	drawScore();
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f + 40, m_state->getCanvasHeight() * 0.5f, 75, m_state->getPlayer()->m_height, br_weapon);

}
//------------------------------------blocks-------------------------------------------------------
void Level::drawBlock(int i, int j)
{
	if (m_block_names[i][j] != "")
	{
		Box& box = m_blocks[i][j];
		float x = box.m_pos_x + m_state->m_global_offset_x;
		float y = box.m_pos_y + m_state->m_global_offset_y;
		m_block_brush.texture = m_state->getFullAssetPath(m_block_names[i][j]);
		string path = "";
		for (char& c : m_block_names[i][j]) {
			if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9' && c != '_') {
				path += c;
			}
			else
			{
				break;
			}
		}
		string tree = "tree";
		string gate = "gate";
		string rock = "rock";
		string poison = "poison";
		string enemy = "rockEnemy";
		if (path != poison && path != enemy) {

			if (path == tree) {
				graphics::drawRect(x, y, m_block_size, m_block_size * 3, m_block_brush);
			}
			else if (path == rock) {
				graphics::drawRect(x, y, m_block_size, m_block_size * 2, m_block_brush);
			}
			else if (path == gate)
			{
				indexframeGate += 0.05;
				if (indexframeGate >= m_gate.size()) {
					indexframeGate = 0;
				}
				m_block_brush.texture = m_gate[int(indexframeGate)];
				graphics::drawRect(x, y, m_block_size * 2, m_block_size * 3, m_block_brush);
			}
			else//ground
			{
				graphics::drawRect(x, y, m_block_size*2, m_block_size, m_block_brush);
			}
		}
		if (m_state->m_debugging)
		{
			if (path != poison && path != enemy) {
				graphics::drawRect(x, y, box.m_width, box.m_height, m_block_brush_debug);
			}
		}
	}
}
//----------------------------------------enemy bird-----------------------------------------------
void Level::drawEnemies()
{
	for (auto& p : m_birds) {
		//objects
		if (p->isActive()) {
			p->draw();
		}
	}
}
//---------------------------------------updateEnemies---------------------------------------------
void Level::updateEnemies(float dt)
{
	if (this->m_birds.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer>= this->enemySpawnTimerMax)
		{
			this->SpawnEnemy();
			this->enemySpawnTimer = 0.0f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}
	for (int i = 0; i < this->m_birds.size(); i++)
	{
		this->m_birds[i]->update(dt);
		
		if (m_state->getPlayer()->intersectSideways(*(m_birds[i])))
		{
			cout<<"Active bird:" << this->m_birds[i]->isActive();
			if (this->m_birds[i]->isActive() && m_state->getPlayer()->isAttacking()){
				updateScore(100);
				graphics::playSound(m_state->getFullAssetPath("Attack.wav"), 1.0f);
				if (!this->m_birds[i]->isActive()) {
					updateScore(200);
					
					m_birds[i]->Damage(m_state->getPlayer()->get_Attack());
					cout << m_birds[i]->getHealth();
					//graphics::playSound(m_state->getFullAssetPath("attacksound.wav"), 1.0f);

				}
			}
			
			if (this->m_birds[i]->isActive() && !m_state->getPlayer()->isAttacking()) {
				graphics::playSound(m_state->getFullAssetPath("notAttack.wav"), 1.0f);
				m_state->getPlayer()->Damage(this->m_birds[i]->getAttack());

			}
			
		}
		if (!this->m_birds[i]->isActive()) {
			m_birds[i]->setActive(false);
			this->m_birds.erase(this->m_birds.begin() + i);
		}	
	}
}
//----------------------------------SpawnEnemy---------------------------------------------------
void Level::SpawnEnemy()
{
	EnemyBird = new Bird(m_state, "Bird");
	this->m_birds.push_back(this->EnemyBird);
}
//----------------------------------checkCollisions----------------------------------------------
void Level::checkCollisions()
{	
	for (int row = 0; row < level_map.size(); row++)
	{
		for (int col = 0; col < level_map[row].size(); col++)
		{
			float offset = 0.0f;
			if (level_map[row][col] == 'X') 
			{
				Blocks block = m_blocks[row][col];
				if (offset = m_state->getPlayer()->intersectDown(block))
				{
					m_state->getPlayer()->m_pos_y += offset;

					// add sound event
					//if (m_state->getPlayer()->m_vy > 1.0f)
					if(m_state->getPlayer()->isJumping() && !m_state->getPlayer()->isGrounding())
						graphics::playSound(m_state->getFullAssetPath("big_impact.wav"), 1.0f);

					m_state->getPlayer()->m_vy = 0.0f;

					break;
				}
			}
			if (level_map[row][col] == 'G') {
				Blocks block = m_blocks[row][col];
				if (offset = m_state->getPlayer()->intersect(block) && m_state->getPlayer()->isPickingUp())
				{
					next_level = true;
					break;
				}
			}
		}
	}
	
	for (int row = 0; row < level_map.size(); row++) {
		for (int col = 0; col < level_map[row].size(); col++) {
			float offset = 0.0f;
			if(level_map[row][col] == 'T' || level_map[row][col] == 'X') {
				Blocks block = m_blocks[row][col];
				if(offset = m_state->getPlayer()->intersectSideways(block))
				{
					m_state->getPlayer()->m_pos_x += offset;
					m_state->getPlayer()->m_vx = 0.0f;
					break;
				}
			}
		}
	}
}
//----------------------------------checkCollisionWithEnemies-------------------------------------
void Level::checkCollisionWithEnemies(float dt)
{
	for (int i = 0; i < this->m_rocks.size(); i++)
	{
		this->m_rocks[i]->update(dt);
		if (this->m_rocks[i]->isActive())
		{
			if (m_weaponlevel.intersect(*(m_rocks[i]))) {
				cout << "*";
			}
		}
	}

	for (int i = 0; i < this->m_rocks.size(); i++)
	{
		this->m_rocks[i]->update(dt);
		if (this->m_rocks[i]->isActive())
		{

			float offset = 0.0f;
			//----------------
			if (offset = m_state->getPlayer()->intersectSideways(*(m_rocks[i])))
			{
				//cout << "yes" << endl;
				m_state->getPlayer()->m_pos_x -= offset;
				if (m_rocks[i]->getSpeed() < 0) {
					m_rocks[i]->m_pos_x += offset + 150;
				}
				else
				{
					m_rocks[i]->m_pos_x += offset - 150;
				}
				if (this->m_rocks[i]->isActive() && m_state->getPlayer()->isAttacking())
				{
					updateScore(250);
					graphics::playSound(m_state->getFullAssetPath("Attack.wav"), 1.0f);
					if (m_state->getPlayer()->PlusAttack()) {
						this->m_rocks[i]->Damage(m_state->getPlayer()->get_Attack() * 2);
						m_state->getPlayer()->setPlusAttack(false);
					}
					else {
						
						this->m_rocks[i]->Damage(m_state->getPlayer()->get_Attack());
						
					}
					if (!this->m_rocks[i]->isActive())
					{
						updateScore(500);
						graphics::playSound(m_state->getFullAssetPath("death_enemy.wav"), 1.0f);
					}
				}
				if (this->m_rocks[i]->isActive() && !m_state->getPlayer()->isAttacking())
				{
					graphics::playSound(m_state->getFullAssetPath("notAttack.wav"), 1.0f);
					m_state->getPlayer()->Damage(this->m_rocks[i]->getAttack());
				}
				m_state->getPlayer()->m_vx = 0.0f;
				break;
			}
			//------------------------------------------------------------------------------
			/*
			offset = 0.0f;

			if (m_state->getPlayer()->isActiveWeapon())
			{
				cout << "yes" << endl;
				cout << m_weapon.intersectSideways(*(m_rocks[i])) << endl;
				if (offset =m_weapon.intersectSideways(*(m_rocks[i])))
				{
					cout << "yes                        2                " << endl;
					//m_state->getPlayer()->m_pos_x -= offset;
					if (m_rocks[i]->getSpeed() < 0) {
						m_rocks[i]->m_pos_x += offset + 150;
					}
					else
					{
						m_rocks[i]->m_pos_x += offset - 150;
					}
					if (this->m_rocks[i]->isActive() && m_state->getPlayer()->isAttacking())
					{
						updateScore(250);
						graphics::playSound(m_state->getFullAssetPath("Attack.wav"), 1.0f);
						if (m_state->getPlayer()->PlusAttack()) {
							this->m_rocks[i]->Damage(m_state->getPlayer()->get_Attack() * 2);
							m_state->getPlayer()->setPlusAttack(false);
						}
						else {
							cout << "before:     " << this->m_rocks[i]->getHealth() << endl;
							this->m_rocks[i]->Damage(m_state->getPlayer()->get_Attack());
							cout << "after:     " << this->m_rocks[i]->getHealth() << endl;
						}
						if (!this->m_rocks[i]->isActive())
						{
							updateScore(500);
							graphics::playSound(m_state->getFullAssetPath("death_enemy.wav"), 1.0f);
						}
					}
					break;
				}
			}
			
			*/
			
		}
	}

	for (int i = 0; i < this->m_rocks.size(); i++)
	{
		this->m_rocks[i]->update(dt);
		if (this->m_rocks[i]->isActive())
		{
			float offset = 0.0f;
			if (m_state->getPlayer()->intersectDown(*(m_rocks[i])))
			{
				m_state->getPlayer()->m_pos_y += offset - 150;
				updateScore(150);
				graphics::playSound(m_state->getFullAssetPath("Attack.wav"), 1.0f);
				if (m_state->getPlayer()->PlusAttack())
				{
					this->m_rocks[i]->Damage(m_state->getPlayer()->get_Attack() * 2);
					m_state->getPlayer()->setPlusAttack(false);
				}
				else
				{
					this->m_rocks[i]->Damage(m_state->getPlayer()->get_Attack());
				}
				if (!this->m_rocks[i]->isActive())
				{
					updateScore(600);
					graphics::playSound(m_state->getFullAssetPath("notAttack.wav"), 1.0f);

				}
				m_state->getPlayer()->m_vy = 0.0f;
				break;
			}
		}
	}
}
//-----------------------------------------------drawScore()----------------------------------------
void Level::drawScore()
{
	graphics::resetPose();
	graphics::drawText(45, 300, 50, "Score: ", br_background);
	char score[20];
	sprintf_s(score, "(%5.2f)", getScore());
	graphics::drawText(265, 300, 50, score, br_background);
}
//------------------------------------setScore()----------------------------------------------------
void Level::setScore(float score)
{
	m_score = score;
}
//------------------------------------getScore()----------------------------------------------------
float Level::getScore()
{
	return m_score;
}
//-------------------------------------updateScore()------------------------------------------------
Level& Level::updateScore(float score)
{
	m_score += score;
	return *this;
}
//--------------------------------Destructor---------------------------------------------------------
Level::~Level()
{
	// Delete dynamic objects
	for (auto dynamicObj : m_dynamic_objects) {
		delete dynamicObj;
	}
	m_dynamic_objects.clear();

	// Delete block enemies
	for (auto blockEnemy : m_block_enemies) {
		delete blockEnemy;
	}
	m_block_enemies.clear();

	// Delete birds
	for (auto bird : m_birds) {
		delete bird;
	}
	m_birds.clear();

	// Delete rocks
	for (auto rock : m_rocks) {
		delete rock;
	}
	m_rocks.clear();

	// Delete poissons
	for (auto poisson : m_poissons) {
		delete poisson;
	}
	m_poissons.clear();
}