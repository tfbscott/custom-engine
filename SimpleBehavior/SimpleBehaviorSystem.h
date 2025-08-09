#pragma once
#include "SimpleBehavior.h"
#include "Core.h"

namespace System
{
	class SimpleBehaviorSystem : public AssignedSystem<Component::SimpleBehavior>
	{
	public:
		//Update is handled via inherented function
		virtual void Update(float);
	};
}