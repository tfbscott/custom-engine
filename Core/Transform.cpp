#include "pch.h"
#include "Transform.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Component
{
	void Transform::Update(float dt)
	{

	}

	const glm::mat4& Transform::Get()
	{
		if (dirty)
		{
			transform = glm::translate(glm::mat4(1.0f), position_);
			transform = glm::rotate(transform, glm::radians(rotation_.x), glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(rotation_.y), glm::vec3(0.0f, 1.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(rotation_.z), glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::scale(transform, scale_);
			dirty = false;
		}

		return transform;
	}

	const glm::vec3& Transform::GetPosition()
	{
		return position_;
	}

	const glm::vec3& Transform::GetRotation()
	{
		return rotation_;
	}

	const glm::vec3& Transform::GetScale()
	{
		return scale_;
	}

	void Transform::SetPosition(const glm::vec3& p)
	{
		position_ = p;
		dirty = true;
	}

	void Transform::SetRotation(const glm::vec3& r)
	{
		rotation_ = r;
		dirty = true;
	}

	void Transform::SetScale(const glm::vec3& s)
	{
		scale_ = s;
		dirty = true;
	}

	bool Transform::IsDirty()
	{
		return dirty;
	}
}