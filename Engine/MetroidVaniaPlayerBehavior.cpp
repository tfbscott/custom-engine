#include "MetroidVaniaPlayerBehavior.h"
#include "Kinematics.h"
#include "CollisionSystem.h"
#include "Transform.h"

//TODO: Make this a setting
#define DEADZONE 0.1f

namespace Component
{

	void MetroidVaniaPlayerBehavior::OnStart()
	{
		playerState = 0;
		BindKeyAction("Walk_Y", this, &MetroidVaniaPlayerBehavior::OnXAxis);
		BindKeyAction("Walk_Left", this, &MetroidVaniaPlayerBehavior::OnWalkLeft);
		BindKeyAction("Walk_Right", this, &MetroidVaniaPlayerBehavior::OnWalkRight);
		BindKeyAction("Walk_Y", this, &MetroidVaniaPlayerBehavior::OnXAxis);
		BindKeyAction("Walk_X", this, &MetroidVaniaPlayerBehavior::OnYAxis);
		BindKeyAction("Jump", this, &MetroidVaniaPlayerBehavior::OnJump);
	}

	void MetroidVaniaPlayerBehavior::OnUpdate(float dt)
	{
		Component::Kinematics* phys = parent->GetComponent<Component::Kinematics>();


		switch (playerState)
		{
		case 1:
			yMovement = 1;

			if (stateTimer < 0)
			{
				EnterJumpArc();
			}
			break;
		case 2:
			yMovement = sin((stateTimer * 3.14f) / jumpArcTimer);

			if (stateTimer < 0)
			{
				playerState = 3;
			}
			break;
		case 3:
			yMovement = -1;

			if (CheckGround())
			{
				playerState = 0;
			}

			break;
		case 0:
			yMovement = 0;
		default:
			break;
		}

		if (stateTimer >= 0)
		{
			stateTimer -= dt;
		}

	
		phys->SetVelocity(glm::vec3(0.25f * xMovement,  0.25 * yMovement, 0));
	}

	void MetroidVaniaPlayerBehavior::OnCollision(Object::GameObject* me, Object::GameObject* them)
	{

	}

	bool MetroidVaniaPlayerBehavior::OnXAxis(int index, float val)
	{
		if (val > DEADZONE)
		{
			xMovement = val;
		}
		else
		{
			xMovement = 0;
		}
		return false;
	}

	bool MetroidVaniaPlayerBehavior::OnWalkLeft(int index, float val)
	{
		if (val > DEADZONE)
		{
			xMovement = -1;
		}
		else
		{
			xMovement = 0;
		}
		return false;
	}

	bool MetroidVaniaPlayerBehavior::OnWalkRight(int index, float val)
	{
		if (val > DEADZONE)
		{
			xMovement = 1;
		}
		else
		{
			xMovement = 0;
		}
		return false;
	}

	bool MetroidVaniaPlayerBehavior::OnYAxis(int index, float val)
	{
		return false;
	}

	bool MetroidVaniaPlayerBehavior::OnAttack(int index, float val)
	{
		return false;
	}

	bool MetroidVaniaPlayerBehavior::OnJump(int index, float val)
	{
		if (val >= 0.5)
		{
			if (playerState == 0)
			{
				EnterJumpStart();
			}
		}
		else
		{
			if (playerState == 1)
			{
				EnterJumpArc();
			}
		}	
		return false;
	}

	void MetroidVaniaPlayerBehavior::EnterJumpStart()
	{
		playerState = 1;

		stateTimer = jumpStartTimer;
	}

	void MetroidVaniaPlayerBehavior::EnterJumpArc()
	{
		playerState = 2;

		stateTimer = jumpArcTimer;
	}

	bool MetroidVaniaPlayerBehavior::CheckGround()
	{
		Component::Transform* tran = GetParent()->GetComponent<Transform>();

		glm::vec3 start = tran->GetPosition() - glm::vec3(0, 1.0f, 0);

		System::CollisionSystem* colSys = GetParent()->GetCore()->GetSystem<System::CollisionSystem>();

		System::RaycastData rdata;

		rdata.ignore.push_back(GetParent());

		Component::RaycastReturn hit;

		return colSys->PerfromRayCast(start, glm::vec3(0, -0.01f, 0), hit, rdata);
	}
}