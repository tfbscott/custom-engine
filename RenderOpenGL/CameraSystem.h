#pragma once
#include "dlldef.h"
#include "Core.h"
#include "Camera.h"

namespace System
{
	class CE_RENDEROGL_API CameraSystem : public AssignedSystem<Component::Camera>
	{
		virtual void Update(float dt);
	};
}