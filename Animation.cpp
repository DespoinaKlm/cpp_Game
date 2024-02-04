#pragma once
#include <sgg/graphics.h>
#include "Animation.h"
#include <iostream>
#include <fstream>
#include "Player.h"
#include "GameState.h"

Animation* Animation::m_uniqueAnimation = nullptr;

Animation::Animation(){

}

void Animation::update(float dt)
{
}

void Animation::draw()
{
    
}

Animation::~Animation()
{
    if (m_uniqueAnimation != nullptr) {
        delete m_uniqueAnimation;
        m_uniqueAnimation = nullptr;
    }
}

vector<string> Animation::loadFile(string customFilename, string movement)
{
    vector<string> m_sprites;

    ifstream file("Animation.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (movement.find(line) != string::npos) {
                m_sprites.push_back(gameState->getFullAssetPath(line));
                cout << line << endl;
            }
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << customFilename << std::endl;
    }
    return m_sprites;
}

Animation* Animation::getInstance() {
    if (m_uniqueAnimation == nullptr) {
        m_uniqueAnimation = new Animation();
        return m_uniqueAnimation;
    }
}

    /*
    vector<string> Animation::loadFile(string filename, string movement) {

    vector<string> m_sprites;

    ifstream file("Animation.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (movement.find(line) != string::npos) {
                m_sprites.push_back(gameState->getFullAssetPath(line));
                cout << line << endl;
            }
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    return m_sprites;
}
    
    */




