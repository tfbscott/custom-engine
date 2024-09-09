#pragma once
#include "SimpleBehavior.h"

namespace Component
{
	class Kinematics;

	class ProjectileBehavior : public SimpleBehavior
	{
	public:
		virtual void OnStart();

		virtual void OnUpdate(float dt);

		virtual void OnCollision(Object::GameObject* me, Object::GameObject* them);

		Object::GameObject* thrower;

	private:
		Kinematics* phys;
	};
}
