#pragma once
#include <sgg/graphics.h>
#include "GameObject.h"
#include "GameState.h"
#include "box.h"

using namespace std;

enum PoisonType { DEFAULT = 0, DAMAGING, HEALING, STRONGER, NROFTYPES };

class Poissons: public GameObject, public Box {
private:
	float indexframePoisson;
	vector<string> m_poissonA;
	graphics::Brush br_poison;
	graphics::Brush br_poison_deg;
	int m_type;
	bool drawframe = false;

public:
	Poissons(GameState* gs,int type, float posx, float posy, float posw, float posh,const string& name = "");
	~Poissons();
	void update(float dt) ;
	void init();
	void draw() ;
	const int& getType() const ;
	void debugDrawPoison();
	void getColor();
	void TypeOfPoison();
};