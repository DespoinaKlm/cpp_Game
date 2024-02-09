#pragma once
#include "GameState.h"
#include "GameObject.h"
class Particle: public GameObject{
private:
	float indexDraw;
	float animation_speed;
public:
	void update(float dt) override;
	void init() override;
	void draw() override;
};
