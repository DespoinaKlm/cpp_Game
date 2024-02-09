#pragma once
#include "Collision.h"
#include "GameState.h"
#include "Rigit_Body_Physics.h"
#include <iostream>
#include "Camera.h"

using namespace std;
Collision::Collision()
{
    if (!gamestateInstance) {
		gamestateInstance = GameState::get_Gamestate();
	}
}

Collision::~Collision()
{
    delete gamestateInstance;
}

void Collision::DownCollision() {


    auto player = GameState::get_Gamestate()->getPlayer();
    auto bl = GameState::get_Gamestate()->getlevel()->getBlock();
    auto boxs = GameState::get_Gamestate()->getlevel()->getLevelMap();

    //dokimi gia na dw an kanei collision
    for (int row = 0; row < boxs.size(); row++) {
        for (int col = 0; col < boxs[row].size(); col++) {
            if (boxs[row][col] == 'X') {
                Blocks block = bl[row][col];
                //cout << "BLOCK " << bl[row][col].m_pos_x << " " << bl[row][col].m_pos_y << " " << bl[row][col].m_width << " " << bl[row][col].m_height << endl;
                //cout << "PLAYER "<< player->m_pos_x << "   " << player->m_pos_y << endl;
                if (player->intersect(block))
                    printf("*");
            }
        }
    }

    //dokimi collision me insertDown
    for (int row = 0; row < boxs.size(); row++) {
        for (int col = 0; col < boxs[row].size(); col++) {
            if (boxs[row][col]=='X') {
                float offset = 0.0f;
                //std:: cout << "here " <<bl[row][col].m_pos_x << endl << bl[row][col].m_pos_y << endl << bl[row][col].m_width << endl << bl[row][col].m_height << endl;
                Blocks block = bl[row][col];
                //cout << GameState::get_Gamestate()->getPlayer()->intersectDown(block);
                //cout << GameState::get_Gamestate()->getPlayer()->m_pos_x<< endl;
                if (offset = player->intersectDown(block))
                {
                    //GameState::get_Gamestate()->getPlayer()->m_pos_y += offset;
                    player->m_pos_y += offset;
                    if (GameState::get_Gamestate()->getPlayer()->getVelocity().m_y > 1.0f)
                        graphics::playSound(GameState::get_Gamestate()->getFullAssetPath("big_impact.wav"), 0.5f);

                    //GameState::get_Gamestate()->getPlayer()->setVelocityY(0.0f);
                    player->setVelocityY(0.0f);
                    break;
                }
            }
            else {
                //cout << row << col<< endl;
                continue;
            }
        }
    }
}
       
void Collision::SideCollision() {
    auto player = GameState::get_Gamestate()->getPlayer();
    auto bl = GameState::get_Gamestate()->getlevel()->getBlock();
    auto boxs = GameState::get_Gamestate()->getlevel()->getLevelMap();
    //dokimi gia na dw an kanei collision
    for (int row = 0; row < boxs.size(); row++) {
        for (int col = 0; col < boxs[row].size(); col++) {
            if (boxs[row][col] == 'X') {
                Blocks block = bl[row][col];
                if (player->intersect(block))
                    printf("*");
            }
        }
    }
    //dokimi collision me insertDown
    for (int row = 0; row < boxs.size(); row++) {
        for (int col = 0; col < boxs[row].size(); col++) {
            if (boxs[row][col] == 'X') {
                float offset = 0.0f;
                //std:: cout << "here " <<bl[row][col].m_pos_x << endl << bl[row][col].m_pos_y << endl << bl[row][col].m_width << endl << bl[row][col].m_height << endl;
                Blocks block = bl[row][col];
                //cout << "effect "<< GameState::get_Gamestate()->getPlayer()->intersectDown(block);
                //cout << GameState::get_Gamestate()->getPlayer()->m_pos_x<< endl;
                if (offset = player->intersectSideways(block))
                {
                    GameState::get_Gamestate()->getPlayer()->m_pos_x += offset;
                    GameState::get_Gamestate()->getPlayer()->setVelocityX(0.0f);
                    break;
                }
            }
            else {
                //cout << row << col<< endl;
                continue;
            }
        }
    }
}
//PALIES PROSPATHEIES POU MPOREI NA MOU FANOYN XRISIMES STO MELLON
 /*
        // Debugging information
       // cout << "Player: (" << player->m_Transform->m_x << " , " << player->m_Transform->m_y << ") " << endl << "Box: (" << box.m_pos_x << " , " << box.m_pos_y << ") " << endl;
        //cout << "Camera: (" << Camera::GetCamera()->GetPosition().m_x<< " , " << Camera::GetCamera()->GetPosition().m_y << ") " << endl;
        //cout << player->intersectDown(box) << "  nooooo " << endl;
        //cout << (player->m_Transform->m_y == box.m_pos_y) << "  yesssss " << endl;
        //cout << (player->m_Transform->m_x== box.m_pos_x) << "  yesssss " << endl;
        // Check for collision with the ground using intersectDown method
        //if (offsetY=player->intersectDown(box)) {
            cout << "Collided with the ground!" << endl;

            // Set the player's state to grounded
            player->setGround(true);

            // Adjust the player's y position based on the collision response
            player->m_Transform->m_y += offsetY;

            // Play sound for impact if the player is falling
            if (player->rigit->getVelocity().m_y > 1.0f)
                graphics::playSound(GameState::get_Gamestate()->getFullAssetPath("big_impact.wav"), 0.5f);

            // Set vertical velocity to zero after collision
            player->rigit->setVelocityY(0.0f);

            // Exit the loop after the first collision (remove if checking multiple blocks)
            break;
        }
        
        */
        
        //else {
            // If no collision, set the player's state to not grounded
        //    player->setGround(false);
        //}
    //}



/*
void Collision::sideCollision() {
    auto player = GameState::get_Gamestate()->getPlayer();
    auto level = GameState::get_Gamestate()->getlevel();

    // Save the previous x position before checking for collisions
    player->m_PreviousPosition.m_x = player->m_Transform->m_x;

    for (auto& box : level->getBlock()) {

        // Debugging information
        cout << "Player: (" << player->m_Transform->m_x << " , " << player->m_Transform->m_y << ") " << endl
            << "Box: (" << box.m_pos_x << " , " << box.m_pos_y << ") " << endl;
        cout << player->intersectDown(box) << "  yessssss " << endl;
        // Check for collision on the horizontal axis using intersectSideways method
        if (player->intersectSideways(box)) {
            // Adjust the player's x position based on the collision
            float offset = player->intersectSideways(box);
            player->m_Transform->m_x += offset;

            // Set horizontal velocity to zero after collision
            player->rigit->setVelocityX(0.0f);

            // Set the player's state to not grounded (adjust based on your game's logic)
            player->setGround(false);

            // Exit the loop after the first collision (remove if checking multiple blocks)
            break;
        }
        else {
            // If no collision, set the player's state to grounded
            player->setGround(true);
        }
    }
}
*/



Collision* Collision::getCollision()
{
    if (m_unique_Collision == nullptr) {
        m_unique_Collision = new Collision();
    }
    return m_unique_Collision;
}
Collision* Collision::m_unique_Collision = nullptr;

	