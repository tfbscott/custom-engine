#pragma once
#include "dlldef.h"
#include "SimpleBehavior.h"
#include "Core.h"

namespace System
{
	class CE_BEHLIB_API SimpleBehaviorSystem : public AssignedSystem<Component::SimpleBehavior>
	{
	public:
		//Update is handled via inherented function
		virtual void Update(float);
	};
}