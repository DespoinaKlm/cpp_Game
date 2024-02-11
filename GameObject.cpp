#include <sgg/graphics.h>
#include "GameObject.h"
#include "GameState.h"
#include <iostream>
#include <fstream>

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
//-----------------------------------loadFileGameObject()---------------------------------------------
vector<string> GameObject::loadFileGameObject(string movement)
{
    vector<string> m_sprites;

    ifstream inputFile;
    inputFile.open("Animation.txt");
    if (inputFile.is_open()) {
        std::string line;
        while (inputFile.good())
        {
            std::getline(inputFile, line);
            if (line.find(movement) != std::string::npos)
            {
                m_sprites.push_back(GameState::get_Gamestate()->getFullAssetPath(line));

            }
        }
        inputFile.close();
    }
    else
    {
        cerr << "failed to open the file" << endl;
    }
    return m_sprites;
}
//------------------------------------update()------------------------------------------------------
void GameObject::update(float dt) {

}
//---------------------------------------------------------------------------------------------------
int GameObject::m_next_id = 1;
