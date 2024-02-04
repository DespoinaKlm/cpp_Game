#pragma once
#include <iostream>
using namespace std;
//its not so different from the vector but it is more useful to use it without any problems
class Point {
public:
	float Point_X, Point_Y;
	Point(float x = 0, float y = 0);
	~Point();
	Point operator+(const Point& p2);
	Point friend operator+=(Point& p1, const Point& p2);
	Point operator-(const Point& p2);
	Point friend operator-=(Point& p1, const Point& p2);
	Point operator*(const Point& p2);

	//void log(std::string msg = "") {
	//	std::cout << msg << "(X,Y)= " << Point_X << " " << Point_Y << ")" << std::endl;
	//}
};
