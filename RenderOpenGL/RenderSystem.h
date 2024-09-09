#pragma once
#include "dlldef.h"
#include "Core.h"
#include "RenderComponent.h"

namespace System
{
	class CE_RENDEROGL_API RenderSystem : public AssignedSystem<Component::RenderComponent>
	{
	public:

		virtual void Update(float);

		virtual void Sync();

	private:
	};
}
