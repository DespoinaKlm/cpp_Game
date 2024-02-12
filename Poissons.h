#pragma once
#include <sgg/graphics.h>
#include "GameObject.h"
#include "GameState.h"
#include "box.h"

using namespace std;

enum PoisonType { DEFAULT = 0, DAMAGING, HEALING, STRONGER, NROFTYPES };

class Poissons: public GameObject, public Box {
private:

	//Animation
	bool drawframe = false;
	float indexframePoisson;
	vector<string> m_poisson;

	//Brush
	graphics::Brush br_poison;
	graphics::Brush br_poison_deg;
	int m_type;
	

public:
	Poissons(GameState* gs,int type, float posx, float posy, float posw, float posh,const string& name = "");
	~Poissons();
	void update(float dt) override;
	void init() override;
	void draw() override;

	//type of poison and color
	const int& getType() const ;
	void getColor();
	void TypeOfPoison();
	void debugDrawPoison();
};