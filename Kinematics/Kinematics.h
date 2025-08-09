#pragma once
#include "Core.h"
#include "glm/glm.hpp"


namespace Component
{
	class Kinematics : public BaseComponent
	{
	public:

		Kinematics();

		~Kinematics();

		void Update(float);

		const glm::vec3& GetVelocity() const;

		const glm::vec3& GetAcceleration() const;

		void SetVelocity(const glm::vec3& v);

		void SetAcceleration(const glm::vec3& a);

	private:
		glm::vec3 velocity;
		glm::vec3 acceleration;

	};
}