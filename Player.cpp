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

using namespace std;

//----------------------------------------Constructor---------------------------------------------------
Player::Player(GameState* gs, const string& name, float health) :GameObject(gs, name), m_health(health)
{
	m_active = true;
	m_Attacking = false;
	plusAttack = false;
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
	indexDustAnimation += 0.5;
	if (indexDustAnimation >= dust.size()) {
		indexDustAnimation = 0;
		drawJump = false;
	}
	br_player.texture = dust[int(indexDustAnimation)];
	if (!right)
	{
		graphics::setScale(-1.0f, 1.0f);
		graphics::drawRect(m_state->getCanvasWidth() * 0.5f+60 , m_state->getCanvasHeight() * 0.5f+80, 40.0f, 40.0f, br_player);
	}
	if (right)
	{
		graphics::resetPose();
		graphics::drawRect(m_state->getCanvasWidth() * 0.5f-60, m_state->getCanvasHeight() * 0.5f + 80, 40.0f, 40.0f, br_player);
	}
	graphics::resetPose();
}
//----------------------------------------updateCooldownAttack------------------------------------------
void Player::drawDustAnimation()
{
	if (drawJump)
	{
		dust_animation = loadFileGameObject("run");
		dustAnimation(dust_animation);
	}
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
		//m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f
		//graphics::drawText(m_state->getCanvasWidth() * 0.5f-500, m_state->getCanvasHeight() * 0.5f-500, 50, "Health: ", br_player_health);
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
			m_Grounding = true;
		}

		if (graphics::getKeyState(graphics::SCANCODE_D)) {
			move = 1.0f;
			right = true;
			m_Grounding = true;
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
			drawJump = true;
			m_vy -= m_accel_vertical * 0.02f;
			m_Grounding = false;
		}
		else
		{
			m_vy -= 0.0f;
			m_Grounding = true;
		}
		
	}
	m_vy += delta_time * m_gravity;

	m_pos_y += m_vy * delta_time;
}
//------------------------------------update()----------------------------------------------------------
void Player::update(float dt)
{
	if (m_pos_y >= 4700.0f)
	{
		m_state->setPointerLevel(6);
		m_state->game_over = true;
		setActive(false);
	}
	if (!dead)
	{
		if (graphics::getKeyState(graphics::SCANCODE_Q)) 
		{
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

	// update offset for other game objects
	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	GameObject::update(dt);
}
//-------------------------------------init()-----------------------------------------------------------
void Player::init()
{
	if (m_state->getPointerLevel()==2) {
		m_pos_x = -1800.0f;
		m_pos_y = 4300.0f;
	}
	else if (m_state->getPointerLevel() == 3) {
		m_pos_x = -1700.0;
		m_pos_y = 4200.0f;
	}
	else if (m_state->getPointerLevel() == 4) {
		m_pos_x = 0.0f;
		m_pos_y = 2000.0f;
	}
	m_width = 90;
	m_height = 150;

	//brush player
	br_player.fill_opacity = 1.1f;
	br_player.outline_opacity = 0.0f;
	br_player.texture = m_state->getFullAssetPath("playerStanding1.png");

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;


}
//-------------------------------------draw()-----------------------------------------------------------
void Player::draw()
{
	
	if (!m_state->getNextLevel())
	{
		if (!dead)
		{
			//takes damage
			if (damage) {
				m_sprites_player = loadFileGameObject("playerDie");
				damageAnimation = true;
			}
			//starts animation for damage
			if (damageAnimation)
			{
				indexPlayer += 0.25;
				int p = (m_sprites_player.size() / 2) + 1;
				if (indexPlayer >= p)
				{
					indexPlayer = 0;
					damage = false;
					damageAnimation = false;
				}
				br_player.texture = m_sprites_player[int(indexPlayer)];
				//if the player jumps and the animation for damage is over he continues the jump animation
				if (m_vy != 0 && !damageAnimation)
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
						//drawJump = true;
						m_sprites_player = loadFileGameObject("playerJump");
					}
					
					if (m_vy != 0)
					{
						//pressed buttons
						if (!(getKeyState(graphics::SCANCODE_A) || getKeyState(graphics::SCANCODE_D)))
						
						{
							//animation falling
							m_sprites_player = loadFileGameObject("playerJump");
							if (!m_Grounding)
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
						m_sprites_player = loadFileGameObject("playerStanding");
					}
					
					//on the floor
					if (m_vy==0)
					{
						drawJump = false;
						indexDustAnimation = true;
						if (getKeyState(graphics::SCANCODE_A) || getKeyState(graphics::SCANCODE_D))
						{
							m_sprites_player = loadFileGameObject("playerWalk");
						}
					}
					if ((drawJump && getKeyState(graphics::SCANCODE_A)) || drawJump && getKeyState(graphics::SCANCODE_D))
					{
						m_sprites_player = loadFileGameObject("playerJump");
					}
					s = (int)fmod(1000.0f - m_pos_x * 0.025f, m_sprites_player.size());
					br_player.texture = m_sprites_player[s];

				}
				//attack player
				if (getKeyState(graphics::SCANCODE_Q))
				{
					weaponIsActive = true;
					m_sprites_player = loadFileGameObject("playerAttack");
					canAttackN = true;
				}
				//animation atttack
				if (canAttackN)
				{
					indexPlayer += 0.25;
					if (indexPlayer >= m_sprites_player.size()) {
						indexPlayer = 0;
						weaponIsActive = false;
						canAttackN = false;
						m_Attacking = false;
					}
					br_player.texture = m_sprites_player[int(indexPlayer)];
					//if the player attacks and the animation for attack is over he continues the jump animation
					if (m_vy!=0 && !canAttackN)
					{
						
						m_sprites_player = loadFileGameObject("playerJump");
					}
				}
			}
			//health bar
			if (m_state->m_debugging)
			{
				debugDraw();
			}
			drawHealth(m_health, m_health_max, 20);
		}
		else
		{
			//animation when the player is dead
			if (indexPlayer == 0) {
				m_sprites_player = loadFileGameObject("playerDie");
			}
			playerDrawDeath();
			
		}
		//direction
		if (right)
		{
			graphics::resetPose();
		}
		else
		{
			graphics::setScale(-1.0f, 1.0f);
		}
		graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 200, 400, br_player);

		graphics::resetPose();
	}
	else
	{
		
		if (indexPlayer=0)
		{
			m_sprites_player = loadFileGameObject("playerWalk");
		}
		indexPlayer += 0.25;
		cout << "indexPlayer: " << indexPlayer << " size: " << m_sprites_player.size()<< endl;
		if (indexPlayer >=m_sprites_player.size())
		{
			indexPlayer = 0;
		cout << "was here " << m_state->getPointerLevel() << endl;
		
		}
		br_player.texture = m_sprites_player[int(indexPlayer)];
		graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 200.0f, 400.0f, br_player);
	}
	if (m_vx==1.0f && m_vy==0) {
		drawJump = true;
	}
	drawDustAnimation();
}
//------------------------------------playerDrawDeath()-------------------------------------------------
void Player::playerDrawDeath()
{
	indexPlayer += 0.25;
	if (indexPlayer >= m_sprites_player.size())
	{
		indexPlayer = m_sprites_player.size() - 1;
		setActive(false);
		m_state->game_over = true;
		m_state->setPointerLevel(6);

	}
	br_player.texture = m_sprites_player[int(indexPlayer)];
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

	//player 
	
	char s[20];
	sprintf_s(s, "(%5.2f, %5.2f)", m_state->getPlayer()->getPosX(), m_state->getPlayer()->getPosY());
	graphics::drawText(45, 300, 50, "Position: ", br_player_debug);
	graphics::drawText(240, 300, 50, s, br_player_debug);
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, m_width, m_height, br_player_debug);

}
//-------------------------------------------------------------------------------------------------------
