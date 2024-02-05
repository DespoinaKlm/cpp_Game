#pragma once
#include <sgg/graphics.h>
#include "GameObject.h"
#include "GameState.h"
#include "box.h"
#include <filesystem>
#include "Blocks.h"

//if we want to set gravity to 9 we have to change the jump_time 
#define jump_time 25.0f
#define jump_force 10.0f
#define Attack_time 20.0f

using namespace std;

class Player : public GameObject, public Box
{
private:
	//brush
	int block_health_size = 25;
	Blocks playerBlocks;
	graphics::Brush br_player;
	graphics::Brush br_player_health;
	float indexPlayer=0;

	//health
	float m_health;
	float m_health_max = 1000;
	int countdownAttack=0;
	
	//Animation
	vector<string> m_sprites_player;
	
	const float m_accel_horizontal = 20.0f;
	const float m_accel_vertical = 4500.0f;
	const float m_max_velocity = 25.0f;
	const float m_gravity = 9.8f;

	//movement
	bool canAttack;;
	bool right;
	bool left;
	bool m_IsJumping;
	bool m_IsRunning;
	bool m_Attacking;
	bool m_Falling;
	bool m_Grounding;
	bool m_IsPickingUp;
	bool plusAttack;
	bool weaponIsActive;
	bool cantMove;
	bool dead;

	//total time
	float JumpTime;
	float JumpForce;
	float m_AttackingTime;

	//class for Animation and Collision
	class Animation* animationInstance=0;

	//functions
	void movePlayer(float dt);
	void AnimationPlayer();

public:
	float delta_time;
	float m_vx = 0.0f;
	float m_vy = 0.0f;
	Player(GameState* gs, const string& name,float health=1000);
	~Player();
	void drawHealth(float health,float max_health,int length);
	Blocks m_weapon;
	//----------getPosition()----------------
	float getPosX() const{ return m_pos_x; }
	float getPosY() const { return m_pos_y; }
	inline graphics::Brush getBrush() { return br_player; }
	inline bool getGround() const {return m_Grounding;}
	inline void setJumping(bool answer) { m_IsJumping = answer; }
	inline void setGround(bool answer) { m_Grounding =answer; }
	inline bool isJumping() const{ return m_IsJumping; }
	inline bool isAttacking() const{ return m_Attacking; }
	inline bool isPickingUp() const { return m_IsPickingUp; }
	inline bool isGrounding() const{ return m_Grounding; }
	inline bool PlusAttack() const { return plusAttack; }
	inline void setPlusAttack(bool answ) { plusAttack = answ; }
	inline float getGravity() const { return m_gravity; }
	inline bool isActiveWeapon() const { return weaponIsActive; }
	inline bool isRight() const { return right; }
	inline bool isLeft() const { return left; }
	//inline void setHealth(float health) { m_health=health; }
	//inline float getHealth() const { return m_health; }

	void update(float dt) override;
	void init() override;
	void draw() override;
	Player &PlusHealth(float plushealth);
	Player &Damage(float damage);
	int get_Attack();
	float get_Health();
	void set_Health(float health);
	void playerDrawDeath();

protected:
	void debugDraw();
};
