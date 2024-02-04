#include "Point.h"

//----------------------Constructor2------------------
Point::Point(float x, float y): Point_X(x),Point_Y(y)
{
}

//----------------------Denstructor------------------
Point::~Point()
{
}

//----------------------operator+--------------------
Point Point::operator+(const Point& p2)
{
    Point result;
    result.Point_X = Point_X + p2.Point_X;
    result.Point_Y = Point_Y + p2.Point_Y;
    return result;
}

//----------------------operator-()------------------
Point Point::operator-(const Point& p2)
{
    Point result;
    result.Point_X = Point_X - p2.Point_X;
    result.Point_Y = Point_Y - p2.Point_Y;
    return result;
}

//----------------------operator*---------------------
Point Point::operator*(const Point& p2)
{
    Point result;
    result.Point_X = Point_X * p2.Point_X;
    result.Point_Y = Point_Y * p2.Point_Y;
    return result;
}

//----------------------operator+=---------------------
Point operator+=(Point& p1, const Point& p2)
{
    p1.Point_X += p2.Point_X;
    p1.Point_Y +=  p2.Point_Y;
    return p1;
}

//----------------------operator-=--------------------
Point operator-=(Point& p1, const Point& p2)
{
    p1.Point_X -= p2.Point_X;
    p1.Point_Y -= p2.Point_Y;
    return p1;
}
