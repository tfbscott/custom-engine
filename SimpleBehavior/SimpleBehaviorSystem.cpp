#include "pch.h"
#include "SimpleBehaviorSystem.h"

namespace System
{
	void SimpleBehaviorSystem::Update(float dt)
	{
		for (Component::BaseComponent* c : components_)
		{
			Component::SimpleBehavior* bc = dynamic_cast<Component::SimpleBehavior*>(c);

			if (bc->first_)
			{
				bc->OnStart();
				bc->first_ = false;

				//Subscribe to the collision event
				bc->SubCollisionEventCallback();
			}

			bc->OnUpdate(dt);
		}
	}
}