#pragma once
#include <iostream>
#include <fstream>
#include "Player.h"
#include <sgg/graphics.h>
#include "GameState.h"

using namespace std;

class Animation {
private:
    Animation();
    GameState* gameState;
    vector<string> m_sprites;
    const string m_filename = "Animation.txt";
    static Animation* m_uniqueAnimation;
   

public:
    void update(float dt);
    void draw();
    static Animation* getInstance();
    ~Animation();
    vector<string> loadFile(string customFilename, string movement);
};
