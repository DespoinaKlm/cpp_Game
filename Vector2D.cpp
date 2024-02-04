#include "Vector2D.h"
#include <iostream>

using namespace std;
//-----------------Constructor-----------------------
Vector2D::Vector2D(float x, float y) :m_x(x), m_y(y)
{
}

//-----------------Destructor------------------------
Vector2D::~Vector2D()
{
}

//-----------------operator+-------------------------
Vector2D Vector2D::operator+(Vector2D& v2)
{
    Vector2D result;
    result.m_x = m_x + v2.m_x;
    result.m_y = m_y + v2.m_y;
    return result;
}
//-----------------operator-()------------------------
Vector2D Vector2D::operator-(Vector2D& v2)
{
    Vector2D result;
    result.m_x = m_x - v2.m_x;
    result.m_y = m_y - v2.m_y;
    return result;
}
//-----------------operator*-------------------------
Vector2D Vector2D::operator*(const float& v2)
{
    Vector2D result;
    result.m_x = m_x * v2;
    result.m_y = m_y * v2;
    return result;
}
/*
Vector2D Vector2D::operator/(float& left)
{
    Vector2D result;
    result.m_x = m_x / left;
    result.m_y = m_y / left;
    return result;
}

Vector2D Vector2D::operator+(float& left)
{
    Vector2D result;
    result.m_x = m_x + left;
    result.m_y = m_y + left;
    return result;
}

*/

