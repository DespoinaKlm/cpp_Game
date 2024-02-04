#pragma once
#include <sgg/graphics.h>
#include "GameState.h"
#include "GameObject.h"
#include "Player.h"
#include <iostream>
#include <cmath>
#include "Collision.h"
#include "Level.h"
#include "Animation.h"
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include "Blocks.h"

using namespace std;
//----------------------------------------Constructor---------------------------------
Player::Player(GameState* gs, const string& name, float health):GameObject(gs, name), m_health(health)
{
	m_IsJumping=false;
	m_IsRunning=false;
	m_Attacking=false;
	plusAttack= false;
	m_Falling = false;
	m_Grounding=false;
	weaponIsActive = false;
	cantMove = false;
	m_health = health;
	rigit = new Rigit_Body_Physics;
	rigit->setGravity(3.0f);
	JumpTime = jump_time;
	JumpForce = jump_force;
	m_AttackingTime =Attack_time;

	if (!collisionInstance) {
		collisionInstance = Collision::getCollision();
	}
	if (!animationInstance) {
		animationInstance = Animation::getInstance();
	}
}
//----------------------------------------loadFileIntoVector--------------------------------------------
vector<string> Player::loadFileIntoVector(const std::string& filePath, std::string player, std::string movement)
{
	vector<std::string> fileContents;
	ifstream inputFile(filePath);
	if (inputFile.is_open()) {
		std::string line;
		while (std::getline(inputFile, line))
		{
			if (line.find(movement) != std::string::npos)
			{
				//string inp = m_state->getFullAssetPath(line);
				fileContents.push_back(m_state->getFullAssetPath(line));
				cout << fileContents.size() << ": " << line << endl;
			}
		}
	}
	else
	{
		cerr << "failed to open the file" << endl;
	}
	return fileContents;
}
//----------------------------------------health bar--------------------------------------------
void Player::drawHealth(float health, float max_health, int length)
{
	int numBlocks = (int)(length*(health/ max_health));
	for (int i=0; i<numBlocks; i++)
	{
		br_player_health.outline_opacity = 0.0f;
		if(health>=750)
		{
			br_player_health.fill_color[0] = 0.0f;
			br_player_health.fill_color[1] = 1.0f;
			br_player_health.fill_color[2] = 0.0f;
			br_player_health.fill_opacity = 1.0f;
		}
		else if (health>=500)
		{
			br_player_health.fill_color[0] = 1.0f;
			br_player_health.fill_color[1] = 0.5f;
			br_player_health.fill_color[2] = 0.0f;
			br_player_health.fill_opacity = 1.0f;
		}
		else if (health >= 250)
		{
			br_player_health.fill_color[0] = 1.0f;
			br_player_health.fill_color[1] = 1.0f;
			br_player_health.fill_color[2] = 0.0f;
			br_player_health.fill_opacity = 1.0f;
		}
		else
		{
			br_player_health.fill_color[0] = 1.0f;
			br_player_health.fill_color[1] = 0.0f;
			br_player_health.fill_color[2] = 0.0f;
			br_player_health.outline_opacity = 0.0f;
		}
		
		br_player_health.fill_opacity = 0.5f;
		graphics::drawText(45, 100, 50, "Health: ", br_player_health);
		graphics::drawRect(i* block_health_size+240, 100, block_health_size, block_health_size * 3, br_player_health);
	}

	for (int j = 0; j < length; j++)
	{
		br_player_health.outline_color[0] = 0.5f; 
		br_player_health.outline_color[1] = 0.5f; 
		br_player_health.outline_color[2] = 0.5f;
		br_player_health.outline_opacity = 1.0f;
		br_player_health.outline_width = true;
		br_player_health.fill_opacity = 0.0f;
		graphics::drawRect(j * block_health_size + 240, 100, block_health_size, block_health_size * 3, br_player_health);
	}
}
//----------------------------------------movePlayer--------------------------------------------
void Player::movePlayer(float dt)
{
	float delta_time = dt/150.0f;
	float move = 0.0f;
	if(graphics::getKeyState(graphics::SCANCODE_A)){
		move -= 1.0f;
	}
		
	if(graphics::getKeyState(graphics::SCANCODE_D)) {
		move = 1.0f;
	}
	
	m_vx = std::min<float>(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);
	m_vx = std::max<float>(-m_max_velocity, m_vx);

	m_vx -= 3.0f * m_vx / (3.0f + fabs(m_vx));

	if (fabs(m_vx) < 0.01f)
		m_vx = 0.0f;

	m_pos_x += m_vx * delta_time;

	if (m_vy == 0.0f) {
		if (graphics::getKeyState(graphics::SCANCODE_W))
		{
			m_vy -= m_accel_vertical * 0.02f;
			m_IsJumping = true;
			m_Grounding = false;
		}
		else {
			m_vy -= 0.0f;
			m_Grounding = true;
			m_IsJumping = false;
		}
	}
	m_vy += delta_time * m_gravity;

	m_pos_y+= m_vy * delta_time;

}
//----------------------------------------AnimationPlayer--------------------------------------------
void Player::AnimationPlayer()
{
	// Jump animation
	//vector<string> m_sprites;
	if (graphics::getKeyState(graphics::SCANCODE_W)) {
		cout << "m_filename: " << m_filename << endl;
		m_sprites= loadFileIntoVector(m_filename,"player", "jump");
	}
	// Walk animation
	else if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_A)) {
		//m_sprites = loadFileIntoVector(m_filename, "player","walk");
	}
	// Attack animation
	else if (graphics::getKeyState(graphics::SCANCODE_Q)) {
		//m_sprites = loadFileIntoVector(m_filename, "player","attack");
	}

	//Ensure m_sprites is not empty
	if (m_sprites.empty()) {
		cerr << "Error: m_sprites is empty." << endl;
		return;
	}

	int s = static_cast<int>(fmodf(1000.0f - m_pos_x * 0.2f, static_cast<float>(m_sprites.size())));
	if (s < 0 || s >= m_sprites.size()) {
		cerr << "Error: Invalid sprite index: " << s << endl;
		return;
	}

	// Set the texture of the player's brush to the current sprite
	br_player.texture = m_sprites[s];

	// Flip the player's texture if moving left (optional)
	if (getKeyState(graphics::SCANCODE_A)) {
		graphics::setScale(-1.0f, 1.0f);
	}

	// Draw the player's sprite
	graphics::drawRect(m_state->getCanvasWidth(), m_state->getCanvasHeight(), m_width, m_height, br_player);

	// Reset transformation for subsequent drawing
	graphics::resetPose();
}
//------------------------------------update()--------------------------------------------------------
void Player::update(float dt)
{
	if (graphics::getKeyState(graphics::SCANCODE_Q)) {
		m_Attacking = true;
	}
	else
	{
		m_Attacking = false;
	}
	if (graphics::getKeyState(graphics::SCANCODE_E))
	{
		m_IsPickingUp = true;
	}
	else
	{
		m_IsPickingUp = false;
	}

	if ((graphics::getKeyState(graphics::SCANCODE_A) && graphics::getKeyState(graphics::SCANCODE_D) && !graphics::getKeyState(graphics::SCANCODE_W)) || (graphics::getKeyState(graphics::SCANCODE_A) && graphics::getKeyState(graphics::SCANCODE_D) && graphics::getKeyState(graphics::SCANCODE_W))) {
		if (m_IsJumping) {

		}
		cantMove = true;
	}
	else
	{
		movePlayer(dt);
		cantMove = false;
	}
	
	
	// update offset for other game objects
	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	GameObject::update(dt);
}
//-------------------------------------init()---------------------------------------------------------------
void Player::init()
{
	
	m_pos_x = -1800.0f;
	m_pos_y = 4300.0f;
	m_width = 90;
	m_height = 150;

	m_weapon = Blocks(m_state->getCanvasWidth() * 0.5f + 40, m_state->getCanvasHeight() * 0.5f,75,170);
	
	//cout << weapon.m_pos_x << "        " << weapon.m_pos_y << "        " << weapon.m_width << "        " << weapon.m_height << endl;
	//brush player
	br_player.fill_opacity = 1.1f;
	br_player.outline_opacity = 0.0f;
	br_player.texture = m_state->getFullAssetPath("playerWalk1.png");

	//brush weapon
	//br_weapon.fill_opacity = 1.1f;
	//br_weapon.outline_opacity = 0.0f;
	//pink
	br_weapon.fill_color[0] = 1.0f;
	br_weapon.fill_color[1] = 0.5f;
	br_weapon.fill_color[2] = 0.5f;
	br_weapon.fill_opacity = 0.2f;

	//white
	br_weapon.outline_opacity = 1.0f;
	br_weapon.outline_color[0] = 1.0f;
	br_weapon.outline_color[1] = 1.0f;
	br_weapon.outline_color[2] = 1.0f;


	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	//m_sprites_player = animationInstance->loadFile();
	//Animation walking 
	m_sprites_player.push_back(m_state->getFullAssetPath("playerWalk1.png"));
	m_sprites_player.push_back(m_state->getFullAssetPath("playerWalk2.png"));
	m_sprites_player.push_back(m_state->getFullAssetPath("playerWalk3.png"));
	m_sprites_player.push_back(m_state->getFullAssetPath("playerWalk4.png"));
	m_sprites_player.push_back(m_state->getFullAssetPath("playerWalk5.png"));
	m_sprites_player.push_back(m_state->getFullAssetPath("playerWalk6.png"));
	m_sprites_player.push_back(m_state->getFullAssetPath("playerWalk7.png"));
	m_sprites_player.push_back(m_state->getFullAssetPath("playerWalk8.png"));
	m_sprites_player.push_back(m_state->getFullAssetPath("playerWalk9.png"));
	m_sprites_player.push_back(m_state->getFullAssetPath("playerWalk10.png"));

	//Animation attack
	m_attack.push_back(m_state->getFullAssetPath("playerAttack1.png"));
	m_attack.push_back(m_state->getFullAssetPath("playerAttack2.png"));
	m_attack.push_back(m_state->getFullAssetPath("playerAttack3.png"));
	m_attack.push_back(m_state->getFullAssetPath("playerAttack4.png"));
	m_attack.push_back(m_state->getFullAssetPath("playerAttack5.png"));
	
	//m_sprites_player = loadFileIntoVector("Animation.txt", "player", "walk");
}
//-------------------------------------draw()---------------------------------------------------------------
void Player::draw()
{
	if (!getKeyState(graphics::SCANCODE_Q)) {

		if (getKeyState(graphics::SCANCODE_W)) {
			//m_sprites_player= loadFileIntoVector(m_filename,"player", "jump");
		}
		if (getKeyState(graphics::SCANCODE_A)) {
			//m_sprites_player = loadFileIntoVector("Animation.txt","player", "walk");
			graphics::setScale(-1.0f, 1.0f);

		}
		int s = (int)fmod(1000.0f - m_pos_x * 0.025f, m_sprites_player.size());
		br_player.texture = m_sprites_player[s];
	}
	if(getKeyState(graphics::SCANCODE_Q)) {
		weaponIsActive = true;
		if (getKeyState(graphics::SCANCODE_A)) {
			//m_sprites_player = loadFileIntoVector("Animation.txt","player", "walk");
			graphics::setScale(-1.0f, 1.0f);

		}

		int s = (int)fmod(1000.0f - m_pos_x * 0.025f, m_attack.size());
		br_player.texture = m_attack[s];
	}
	else {
		weaponIsActive = false;
	}
	
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 150, 200, br_player);
	if (!getKeyState(graphics::SCANCODE_A)) {
		//graphics::resetPose();
	}
	graphics::resetPose();
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f + 40, m_state->getCanvasHeight() * 0.5f, 80, 170, br_weapon);

	//animationInstance->draw();
	//AnimationPlayer();
	if (m_state->m_debugging) {
		debugDraw();
	}
	drawHealth(m_health,m_health_max,20);
}

//---------------------------------------get_Attack()---------------------------------------------------
int Player::get_Attack()
{
	return 20 + rand() % 51;
}

//---------------------------------------sword()----------------------------------------------------
int Player::sword()
{
	return 40 + rand() % 61;
}

//---------------------------------------get_Healt()----------------------------------------------------
float Player::get_Health()
{
	return m_health;
}

//---------------------------------------set_Healt()----------------------------------------------------
void Player::set_Health(float health)
{
	m_health = health;
}

//---------------------------------------PlusHealth()----------------------------------------------------
Player &Player::PlusHealth(float plushealth)
{
	m_health += plushealth;
	if (m_health >= 1000) {
		m_health = 1000;
	}
	//epidi touleme na epistrecei to idio to antikeimeno
	return *this;
}

//---------------------------------------Damage()----------------------------------------------------
Player &Player::Damage(float damage)
{
	m_health -= damage;
	if (m_health <= 0) {
		cout << "dead";
		setActive(false);
	}
	return *this;
}

//---------------------------------------Destuctor()----------------------------------------------------
Player::~Player()
{
	delete rigit;
	delete animationInstance;
	delete collisionInstance;
}

//---------------------------------------debugDraw()----------------------------------------------------
void Player::debugDraw()
{
	graphics::Brush br_player_debug;
	
	//yellow
	br_player_debug.fill_opacity = 0.2f;
	br_player_debug.fill_color[0] = 1.0f; 
	br_player_debug.fill_color[1] = 1.0f; 
	br_player_debug.fill_color[2] = 0.0f; 

	//Purple 
	br_player_debug.outline_opacity = 1.0f;
	br_player_debug.outline_color[0] = 0.5f; 
	br_player_debug.outline_color[1] = 0.0f; 
	br_player_debug.outline_color[2] = 0.5f;
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, m_width, m_height, br_player_debug);

	/*
	//pink
	br_weapon.fill_color[0] = 1.0f; 
	br_weapon.fill_color[1] = 0.5f; 
	br_weapon.fill_color[2] = 0.5f;
	br_weapon.fill_opacity = 0.2f;

	//white
	br_weapon.outline_opacity = 1.0f;
	br_weapon.outline_color[0] = 1.0f;
	br_weapon.outline_color[1] = 1.0f;
	br_weapon.outline_color[2] = 1.0f;

	graphics::drawRect(m_state->getCanvasWidth() * 0.5f+40, m_state->getCanvasHeight() * 0.5f, 75, m_height, br_weapon);

	*/
	
}