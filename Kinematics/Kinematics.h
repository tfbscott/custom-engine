#pragma once
#include "dlldef.h"
#include "Core.h"
#include "glm/glm.hpp"


namespace Component
{
	class Kinematics : public BaseComponent
	{
	public:

		CE_KINELIB_API Kinematics();

		CE_KINELIB_API ~Kinematics();

		CE_KINELIB_API void Update(float);

		CE_KINELIB_API const glm::vec3& GetVelocity() const;

		CE_KINELIB_API const glm::vec3& GetAcceleration() const;

		CE_KINELIB_API void SetVelocity(const glm::vec3& v);

		CE_KINELIB_API void SetAcceleration(const glm::vec3& a);

	private:
		glm::vec3 velocity;
		glm::vec3 acceleration;

	};
}