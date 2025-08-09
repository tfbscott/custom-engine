#pragma once
#include "Core.h"
#include "Camera.h"

namespace System
{
	class CameraSystem : public AssignedSystem<Component::Camera>
	{
		virtual void Update(float dt);
	};
}