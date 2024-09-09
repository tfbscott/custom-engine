#pragma once
#include "SimpleBehavior.h"
#include "glm/vec3.hpp"

namespace Component
{
	class Transform;

	class ShrinkandKill : public SimpleBehavior
	{
		virtual void OnStart();

		virtual void OnUpdate(float dt);

		float runTime_;

		float timer_;

		glm::vec3 startingScale_;

		Transform* tran_;
	};
}