#pragma once
#include <sgg/graphics.h>
#include "GameObject.h"
#include "GameState.h"
#include "Poissons.h"
#include "Player.h"
#include "Level.h"
//---------------------------------Constructor--------------------------------------------------------------------------------
Poissons::Poissons(GameState* gs, int type,float posx, float posy, float posw, float posh, const string& name):GameObject(gs, name), m_type(type)
{
	m_type = type;
	m_pos_x = posx;
	m_pos_y = posy;
	m_width = posw;
	m_height = posh;
	m_active = true;
}
//---------------------------------Update-------------------------------------------------------------------------------------
void Poissons::update(float dt)
{

}
//---------------------------------Init---------------------------------------------------------------------------------------
void Poissons::init()
{
	//brush
	getColor();
	indexframePoisson = 0;

	br_poison.fill_opacity = 1.1f;
	br_poison.outline_opacity = 0.0f;
	br_poison.texture = m_state->getFullAssetPath("poison1.png");
	
	//try animation for the poisson
	m_poissonA = loadFileGameObject("poison");
	
}
//---------------------------------Color--------------------------------------------------------------------------------------
void Poissons::getColor()
{
	switch (m_type)
	{
	case PoisonType::DEFAULT:
		break;
	case PoisonType::HEALING:
		br_poison.fill_color[0] = 0.0f;
		br_poison.fill_color[1] = 1.0f;
		br_poison.fill_color[2] = 0.0f;
		break;

	case PoisonType::DAMAGING:
		br_poison.fill_color[0] = 1.0f;
		br_poison.fill_color[1] = 0.0f;
		br_poison.fill_color[2] = 0.0f;
		break;

	case PoisonType::STRONGER:
		br_poison.fill_color[0] = 1.0f; 
		br_poison.fill_color[1] = 0.5f; 
		br_poison.fill_color[2] = 0.5f;
		break;
	}
}
//---------------------------------TypeOfPoison-------------------------------------------------------------------------------
void Poissons::TypeOfPoison()
{
	switch (m_type)
	{
		case PoisonType::DEFAULT:
			m_state->getlevel()->updateScore(rand() % 51 + 50);
			break;
		case PoisonType::HEALING:
			m_state->getPlayer()->PlusHealth(rand() % 51 + 250);
			break;
		case PoisonType::DAMAGING:
			m_state->getPlayer()->Damage(10 + rand() % 21);
			break;
		case PoisonType::STRONGER:
			m_state->getPlayer()->setPlusAttack(true);
			break;
	}
}
//---------------------------------Draw---------------------------------------------------------------------------------------
void Poissons::draw()
{
	graphics::resetPose();
	float x = m_pos_x + m_state->m_global_offset_x;
	float y = m_pos_y + m_state->m_global_offset_y;

	//Animation
	if (m_state->getPlayer()->isActive() && intersect(*m_state->getPlayer()) && m_state->getPlayer()->isPickingUp())
	{
		drawframe = true;
	}
	if (drawframe)
	{
		indexframePoisson += 0.1;
		if (indexframePoisson >= m_poissonA.size())
		{
			TypeOfPoison();
			drawframe = false;
			m_active=false;
		}
		else
		{
			switch (m_type)
			{
			case PoisonType::DEFAULT:
				graphics::playSound(m_state->getFullAssetPath("pow.wav"), 0.5f);
				break;
			case PoisonType::HEALING:
				graphics::playSound(m_state->getFullAssetPath("health.wav"), 0.5f);
				break;
			case PoisonType::DAMAGING:
				graphics::playSound(m_state->getFullAssetPath("hit.wav"), 0.7f);
				break;
			case PoisonType::STRONGER:
				graphics::playSound(m_state->getFullAssetPath("points.wav"), 0.5f);
				break;
			}
			br_poison.texture = m_poissonA[int(indexframePoisson)];
		}
	}
	//cout << indexframePoisson << "\n";
	graphics::drawRect(x, y, m_width * 2.5f, m_height * 5.0f, br_poison);

	if (m_state->m_debugging) {
		debugDrawPoison();
	}
}
//---------------------------------getType------------------------------------------------------------------------------------
const int& Poissons::getType() const
{
	return m_type;
}
//---------------------------------debugDrawPoison----------------------------------------------------------------------------
void Poissons::debugDrawPoison()
{
	float x = m_pos_x + m_state->m_global_offset_x;
	float y = m_pos_y + m_state->m_global_offset_y;

	br_poison_deg.fill_opacity = 0.1f;
	br_poison_deg.fill_color[0] = 0.9f;
	br_poison_deg.fill_color[1] = 0.0f;
	br_poison_deg.fill_color[2] = 0.2f;
	br_poison_deg.outline_color[0] = 0.3f;
	br_poison_deg.outline_color[1] = 1.0f;
	br_poison_deg.outline_color[2] = 0.2f;

	graphics::drawRect(x, y, m_width , m_height , br_poison_deg);
}
//---------------------------------Destructor---------------------------------------------------------------------------------
Poissons::~Poissons()
{

}
//----------------------------------------------------------------------------------------------------------------------------
