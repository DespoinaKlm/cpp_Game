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
		br_background.fill_color[0] = p;
		br_background.fill_color[1] = p;
		br_background.fill_color[2] = 0.5f;
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
	NextLevel(getScore(),m_state->getPlayer()->get_Health());
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
	this->enemySpawnTimerMax = 80.0f;
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
				float pos_y = row * m_block_size+50 ;
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
				float pos_y = row * m_block_size;
				float pw_h = m_block_size / 2.2;
				m_blocks[row][col] =Blocks(pos_x , pos_y, pw_h, pw_h);
				poisontype = new Poissons(m_state, rand() % PoisonType::NROFTYPES, pos_x, pos_y, pw_h, pw_h, "Poison");
				m_dynamic_objects.push_back(poisontype);
				m_block_names[row][col] ="poison1.png";
			}
			else if (level_map[row][col] == 'E') {
				float pos_x = col * m_block_size - 1850;
				float pos_y = row * m_block_size + 30 ;
				EnemyRock = new Rock(m_state, rand() % RockTyoe::NROFTYPES1, pos_x, pos_y, "RockEnemy", 600);
				m_dynamic_objects.push_back(EnemyRock);
				m_Enemies.push_back(EnemyRock);
				m_blocks[row][col] = Blocks(pos_x, pos_y, EnemyRock->m_width, EnemyRock->m_height);
				m_block_names[row][col] = "rockEnemy1.png";
			}
			else if (level_map[row][col] == 'B') {
				float pos_x = col * m_block_size - 2500;
				float pos_y = row * m_block_size + 30;
				EnemyBird = new Bird(m_state, pos_x, pos_y, "Bird", 50);
				m_dynamic_objects.push_back(EnemyBird);
				m_Enemies.push_back(EnemyBird);
				m_blocks[row][col] = Blocks(pos_x, pos_y, EnemyBird->m_width, EnemyBird->m_height);
				m_block_names[row][col] = "bird1.png";
			}
			else
			{
				m_blocks[row][col] = Blocks();
				m_block_names[row][col] = "";
			}
		}
	}
	
	for (auto& p : m_static_objects)
	{
		if (p) {
			p->init();
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

	for (auto& p : m_static_objects)
	{
		if (p)
		{
			//objects
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
//------------------------------------loadFileMap()----------------------------------------------------------
vector<vector<char>> Level::loadFileMap(int pointer)
{
	vector<vector<char>> level_map;
	std::ifstream inputFile(m_state->getFullAssetPath("Level" + std::to_string(pointer) + ".txt"));
	cout << "Level" + std::to_string(pointer) + ".txt" << endl;

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
	//ektypwse to level
	for (const auto& row : level_map) {
		for (char ch : row) {
			std::cout << ch;
		}
		std::cout << std::endl;
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
		const char* tree = "tree";
		const char* gate = "gate";
		const char* rock = "rock";
		const char* poison = "poison";
		const char* enemy = "rockEnemy";
		const char* bird = "bird";
		if (strcmp(paths, poison) != 0 && strcmp(paths, enemy) != 0 && strcmp(paths,bird)!=0)
		{

			if (strcmp(paths, tree)== 0)
			{
				graphics::drawRect(x, y, m_block_size, m_block_size * 3, m_block_brush);
			}
			else if (strcmp(paths, rock) == 0)
			{
				graphics::drawRect(x, y, m_block_size, m_block_size * 2, m_block_brush);
			}
			else if (strcmp(paths, gate) == 0)
			{
				indexframeGate += 0.30;
				if (indexframeGate >= m_gate.size()) {
					indexframeGate = 0;
				}
				m_block_brush.texture = m_gate[int(indexframeGate)];
				graphics::drawRect(x, y, m_block_size * 2, m_block_size * 3, m_block_brush);
			}
			else
			{
				graphics::drawRect(x, y, m_block_size * 2.5, m_block_size * 10, m_block_brush);
			}
		}
		if (m_state->m_debugging)
		{
			if (strcmp(paths, poison) != 0 && strcmp(paths, enemy) != 0 && strcmp(paths, bird) != 0)
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
	//wall
	for (int row = 0; row < level_map.size(); row++) {
		for (int col = 0; col < level_map[row].size(); col++) {
			float offset = 0.0f;
			if (level_map[row][col] == 'X') {
				Blocks block = m_blocks[row][col];
				if (m_state->getPlayer()->insertUp(block) && !m_state->getPlayer()->intersectSideways(block) && !m_state->getPlayer()->intersectDown(block)) {
					//cout<<m_state->getPlayer()->insertUp(block);
					//cout << " find the differences " << m_state->getPlayer()->intersectDown(block) << endl;
					//cout << "Up up" << endl;
					if (m_state->getPlayer()->m_vy < 0) {
						m_state->getPlayer()->m_pos_y = block.m_pos_y + block.m_height - 0.1;
				
						m_state->getPlayer()->m_vy += m_state->getPlayer()->delta_time * m_state->getPlayer()->getGravity();
						m_state->getPlayer()->m_pos_y += m_state->getPlayer()->m_vy * m_state->getPlayer()->delta_time;
						//cout << m_state->getPlayer()->m_vy << endl;
						break;
					}
				}
				if(m_state->getPlayer()->insertUp(block) && m_state->getPlayer()->intersectSideways(block))
				{
					//cout << "hihi" << endl;
					break;
				}
				if (m_state->getPlayer()->insertUp(block) && m_state->getPlayer()->intersectDown(block))
				{
					//cout << "hoho" << endl;
					break;
				}
			}
		}
	}
	//Floor
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
					
					if (m_state->getPlayer()->m_vy > 5.0f)
						graphics::playSound(m_state->getFullAssetPath("big_impact.wav"), 1.0f);
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
				Blocks block = m_blocks[row][col];
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
	/*
	for (auto& item : m_dynamic_objects) {
		float offset = 0.0f;
		if (item->isActive() && m_state->getPlayer()->isAttacking())
			{
				if (m_weaponlevel.intersect()
				{
					updateScore(100 + rand() % 251);
					if (m_state->getPlayer()->isRight()) {
						//left
						m_rocks[i]->m_pos_x += offset + 50;
					}
					else
					{
						//right
						m_rocks[i]->m_pos_x += offset - 50;
					}
					graphics::playSound(m_state->getFullAssetPath("Attack.wav"), 1.0f);
					if (m_state->getPlayer()->PlusAttack()) {
						this->m_rocks[i]->Damage(m_state->getPlayer()->get_Attack() * 2);
						m_state->getPlayer()->setPlusAttack(false);
					}
					else {
						if (m_state->getPlayer()->isActive()) {
							this->m_rocks[i]->Damage(m_state->getPlayer()->get_Attack());
						}
					}
					if (!this->m_rocks[i]->isActive())
					{
						cout << "yes: " << this->m_rocks[i]->isActive() << endl;
						updateScore(250 + rand() % 501);
						graphics::playSound(m_state->getFullAssetPath("death_enemy.wav"), 1.0f);
					}
				}
			}
		}
		
	}
}
	*/
	
	/*
	for (auto& p: m_dynamic_objects) {
		cout << p->getName() << endl;
		const char* name = p->getName().c_str();
		const char* nameEnemy = "RockEnemy";
		if (strcmp(name, nameEnemy) == 0) {
			p->update(dt);
			float offset = 0.0f;
			if (p->isActive() && m_state->getPlayer()->isAttacking())
			{
				if (m_weaponlevel.intersect(p))
				{
					updateScore(100 + rand() % 251);
					if (p->getSpeed() < 0) {
						p->m_pos_x += offset + 150;
					}
					else
					{
						p->m_pos_x += offset - 150;
					}
					graphics::playSound(m_state->getFullAssetPath("Attack.wav"), 1.0f);
					if (m_state->getPlayer()->PlusAttack()) {
						p->Damage(m_state->getPlayer()->get_Attack() * 2);
						m_state->getPlayer()->setPlusAttack(false);
					}
					else {
						p->Damage(m_state->getPlayer()->get_Attack());
					}
					if (p->getDead())
					{
						updateScore(250 + rand() % 501);
						graphics::playSound(m_state->getFullAssetPath("death_enemy.wav"), 1.0f);
					}
				}
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//they work
	

	for (int i = 0; i < this->m_rocks.size(); i++)
	{
		this->m_rocks[i]->update(dt);
		float offset = 0.0f;
		if (this->m_rocks[i]->isActive() && m_state->getPlayer()->isAttacking())
		{
			
			if (m_weaponlevel.intersect(*(m_rocks[i]))){
				updateScore(100 + rand() % 251);
				if (m_rocks[i]->getSpeed() < 0) {
					//left
					m_rocks[i]->m_pos_x += offset + 50;
				}
				else
				{
					//right
					m_rocks[i]->m_pos_x += offset - 50;
				}
				graphics::playSound(m_state->getFullAssetPath("Attack.wav"), 1.0f);
				if (m_state->getPlayer()->PlusAttack()) {
					this->m_rocks[i]->Damage(m_state->getPlayer()->get_Attack() * 2);
					m_state->getPlayer()->setPlusAttack(false);
				}
				else {
					if (m_state->getPlayer()->isActive()) {
						this->m_rocks[i]->Damage(m_state->getPlayer()->get_Attack());
					}
				}
				if (!this->m_rocks[i]->isActive())
				{
					cout <<"yes: " << this->m_rocks[i]->isActive() << endl;
					updateScore(250 + rand() % 501);
					graphics::playSound(m_state->getFullAssetPath("death_enemy.wav"), 1.0f);
				}
			}
		}
	}

	for (int i = 0; i < this->m_rocks.size(); i++)
	{
		this->m_rocks[i]->update(dt);
		if (this->m_rocks[i]->isActive())
		{
			if (m_state->getPlayer()->isActive()) {
				float offset = 0.0f;
				if (offset = m_state->getPlayer()->intersectSideways(*(m_rocks[i])))
				{
					updateScore((10 + rand() % 50) * -1);
					if (m_rocks[i]->getSpeed() < 0) {
						m_rocks[i]->m_pos_x += offset + 50;
						m_state->getPlayer()->m_pos_x += offset - 50;
					}
					else
					{
						m_state->getPlayer()->m_pos_x += offset + 50;
						m_rocks[i]->m_pos_x += offset - 50;
					}
					if (!this->m_rocks[i]->getCantAttack() && !m_state->getPlayer()->isAttacking())
					{
						graphics::playSound(m_state->getFullAssetPath("notAttack.wav"), 1.0f);
						m_state->getPlayer()->Damage(this->m_rocks[i]->getAttack());
					}
					m_state->getPlayer()->m_vx = 0.0f;
					break;
				}
			}
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
				updateScore(10 + rand() % 151);
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
					updateScore(100 + rand() % 350);
					graphics::playSound(m_state->getFullAssetPath("notAttack.wav"), 1.0f);

				}
				m_state->getPlayer()->m_vy = 0.0f;
				break;
			}
		}
	}*/
}
//-----------------------------------------------drawScore()------------------------------------------
void Level::drawScore()
{
	graphics::resetPose();
	graphics::drawText(45, 300, 50, "Score: ", br_background);
	char score[20];
	sprintf_s(score, "(%5.2f)", getScore());
	graphics::drawText(265, 300, 50, score, br_background);
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
//------------------------------------NextLevel()-----------------------------------------------------
void Level::NextLevel(float score, float health)
{
	if (m_state->getNextLevel())
	{
		setScore(m_score);
		m_state->getPlayer()->set_Health(health);
	}
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
	for (auto& blocks : m_blocks) 
	{
		blocks.clear();
	}
	m_blocks.clear();

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