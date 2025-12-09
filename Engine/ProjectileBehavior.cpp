#include "ProjectileBehavior.h"

#include "Kinematics.h"
#include "Transform.h"
#include "ShooterPlayerBehavior.h"

#include "GameStateManager.h"

namespace Component
{
	void ProjectileBehavior::OnStart()
	{
		phys = GetParent()->GetComponent<Kinematics>();
	}

	void ProjectileBehavior::OnUpdate(float dt)
	{

	}

	void ProjectileBehavior::OnCollision(Object::GameObject* me, Object::GameObject* them)
	{
		phys->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));

		phys->SetAcceleration(glm::vec3(0.0f, 0.0f, 0.0f));

		if(them->GetIdentifier() == "Hole")
		{ 
			GetParent()->GetCore()->StateManager->SetNextGameState(GetParent()->GetCore()->StateManager->GetCurrentState() + 1);
		}
		else
		{
			if (thrower)
			{
				thrower->GetComponent<Transform>()->SetPosition(GetParent()->GetComponent<Transform>()->GetPosition());

				//This is a sketchy way to prevent multiple disks
				thrower->GetComponent<ShooterPlayerBehavior>()->canFire = true;
			}

		}
		GetParent()->Destroy();
		
	}
}