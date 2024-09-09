#include "pch.h"
#include "SimpleBehavior.h"

namespace Component
{
	unsigned int SimpleBehavior::totalBehaviorCount = 0;

	SimpleBehavior::SimpleBehavior() : first_(true), keyCallbacks()
	{
		++totalBehaviorCount;

		behID = std::to_string(totalBehaviorCount);
	}

	void SimpleBehavior::OnDelete()
	{
		for (std::string& k : keyCallbacks)
		{
			GetParent()->GetCore()->inputManager->RemoveActionCallback(k, behID + '_' + k);
		}

	}

	void SimpleBehavior::CollisionEventFunction(Event::CollisionEventData* e)
	{
		OnCollision(e->me, e->them);
	}

	void SimpleBehavior::SubCollisionEventCallback()
	{
		GetParent()->AddEventCallback<Event::CollisionEventData, SimpleBehavior>(this, &SimpleBehavior::CollisionEventFunction);
	}

	void SimpleBehavior::Update(float dt)
	{
		if (first_)
		{
			OnStart();
			first_ = false;

			//Subscribe to the collision event
			SubCollisionEventCallback();
		}

		OnUpdate(dt);
	}


}