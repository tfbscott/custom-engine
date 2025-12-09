#pragma once
#include "SimpleBehavior.h"

namespace Component 
{
	class MetroidVaniaPlayerBehavior : public SimpleBehavior
	{
	public:

		virtual void OnStart();

		virtual void OnUpdate(float dt);

		virtual void OnCollision(Object::GameObject* me, Object::GameObject* them);

	private:
		//Input Functions
		bool OnXAxis(int index, float val);

		bool OnWalkRight(int index, float val);

		bool OnWalkLeft(int index, float val);
		
		bool OnYAxis(int index, float val);

		bool OnAttack(int index, float val);

		bool OnJump(int index, float val);

		void EnterJumpStart();

		void EnterJumpArc();

		bool CheckGround();
	
		/*
		0 - On Floor
		1 - Jump Start
		2 - Jump Peak
		3 - Falling
		*/
		int playerState;

		float stateTimer;

		float jumpStartTimer = 2;
		float jumpArcTimer = 1;

		float xMovement;
		float yMovement;
	};
}