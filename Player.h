#pragma once
#include <sgg/graphics.h>
#include "GameObject.h"
#include "GameState.h"
#include "box.h"

using namespace std;

class Player : public GameObject, public Box
{
private:
	//brush
	graphics::Brush br_player;
	graphics::Brush br_player_health;

	//animation index
	float indexPlayer = 0;
	float indexDustAnimation = 0;
	int s;

	//health
	int block_health_size = 25;
	float m_health;
	float m_health_max = 1000;
	
	//Animation
	vector<string> m_sprites_player;
	vector<string> dust_animation;
	
	//movement
	const float m_accel_horizontal = 30.0f;
	const float m_accel_vertical = 4500.0f;
	const float m_max_velocity = 70.0f;
	const float m_gravity = 9.8f;

	//bool movement
	bool canAttackN;
	bool damage;
	bool damageAnimation;
	bool right;
	bool m_Attacking;
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

	//inheritance GameObject
	void update(float dt) override;
	void init() override;
	void draw() override;

	//position
	float getPosX() const{ return m_pos_x; }
	float getPosY() const { return m_pos_y; }

	//help for animation and movements
	inline bool isAttacking() const { return m_Attacking; }
	inline bool isPickingUp() const { return m_IsPickingUp; }
	inline bool PlusAttack()const { return plusAttack; }
	inline void setPlusAttack(bool answ) { plusAttack = answ; }
	inline float getGravity() const { return m_gravity; }
	inline bool isActiveWeapon() const { return weaponIsActive; }
	inline bool isRight()  const { return right; }
	void drawDustAnimation();
	void playerDrawDeath();
	void dustAnimation(vector<string>dust);

	//health player
	void drawHealth(float health,float max_health,int length);
	Player &PlusHealth(float plushealth);
	Player &Damage(float damage);
	float get_Health();
	void set_Health(float health);

	//attack
	int get_Attack();

protected:
	//debug
	void debugDraw();
};
