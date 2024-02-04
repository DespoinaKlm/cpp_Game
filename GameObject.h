#pragma once
#include <sgg/graphics.h>
#include <string>
#include "Properties.h"

using namespace std;
class GameObject
{
private:
	static int m_next_id;
protected:

	class GameState* m_state;
	string m_name;
	int m_id = 0;
	bool m_active = true;

public:
	GameObject(GameState* gs, const string& name = "");
	virtual ~GameObject();
	virtual void update(float dt);
	virtual void init();
	virtual void draw();
	bool isActive() { return m_active; }
	void setActive(bool a) { m_active = a; }
	int getID(){return m_next_id;}
};

