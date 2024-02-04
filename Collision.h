#pragma once
#include <sgg/graphics.h>
#include "box.h"
#include <vector>
#include "GameObject.h"
#include "GameState.h"
#include "Player.h"  
#include "Level.h"

using namespace std;

class Collision {
private:
    class GameState* gamestateInstance;
    static Collision* m_unique_Collision;
    Collision();
public:
    ~Collision();
    void DownCollision();
    void SideCollision();
    static Collision* getCollision();
};

