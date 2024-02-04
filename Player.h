#pragma once
#include <sgg/graphics.h>
#include "GameObject.h"
#include "GameState.h"
#include "box.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Properties.h"
#include "Rigit_Body_Physics.h"
#include "Point.h"
#include "Collision.h"
#include "Animation.h"
#include <filesystem>
#include "Blocks.h"

//if we want to set gravity to 9 we have to change the jump_time 
#define jump_time 25.0f
#define jump_force 10.0f
#define Attack_time 20.0f

using namespace std;

//player has health,attack,and weapons
class Player : public GameObject, public Box
{
private:
	//brush
	int block_health_size = 25;
	Blocks playerBlocks;
	graphics::Brush br_player;
	graphics::Brush br_player_health;
	graphics::Brush br_weapon;

	const string m_filename = "Animation.txt";
	vector<string> m_sprites;
	vector<string> m_attack;
	vector<string> loadFileIntoVector(const std::string& filePath,std::string player, std::string movement);
	
	//health
	float m_health;
	float m_health_max = 1000;
	
	//Animation
	vector<string> m_sprites_player;
	
	//Vector2D
	Vector2D direction;
	Vector2D velocity;
	Vector2D accel=Vector2D(20.0f , 4500.0f);

	const float m_accel_horizontal = 20.0f;
	//const float m_accel_horizontal = 100.0f;
	const float m_accel_vertical = 4500.0f;
	const float m_max_velocity = 25.0f;
	const float m_gravity = 9.8f;

	//movement
	bool m_IsJumping;
	bool m_IsRunning;
	bool m_Attacking;
	bool m_Falling;
	bool m_Grounding;
	bool m_IsPickingUp;
	bool plusAttack;
	bool weaponIsActive;
	bool cantMove;

	//total time
	float JumpTime;
	float JumpForce;
	float m_AttackingTime;

	//class for Animation and Collision
	class Animation* animationInstance=0;
	class Collision* collisionInstance=0;

	//functions
	void movePlayer(float dt);
	void movePlayerNew(float dt);
	void AnimationPlayer();

public:
	float delta_time;
	float m_vx = 0.0f;
	float m_vy = 0.0f;
	Player(GameState* gs, const string& name,float health=1000);
	~Player();
	Rigit_Body_Physics* rigit;
	void drawHealth(float health,float max_health,int length);
	Blocks m_weapon;
	//----------getPosition()----------------
	float getPosX() { return m_pos_x; }
	float getPosY() { return m_pos_y; }
	inline graphics::Brush getBrush() { return br_player; }
	inline Vector2D getDirection() { return direction; }
	inline Vector2D getVelocity() { return velocity; }
	inline bool getGround() {return m_Grounding;}
	inline void setVelocityX(float answer) { velocity.m_x = answer; }
	inline void setVelocityY(float answer) { velocity.m_y = answer; }
	inline void setJumping(bool answer) { m_IsJumping = answer; }
	inline void setGround(bool answer) { m_Grounding =answer; }
	inline bool isJumping() { return m_IsJumping; }
	inline bool isAttacking() { return m_Attacking; }
	inline bool isPickingUp() { return m_IsPickingUp; }
	inline bool isGrounding() { return m_Grounding; }
	inline bool PlusAttack() { return plusAttack; }
	inline void setPlusAttack(bool answ) { plusAttack = answ; }
	
	inline bool isActiveWeapon() { return weaponIsActive; }
	//inline void setHealth(float health) { m_health=health; }
	//inline float getHealth() const { return m_health; }

	void update(float dt) override;
	void init() override;
	void draw() override;
	int sword();
	Player &PlusHealth(float plushealth);
	Player &Damage(float damage);
	int get_Attack();
	float get_Health();
	void set_Health(float health);

protected:
	void debugDraw();
};
