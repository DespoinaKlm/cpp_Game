#pragma once
#include "Vector2D.h"
//useful for the movement of the player
class Transform {
public:
	float m_x, m_y;
	Transform(float x = 0, float y = 0) :m_x(x), m_y(y) {};
	inline void TranslateX(float x) { m_x += x; }
	inline void TranslateY(float y) { m_y += y; }
	inline void TranslateXm(float x) { m_x -= x; }
	inline void TranslateYm(float y) { m_y -= y; }
	inline void Translate(Vector2D v) { m_x += v.m_x; m_y += v.m_y;}
};