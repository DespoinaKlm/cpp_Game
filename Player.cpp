#pragma once
#include <sgg/graphics.h>
#include "GameState.h"
#include "GameObject.h"
#include "Player.h"
#include <iostream>
#include <cmath>
#include "Level.h"
#include <fstream>
#include <string>
#include <iostream>
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
	right = false;
	left = false;
	dead = false;
	m_health = health;
	JumpTime = jump_time;
	JumpForce = jump_force;
	m_AttackingTime =Attack_time;
}
//----------------------------------------health bar----------------------------------------------------
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
//----------------------------------------movePlayer----------------------------------------------------
void Player::movePlayer(float dt)
{
	delta_time = dt/150.0f;
	float move = 0.0f;
	if (!(graphics::getKeyState(graphics::SCANCODE_A) && graphics::getKeyState(graphics::SCANCODE_D))|| (graphics::getKeyState(graphics::SCANCODE_A) && graphics::getKeyState(graphics::SCANCODE_D) && graphics::getKeyState(graphics::SCANCODE_W))) {

		if (graphics::getKeyState(graphics::SCANCODE_A)) {
			move -= 1.0f;
			left = true;
			right = false;
		}

		if (graphics::getKeyState(graphics::SCANCODE_D)) {
			move = 1.0f;
			left = false;
			right = true;
		}
	

		m_vx = std::min<float>(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);
		m_vx = std::max<float>(-m_max_velocity, m_vx);

		m_vx -= 3.0f * m_vx / (3.0f + fabs(m_vx));

		if (fabs(m_vx) < 0.01f)
			m_vx = 0.0f;

		m_pos_x += m_vx * delta_time;
	}
	if (m_vy == 0.0f) {
		if (graphics::getKeyState(graphics::SCANCODE_W))
		{
			m_vy -= m_accel_vertical * 0.02f;
			m_IsJumping = true;
			m_Grounding = false;
		}
		else
		{
			m_vy -= 0.0f;
			m_Grounding = true;
			m_IsJumping = false;
		}
	}
	m_vy += delta_time * m_gravity;

	m_pos_y += m_vy * delta_time;
	
}
/*
//----------------------------------------AnimationPlayer-----------------------------------------------
void Player::AnimationPlayer()
{
	// Jump animation
	if (graphics::getKeyState(graphics::SCANCODE_W)){
		m_sprites_player = loadFileGameObject("playerJump");
	}
	// Walk animation
	else if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_A))
	{
		
		* if (graphics::getKeyState(graphics::SCANCODE_D)) {
			graphics::resetPose();
		}
		if (graphics::getKeyState(graphics::SCANCODE_A)) {
			graphics::setScale(-1.0f, 1.0f);
		}
		m_sprites_player = loadFileGameObject("playerWalk");
	}
	// Attack animation
	else if (graphics::getKeyState(graphics::SCANCODE_Q))
	{
		m_sprites_player = loadFileGameObject("playerAttack");
	}
	int s = (int)fmod(1000.0f - m_pos_x * 0.025f, m_sprites_player.size());
	br_player.texture = m_sprites_player[s];

	// Flip the player's texture if moving left (optional)
	if (getKeyState(graphics::SCANCODE_A))
	{
		graphics::setScale(-1.0f, 1.0f);
	}

	// Draw the player's sprite
	graphics::drawRect(m_state->getCanvasWidth(), m_state->getCanvasHeight(), m_width, m_height, br_player);

	// Reset transformation for subsequent drawing
	graphics::resetPose();
}
*/
//------------------------------------update()----------------------------------------------------------
void Player::update(float dt)
{
	if (m_pos_y >=4700.0f) {
		setActive(false);
	}
	if (!dead) {
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

		movePlayer(dt);
	}
	else {
		m_pos_x += m_vx;
	}
	
	// update offset for other game objects
	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	GameObject::update(dt);
}
//-------------------------------------init()-----------------------------------------------------------
void Player::init()
{
	m_pos_x = -1800.0f;
	m_pos_y = 4300.0f;
	m_width = 90;
	m_height = 150;

	//brush player
	br_player.fill_opacity = 1.1f;
	br_player.outline_opacity = 0.0f;
	br_player.texture = m_state->getFullAssetPath("playerWalk1.png");

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	m_sprites_player = loadFileGameObject("playerWalk");
}
//-------------------------------------draw()-----------------------------------------------------------
void Player::draw()
{
	if (!dead) {
		if (!getKeyState(graphics::SCANCODE_Q))
		{

			if (getKeyState(graphics::SCANCODE_W))
			{
				m_IsJumping = true;
				m_Grounding = false;
				if (getKeyState(graphics::SCANCODE_A)) {
					graphics::setScale(-1.0f, 1.0f);
				}
				if (getKeyState(graphics::SCANCODE_D)) {
					graphics::resetPose();
				}
				m_sprites_player = loadFileGameObject("playerJump");
			}
			if (m_vy != 0) {
				int s = (int)fmod(1000.0f - m_pos_y * 0.025f, m_sprites_player.size());
				br_player.texture = m_sprites_player[s];
				//m_Grounding = true;
				//m_IsJumping = false;
			}
			else {
				m_IsJumping = false;
				m_Grounding = true;
				m_sprites_player = loadFileGameObject("playerWalk");
			}
			if (getKeyState(graphics::SCANCODE_A)) {
				graphics::setScale(-1.0f, 1.0f);
			}
			//cout << m_vy << endl;
			if (m_Grounding) {
				if (getKeyState(graphics::SCANCODE_A) || getKeyState(graphics::SCANCODE_D))
				{
					m_sprites_player = loadFileGameObject("playerWalk");
					if (graphics::getKeyState(graphics::SCANCODE_D)) {
						graphics::resetPose();
					}
					if (graphics::getKeyState(graphics::SCANCODE_A)) {
						graphics::setScale(-1.0f, 1.0f);
					}

				}
			}
			int s = (int)fmod(1000.0f - m_pos_x * 0.025f, m_sprites_player.size());
			br_player.texture = m_sprites_player[s];
		}
		if (getKeyState(graphics::SCANCODE_Q))
		{
			weaponIsActive = true;
			m_sprites_player = loadFileGameObject("playerAttack");
			canAttack = true;
			if (getKeyState(graphics::SCANCODE_A))
			{
				graphics::setScale(-1.0f, 1.0f);
			}
			int s = (int)fmod(1000.0f - m_pos_x * 0.025f, m_sprites_player.size());
			br_player.texture = m_sprites_player[s];
		}
		if(canAttack){
			indexPlayer += 0.15;
			if (indexPlayer >= m_sprites_player.size()) {
				indexPlayer = 0;
				weaponIsActive = false;
				canAttack = false;
			}
			br_player.texture = m_sprites_player[int(indexPlayer)];
		}

		graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 150, 200, br_player);

		graphics::resetPose();
		if (m_state->m_debugging)
		{
			debugDraw();
		}
		drawHealth(m_health, m_health_max, 20);
	}
	else {
		if (indexPlayer == 0) {
			m_sprites_player = loadFileGameObject("playerDie");
		}
		playerDrawDeath();
	}
}
//------------------------------------playerDrawDeath()-------------------------------------------------
void Player::playerDrawDeath()
{
	indexPlayer += 0.2;
	if (indexPlayer >= m_sprites_player.size()) {
		indexPlayer = m_sprites_player.size() - 1;
		setActive(false);

	}
	br_player.texture = m_sprites_player[int(indexPlayer)];
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 150, 200, br_player);
}
//---------------------------------------get_Attack()---------------------------------------------------
int Player::get_Attack()
{
	return 40 + rand() % 81;
}
//---------------------------------------get_Healt()----------------------------------------------------
float Player::get_Health()
{
	return m_health;
}
//---------------------------------------set_Healt()-----------------------------------------------------
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
	return *this;
}
//---------------------------------------Damage()--------------------------------------------------------
Player &Player::Damage(float damage)
{
	m_health -= damage;
	if (m_health <= 0) {
		dead = true;
		weaponIsActive = false;
	}
	return *this;
}
//---------------------------------------Destuctor()-----------------------------------------------------
Player::~Player()
{
}
//---------------------------------------debugDraw()-----------------------------------------------------
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

}
//-------------------------------------------------------------------------------------------------------