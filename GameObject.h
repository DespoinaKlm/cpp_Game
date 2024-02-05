#pragma once
#include <sgg/graphics.h>
#include <iostream>
#include <string>

using namespace std;
class GameObject
{
private:
	static int m_next_id;
protected:

	class GameState* m_state;
	const string m_name;
	int m_id = 0;
	bool m_active = true;
public:
	GameObject(GameState* gs, const string& name = "");
	virtual ~GameObject();
	virtual void update(float dt);
	virtual void init();
	virtual void draw();
	inline bool isActive() const { return m_active; }
	inline void setActive(bool a) { m_active = a; }
	inline int getID(){return m_next_id;}
	inline const string& getName() { return m_name; }
	vector<string> loadFileGameObject(string movement);
};

