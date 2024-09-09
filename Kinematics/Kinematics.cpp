#include "pch.h"
#include "Kinematics.h"
#include "Transform.h"
#include "GameObject.h"

namespace Component
{
	Kinematics::Kinematics() : velocity(0), acceleration(0)
	{

	}

	Kinematics::~Kinematics()
	{

	}

	void Kinematics::Update(float dt)
	{
		//Transform should ALWAYS be index 0
		//This should be replaced with a templated GetComponent later
		Transform* t = parent->GetComponent<Transform>();//dynamic_cast<Transform*>(parent->GetComponent(0));

		velocity = velocity + (acceleration * dt);
		t->SetPosition(t->GetPosition() + (velocity * dt));
	}


	const glm::vec3& Kinematics::GetVelocity() const
	{
		return velocity;
	}

	const glm::vec3& Kinematics::GetAcceleration() const
	{
		return acceleration;
	}

	void Kinematics::SetVelocity(const glm::vec3& v)
	{
		velocity = v;
	}

	void Kinematics::SetAcceleration(const glm::vec3& a)
	{
		acceleration = a;
	}
}