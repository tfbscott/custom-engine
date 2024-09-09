#pragma once
#include "dlldef.h"
#include "Core.h"
#include "Collider.h"

#include <list>

namespace System
{

	struct RaycastData
	{
		RaycastData() : ignore() {}

		std::list<Object::GameObject*> ignore;
	};

	class CE_KINELIB_API CollisionSystem : public AssignedSystem<Component::Collider>
	{
	public:
		//This system will need an overhauled update function
		virtual void Update(float);
	

		bool PerfromRayCast(const glm::vec3& point, const glm::vec3& delta, Component::RaycastReturn& hit, const RaycastData& data = RaycastData());

	private:
	};
}
