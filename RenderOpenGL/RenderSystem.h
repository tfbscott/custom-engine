#pragma once
#include "Core.h"
#include "RenderComponent.h"

namespace System
{
	class RenderSystem : public AssignedSystem<Component::RenderComponent>
	{
	public:

		virtual void Update(float);

		virtual void Sync();

	private:
	};
}
