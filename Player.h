#pragma once
#include <sgg/graphics.h>
#include "GameObject.h"
#include "GameState.h"
#include "box.h"
#include <filesystem>
#include "Blocks.h"

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
	float indexDustAnimation = 0;
	float animation_speed = 0.5;
	float x_d=0, y_d=0;
	int s;
	//health
	float m_health;
	float m_health_max = 1000;
	//Animation
	vector<string> m_sprites_player;
	vector<string> dust_animation;
	
	const float m_accel_horizontal = 20.0f;
	const float m_accel_vertical = 4500.0f;
	const float m_max_velocity = 40.0f;
	const float m_gravity = 9.8f;

	//attack Cooldown
	float attackCooldown;
	float attackCooldownMax;

	//movement
	bool canAttackN;
	bool damage;
	bool damageAnimation;
	bool right;
	bool m_IsJumping;
	bool m_IsRunning;
	bool m_Attacking;
	bool m_Falling;
	bool m_Grounding;
	bool m_IsPickingUp;
	bool plusAttack;
	bool weaponIsActive;
	bool dead;
	bool drawJump;

	//functions
	void movePlayer(float dt);

public:
	float delta_time;
	float m_vx = 0.0f;
	float m_vy = 0.0f;
	Player(GameState* gs, const string& name,float health=1000);
	~Player();
	void drawHealth(float health,float max_health,int length);
	//----------getPosition()----------------
	float getPosX() const{ return m_pos_x; }
	float getPosY() const { return m_pos_y; }
	inline bool getGround() const {return m_Grounding;}
	inline void setJumping(bool answer) { m_IsJumping = answer; }
	inline void setGround(bool answer) { m_Grounding =answer; }
	inline bool isJumping() { return m_IsJumping; }
	inline bool isAttacking() { return m_Attacking; }
	inline bool isPickingUp()  { return m_IsPickingUp; }
	
	inline bool isGrounding() { return m_Grounding; }
	inline bool PlusAttack()  { return plusAttack; }
	inline void setPlusAttack(bool answ) { plusAttack = answ; }
	inline float getGravity()  { return m_gravity; }
	inline bool isActiveWeapon()  { return weaponIsActive; }
	inline bool isRight()  { return right; }
	inline bool isLeft()  { return left; }
	const bool canAttack();
	void updateCooldownAttack();
	void drawDustAnimation();
	void update(float dt) override;
	void init() override;
	void draw() override;
	Player &PlusHealth(float plushealth);
	Player &Damage(float damage);
	int get_Attack();
	float get_Health();
	void set_Health(float health);
	void playerDrawDeath();
	void dustAnimation(vector<string>dust);

protected:
	void debugDraw();
};
