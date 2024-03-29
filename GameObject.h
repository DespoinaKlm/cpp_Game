#pragma once
#include <sgg/graphics.h>
#include <iostream>
#include <string>
#include  "box.h"

using namespace std;
class GameObject 
{
private:
	static int m_next_id;
protected:
	class GameState* m_state;
	string m_name;
	int m_id = 0;
	bool m_active;
public:
	GameObject(GameState* gs, const string& name = "");
	virtual ~GameObject();
	virtual void update(float dt);
	virtual void init();
	virtual void draw();
	inline bool isActive()const { return m_active;}
	inline void setActive(bool a) { m_active = a; }
	inline void setName(string name){ m_name = name; }
	inline const string& getName() { return m_name; }
	vector<string> loadFileGameObject(string movement);
};

