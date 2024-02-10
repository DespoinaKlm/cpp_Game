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

//----------------------------------------Constructor---------------------------------------------------
Player::Player(GameState* gs, const string& name, float health) :GameObject(gs, name), m_health(health)
{
	m_IsJumping = false;
	m_IsRunning = false;
	m_Attacking = false;
	plusAttack = false;
	m_Falling = false;
	m_Grounding = false;
	weaponIsActive = false;
	right = false;
	dead = false;
	canAttackN = false;
	drawJump = false;
	damage = false;
	damageAnimation = false;

	m_health = health;
}
//---------------------------------------dustAnimation()-------------------------------------------------
void Player::dustAnimation(vector<string>dust)
{

	if (indexDustAnimation == 0) {
		if (!right) {
			//cout << "yes" << endl;
			x_d = m_pos_x + m_state->m_global_offset_x + 80;
		}
		if (right) {
			//cout << "no" << endl;
			x_d = m_pos_x + m_state->m_global_offset_x - 40;
		}

		y_d = m_pos_y + m_state->m_global_offset_y + 100;
	}

	indexDustAnimation += 0.5;
	//cout << m_vx<<endl;
	if (indexDustAnimation >= dust.size()) {
		indexDustAnimation = 0;
		drawJump = false;
		m_IsRunning = false;
	}
	br_player.texture = dust[int(indexDustAnimation)];
	if (right)
	{
		//cout << "have fun " << endl;
		graphics::drawRect(x_d, y_d, 40.0f, 40.0f, br_player);
	}
	//else
	//{
		//graphics::drawRect(m_state->getCanvasWidth() * 0.5f-40, m_state->getCanvasHeight() * 0.5f, 110.0f, 50.0f, br_player);
	//}
}
//----------------------------------------updateCooldownAttack------------------------------------------
void Player::drawDustAnimation()
{
	//if (drawJump)
	//{
		//if (graphics::getKeyState(graphics::SCANCODE_W)) {
			//dust_animation = loadFileGameObject("jump");
			//dustAnimation(dust_animation);
		//}
		//else
		//{
	//cout << "m_IsRunning: " << m_IsRunning << endl;
			if (m_IsRunning)
			{
				dust_animation = loadFileGameObject("run");
				dustAnimation(dust_animation);
			}
		//}
	//}
}
//----------------------------------------updateCooldownAttack------------------------------------------
void Player::updateCooldownAttack()
{
	if (this->attackCooldown < this->attackCooldownMax) {
		this->attackCooldown += 0.5f;
	}
}
//----------------------------------------canAttack----------------------------------------------------
const bool Player::canAttack()
{
	//cout << attackCooldown << endl;
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.0f;
		return true;
	}
	return false;
}
//----------------------------------------health bar----------------------------------------------------
void Player::drawHealth(float health, float max_health, int length)
{
	int numBlocks = (int)(length * (health / max_health));
	for (int i = 0; i < numBlocks; i++)
	{
		br_player_health.outline_opacity = 0.0f;
		if (health >= 750)
		{
			br_player_health.fill_color[0] = 0.0f;
			br_player_health.fill_color[1] = 1.0f;
			br_player_health.fill_color[2] = 0.0f;
			br_player_health.fill_opacity = 1.0f;
		}
		else if (health >= 500)
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
		graphics::drawRect(i * block_health_size + 240, 100, block_health_size, block_health_size * 3, br_player_health);
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
	delta_time = dt / 150.0f;
	float move = 0.0f;
	if (!((graphics::getKeyState(graphics::SCANCODE_A) && graphics::getKeyState(graphics::SCANCODE_D)) || (graphics::getKeyState(graphics::SCANCODE_A) && graphics::getKeyState(graphics::SCANCODE_D) && graphics::getKeyState(graphics::SCANCODE_W)))) {

		if (graphics::getKeyState(graphics::SCANCODE_A)) {
			move -= 1.0f;
			right = false;
			m_IsRunning = true;
		}

		if (graphics::getKeyState(graphics::SCANCODE_D)) {
			move = 1.0f;
			right = true;
			m_IsRunning = true;
		}


		m_vx = std::min<float>(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);
		m_vx = std::max<float>(-m_max_velocity, m_vx);

		m_vx -= 3.0f * m_vx / (3.0f + fabs(m_vx));

		if (fabs(m_vx) < 0.01f)
			m_vx = 0.0f;

		m_pos_x += m_vx * delta_time;
	}
	if (m_vy == 0.0f)
	{
		if (graphics::getKeyState(graphics::SCANCODE_W))
		{
			//m_IsRunning = false;
			drawJump = true;
			m_vy -= m_accel_vertical * 0.02f;
			m_IsJumping = true;
			m_Grounding = false;
		}
		else
		{
			//m_IsRunning = false;
			m_vy -= 0.0f;
			m_Grounding = true;
			m_IsJumping = false;
		}
	}
	m_vy += delta_time * m_gravity;

	m_pos_y += m_vy * delta_time;

}
//------------------------------------update()----------------------------------------------------------
void Player::update(float dt)
{
	if (m_pos_y >= 4700.0f) {
		setActive(false);
	}
	if (!dead)
	{
		if (graphics::getKeyState(graphics::SCANCODE_Q)) {
			m_Attacking = true;
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
	if (dead)
	{
		m_pos_x += m_vx;
	}


	updateCooldownAttack();


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
	br_player.texture = m_state->getFullAssetPath("playerStanding1.png");

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	//m_sprites_player = loadFileGameObject("playerWalk");
	this->attackCooldownMax = 15.0f;
	this->attackCooldown = this->attackCooldownMax;
	//cout << this->attackCooldownMax << "         " << this->attackCooldown;
}
//-------------------------------------draw()-----------------------------------------------------------
void Player::draw()
{
	//cout << m_state->getlevel()->getNextLevel() << endl;
	//mini animation
	if (!m_state->getlevel()->getNextLevel())
	{
		//cout <<"velocity   " << m_vx << endl;
		//cout << (!getKeyState(graphics::SCANCODE_Q) && !getKeyState(graphics::SCANCODE_A) && !getKeyState(graphics::SCANCODE_D) && !getKeyState(graphics::SCANCODE_W) && m_vx==0 ) << endl;;
		//not dead
		if (!dead)
		{
			//takes damage
			if (damage) {
				m_sprites_player = loadFileGameObject("playerDie");
				damageAnimation = true;
			}
			//starts animation for damage
			if (damageAnimation) {
				if (getKeyState(graphics::SCANCODE_A))
				{
					right = false;
				}
				indexPlayer += 0.40;
				int p = (m_sprites_player.size() / 2) + 1;
				if (indexPlayer >= p)
				{
					indexPlayer = 0;
					damage = false;
					damageAnimation = false;
					
				}

				br_player.texture = m_sprites_player[int(indexPlayer)];
				cout <<"damageAnimation: " << damageAnimation << " indexPlayer: " << indexPlayer<<endl;
				if (getKeyState(graphics::SCANCODE_W)&& !damageAnimation)
				{
					m_sprites_player = loadFileGameObject("playerJump");
				}
			}
			//player wasnt attacked
			if (!damage)
			{
				//if he hasnt attacked
				if (!getKeyState(graphics::SCANCODE_Q) && !canAttackN)
				{
					//if he jumped
					if (getKeyState(graphics::SCANCODE_W))
					{
						m_IsJumping = true;
						m_Grounding = false;
						//direction for the player
						if (getKeyState(graphics::SCANCODE_A))
						{
							right = false;
						}
						if (getKeyState(graphics::SCANCODE_D))
						{
							right = true;
						}

						m_sprites_player = loadFileGameObject("playerJump");
					}
					//if he falling
					if (m_vy != 0)
					{
						m_Grounding = false;
						m_IsJumping = false;
						m_Falling = true;
						//pressed buttons
						if (getKeyState(graphics::SCANCODE_A) || getKeyState(graphics::SCANCODE_D))
						{
							s = (int)fmod(1000.0f - m_pos_y * 0.025f, m_sprites_player.size());
							br_player.texture = m_sprites_player[s];
						}
						else
						{
							//animation falling
							m_sprites_player = loadFileGameObject("playerJump");
							if (m_Falling)
							{
								indexPlayer += 0.5;
								if (indexPlayer >= m_sprites_player.size())
								{
									indexPlayer = 0;
								}
								br_player.texture = m_sprites_player[int(indexPlayer)];
							}
							else
							{
								indexPlayer = 0;
							}
						}
					}
					else
					{
						m_Falling = false;
						m_IsRunning = false;
						m_IsJumping = false;
						m_Grounding = true;
						m_sprites_player = loadFileGameObject("playerStanding");
					}
					//direction
					if (getKeyState(graphics::SCANCODE_A))
					{
						right = false;
						//m_IsRunning = true;
					}
					//on the floor
					if (m_Grounding)
					{
						indexDustAnimation = true;
						if (getKeyState(graphics::SCANCODE_A) || getKeyState(graphics::SCANCODE_D))
						{

							m_sprites_player = loadFileGameObject("playerWalk");
							if (graphics::getKeyState(graphics::SCANCODE_D))
							{
								right = true;
							}
							if (graphics::getKeyState(graphics::SCANCODE_A))
							{
								right = false;
							}

						}
					}
					//cout<<"for the walk" << m_sprites_player.size() << endl;
					s = (int)fmod(1000.0f - m_pos_x * 0.025f, m_sprites_player.size());
					br_player.texture = m_sprites_player[s];
					//cout << "1000.0f - m_pos_x(" << m_pos_x << ")* 0.025f  MOD " << m_sprites_player.size() << ": " << s << endl;

				}
				//attack player
				if (getKeyState(graphics::SCANCODE_Q))
				{
					weaponIsActive = true;
					m_sprites_player = loadFileGameObject("playerAttack");
					canAttackN = true;

					if (getKeyState(graphics::SCANCODE_A))
					{
						right = false;
					}
				}
				if (canAttackN)
				{

					if (getKeyState(graphics::SCANCODE_A))
					{
						right = false;
					}
					indexPlayer += 0.5;
					//cout << "indexPlayer: " << indexPlayer << " m_sprites_player.size(): " << m_sprites_player.size() << endl;
					if (indexPlayer >= m_sprites_player.size()) {
						indexPlayer = 0;
						weaponIsActive = false;
						canAttackN = false;
						m_Attacking = false;
					}
					br_player.texture = m_sprites_player[int(indexPlayer)];
					if (getKeyState(graphics::SCANCODE_W)) {
						m_IsJumping = true;
					}
					if (m_IsJumping && !canAttackN){
						//cout << "indexPlayer: " << indexPlayer << " canAttackN: " << canAttackN << endl;
						m_sprites_player = loadFileGameObject("playerJump");
					}
				}
				if (damage)
				{
					m_sprites_player = loadFileGameObject("playerDie");
					damageAnimation = true;
				}
				if (damageAnimation)
				{
					if (getKeyState(graphics::SCANCODE_A))
					{
						right = false;
					}
					indexPlayer += 0.5;//animation_speed;
					//cout << m_sprites_player.size() << "   " << m_sprites_player.size() / 2 << endl;
					int p = m_sprites_player.size() / 2;
					if (indexPlayer >= p) {
						indexPlayer = 0;
						damage = false;
						damageAnimation = false;
					}
					br_player.texture = m_sprites_player[int(indexPlayer)];
				}
				if (right)
				{
					graphics::resetPose();
				}
				else
				{
					graphics::setScale(-1.0f, 1.0f);
				}
			}
			graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 200, 400, br_player);

			graphics::resetPose();
			if (m_state->m_debugging)
			{
				debugDraw();
			}
			drawHealth(m_health, m_health_max, 20);
		}
		else
		{
			if (indexPlayer == 0) {
				m_sprites_player = loadFileGameObject("playerDie");
			}
			playerDrawDeath();
			graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 200, 400, br_player);
		}
	}
	else
	{
		m_sprites_player = loadFileGameObject("playerWalk");
		//cout << "indexPlayer: "<< indexPlayer<<" size: "<< m_sprites_player.size()<<endl;
		indexPlayer += animation_speed;
		if (indexPlayer >= m_sprites_player.size()) {
			indexPlayer = 0;
		}
		br_player.texture = m_sprites_player[int(indexPlayer)];
		graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 200.0f, 400.0f, br_player);
	}
	drawDustAnimation();
}

//------------------------------------playerDrawDeath()-------------------------------------------------
void Player::playerDrawDeath()
{
	indexPlayer += 0.5;
	//cout << indexPlayer << endl;
	if (indexPlayer >= m_sprites_player.size())
	{
		indexPlayer = m_sprites_player.size() - 1;
		setActive(false);

	}
	br_player.texture = m_sprites_player[int(indexPlayer)];
	//graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 150, 200, br_player);
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
Player& Player::PlusHealth(float plushealth)
{
	m_health += plushealth;
	if (m_health >= 1000) {
		m_health = 1000;
	}
	return *this;
}
//---------------------------------------Damage()--------------------------------------------------------
Player& Player::Damage(float damage)
{
	m_health -= damage;
	if (m_health > 0) {
		this->damage = true;
	}
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
