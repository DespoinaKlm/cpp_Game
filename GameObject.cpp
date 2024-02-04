#include <sgg/graphics.h>
#include "GameObject.h"
#include "GameState.h"

//------------------------------------Constructor----------------------------------------------------
GameObject::GameObject(GameState* gs, const string& name): m_state(gs), m_name(name), m_id(m_next_id++)
{
}

//------------------------------------Destructor----------------------------------------------------
GameObject:: ~GameObject() {

}

//------------------------------------init()--------------------------------------------------------
void GameObject::init() {

}

//------------------------------------draw()--------------------------------------------------------
void GameObject::draw() {

}

//------------------------------------update()------------------------------------------------------
void GameObject::update(float dt) {

}
int GameObject::m_next_id = 1;
