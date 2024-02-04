#pragma once
#include <iostream>

//useful for the mass, velocity, force, fiction
class Vector2D {
public:
	float m_x, m_y;
	Vector2D(float x=0, float y=0);
	~Vector2D();
	Vector2D operator+(Vector2D& v2);
	Vector2D operator-(Vector2D& v2);
	Vector2D operator*(const float& v2);
	//Vector2D operator/(float& left);
	//Vector2D operator+(float & left);
	//void log(std::string msg = "") {
	//	std::cout << msg << "(X,Y)= " << m_x <<" " << m_y << ")" << std::endl;
	//}
};
