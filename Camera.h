#pragma once
#include "Point.h"
#include "Vector2D.h"
#include <sgg/graphics.h>
#include "GameState.h"
//camera is useful for the player because we have a stable background and a moving player 
//its like GameState

class Camera {
public:
	float m_x_start, m_y_start, m_width, m_height;
	void Update(float dt);
	Vector2D GetPosition();
	void SetPoint(Point* target);
	static Camera* GetCamera();

private:

	//Constructor here  because we will have only 1 camera
	Camera();
	//Vector is useful for the current position of the camera
	Vector2D position;
	//Point for the player because the camera will be working with him
	Point* m_player_target;
	//graphics::drawRect()
	static Camera* m_unique_camera;
	~Camera();
};