#pragma once
#include "Bird.h"
#include <sgg/graphics.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring> // Include for strerror
#include <cerrno>  // Include for errno
#include "GameState.h"
#include "GameObject.h"
#include <vector>
#include <string>
#include <filesystem>

using namespace std;
//----------------------------Constructor-------------------------------------
Bird::Bird(GameState* gs, const string& name, int health):Enemy(gs,name,health), m_filename("Bird.txt")
{
    //bird_enemy=loadFileIntoVector(m_filename);
    m_width = enemy_size;
    m_height = enemy_size;
    init();
    loadFileIntoVector("bird");
}
//----------------------------Destructor-------------------------------------
Bird::~Bird()
{
}
//----------------------------Constructor-------------------------------------
vector<string> Bird::loadFileIntoVector(const std::string& filePath)
{
    vector<std::string> fileContents;
    ifstream inputFile(filePath);
   
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line))
        {
            fileContents.push_back(m_state->getFullAssetPath(line));
            cout << m_state->getFullAssetPath(line);
        }
        inputFile.close();
    }
    else {
        //cerr << "failed to open the file" << endl;
    }
    return fileContents;
}
//----------------------------Constructor-------------------------------------
void Bird::update(float dt)
{
    if (reverse > 5)
    {
        m_pos_x -= speed_enemy * graphics::getDeltaTime();
    }
    else
    {
        m_pos_x += speed_enemy * graphics::getDeltaTime();
    }
   
    if (m_pos_x < -enemy_size && reverse>5)
    {
        setActive(false);
    }
    if ( m_pos_x>CANVAS_WIDTH&& reverse<=5) 
    {
        setActive(false);
    }
    if (m_enemy_health <= 0) {
        setActive(false);
    }
    Enemy::update(dt);
}
//----------------------------Constructor-------------------------------------
void Bird::init()
{
    //Brush bird
    br_enemy_birds.fill_opacity = 1.1f;
    br_enemy_birds.outline_opacity = 0.0f;
    br_enemy_birds.texture = m_state->getFullAssetPath("bird1.png");

    reverse = rand() % 10 + 1;
    if (reverse >5) {
        m_pos_x = CANVAS_WIDTH + enemy_size * 1.1f;
    }
    else
    {
        m_pos_x =enemy_size * ( - 1)*1.1f;
    }
    
    m_pos_y = CANVAS_HEIGHT * rand() / (float)RAND_MAX ;
    
    bird_enemy.push_back(m_state->getFullAssetPath("bird1.png"));
    bird_enemy.push_back(m_state->getFullAssetPath("bird2.png"));
    bird_enemy.push_back(m_state->getFullAssetPath("bird3.png"));
    bird_enemy.push_back(m_state->getFullAssetPath("bird4.png"));
    bird_enemy.push_back(m_state->getFullAssetPath("bird5.png"));
    bird_enemy.push_back(m_state->getFullAssetPath("bird6.png"));
    bird_enemy.push_back(m_state->getFullAssetPath("bird7.png"));
    bird_enemy.push_back(m_state->getFullAssetPath("bird8.png"));
    bird_enemy.push_back(m_state->getFullAssetPath("bird9.png"));
    bird_enemy.push_back(m_state->getFullAssetPath("bird10.png"));
    //bird_enemy = loadFileIntoVector(m_filename);
    Enemy::init();
}
//----------------------------draw-------------------------------------
void Bird::draw()
{
    float x = m_pos_x + m_state->m_global_offset_x;
    float y = m_pos_y + m_state->m_global_offset_y;
    cout << m_state->m_global_offset_x << "             " << m_state->m_global_offset_y<<endl;
    int s = int(fmodf(1000.0f - m_pos_x * 0.05f, bird_enemy.size()));
    br_enemy_birds.texture = bird_enemy[s];
    if (reverse>5)
    {
        graphics::setScale(-1.0f, 1.0f);
    }
    graphics::drawRect(m_pos_x, m_pos_y, enemy_size *0.8, enemy_size * 0.8, br_enemy_birds);
    
    cout << m_pos_x << "               " << m_pos_y << endl;
    cout << x << "                 " << y << endl;
    //graphics::drawRect(x, y, enemy_size / 2, enemy_size / 2, br_enemy_birds);
    graphics::resetPose();

    if (m_state->m_debugging)
    {
        debugDrawEnemy(m_pos_x, m_pos_y);
        //debugDrawEnemy(x, y);
    }

    Enemy::draw();
}
//----------------------------debugDrawEnemy-------------------------------------
void Bird::debugDrawEnemy(float x, float y)
{
    graphics::Brush br_enemy_birdsD;
    br_enemy_birdsD.outline_opacity = 1.0f;
    br_enemy_birdsD.fill_opacity = 0.2f;
    br_enemy_birdsD.fill_color[0] = 1.0f;
    br_enemy_birdsD.fill_color[1] = 0.3f;
    br_enemy_birdsD.fill_color[2] = 0.0f;
    br_enemy_birdsD.outline_color[0] = 0.2f;
    br_enemy_birdsD.outline_color[1] = 1.2f;
    br_enemy_birdsD.outline_color[2] = 0.3f;
    graphics::drawRect(x, y, enemy_size, enemy_size, br_enemy_birdsD);
}
/*
vector<string> Bird::loadFileIntoVector(const string& movement)
{
    vector<std::string> fileContents;
    fs::path fullPath = fs::absolute("Bird.txt");
    cout << "Absolute path: " << fullPath << std::endl;

    ifstream inputFile(fullPath);

    if (!inputFile) {
        cout << "Error: Unable to open the file." << endl;
        return fileContents; // Return an empty vector in case of an error.
    }

    string line;
    while (getline(inputFile, line)) {
        fileContents.push_back(line);
        cout << line << endl;
    }

    inputFile.close();

    return fileContents;
}


vector<string> loadFileIntoVector(const string movement) {
    vector<string> fileContents;
    string filePath = "Bird.txt";
    ifstream inputFile(filePath);

    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            string n = GameState::get_Gamestate()->getFullAssetPath(line);
            fileContents.push_back(n);
            cout << n;
        }
        inputFile.close();
    }
    else {
        cerr << "failed to open the file" << endl;
    }

    return fileContents;
}
*/