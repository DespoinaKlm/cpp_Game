#pragma once
#include "Vector2D.h"
//helpful for the physics
#define Forward_R 1
#define Backward_R -1
#define Downward_R 1
#define Upward_R -1
#define Gravity 9.8f

class Rigit_Body_Physics {
private:

	float m_Gravity=Gravity;
	const float m_Mass = 1.0f;
	Vector2D m_Force;
	Vector2D m_Friction;
	Vector2D m_Position;
	Vector2D m_Velocity;
	Vector2D m_Accelaration;

public:
	//------------------Constructor----------------------//
	Rigit_Body_Physics() {};

	//-------------------Destructor---------------------//
	~Rigit_Body_Physics() {};

	//------------------Force---------------------------//
	inline void ApplyForce(Vector2D Fr) { m_Force = Fr; }
	inline void ApplyForceX(float Fx) { m_Force.m_x = Fx; }
	inline void ApplyForceY(float Fy) { m_Force.m_y = Fy; }
	inline void UnSetForce() { m_Force = Vector2D(0, 0); }

	//------------------Friction---------------------------//
	inline void ApplyFriction(Vector2D Fr) { m_Friction = Fr; }
	inline void UnSetFriction() { m_Friction = Vector2D(0, 0); }

	//------------------Getters---------------------------//
	inline float GetGravity() { return m_Gravity; }
	inline void setGravity(float gravity) { m_Gravity = gravity; }
	inline float GetMass() { return m_Mass; }
	Vector2D getPosition(){ return m_Position; }
	Vector2D getVelocity() { return m_Velocity; }
	inline void setVelocityY(float velocity) { m_Velocity.m_y=velocity; }
	inline void setVelocityX(float velocity) { m_Velocity.m_x = velocity; }
	Vector2D getAccelaratiom(){ return m_Accelaration; }

	void Update(float dt) {
		m_Accelaration.m_x = (m_Force.m_x + m_Friction.m_x) / m_Mass;
		m_Accelaration.m_y = m_Gravity + (m_Force.m_y / m_Mass);
		m_Velocity = m_Accelaration *(dt / 1000);
		m_Position = m_Velocity * dt;
	}
};
