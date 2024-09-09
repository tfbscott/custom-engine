#include "pch.h"
#include "Camera.h"
#include "Transform.h"
#include "GameObject.h"
#include "RenderComponent.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Component
{
	Camera::Camera(): posOffset(0.0f), rotOffset(0.0f), front(0.0f), WorldUp(0.0f, 1.0f, 0.0f), view(0.0f), isDirty(true), active(true), displayX(0), displayY(0), displayWidth(1), displayHeight(1)
	{

	}

	void Camera::Update(float dt)
	{

	}

	const glm::mat4& Camera::Get()
	{
		Transform* t = parent->GetComponent<Transform>();

		if (isDirty || t->IsDirty())
		{
			
			glm::vec3 pos = posOffset + t->GetPosition();
			glm::vec3 rot = rotOffset + t->GetRotation();

			//These are here so I can swap them if need be
			float yaw = -(rot.y);
			float& pitch = rot.x;

			//Pulling this math from online tutorials because the math I used in my
			//graphics class used funky rotation functions that I don't want to remake
			
			glm::vec3 right;
			glm::vec3 up;

			front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			front.y = sin(glm::radians(pitch));
			front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			front = glm::normalize(front);

			right = glm::normalize(glm::cross(front, WorldUp));
			up = glm::normalize(glm::cross(right, front));

			view = glm::lookAt(pos, pos + front, up);

			isDirty = false;
		}

		return view;
			
	}

	const glm::vec3& Camera::GetPositionOffset()
	{
		return posOffset;
	}

	const glm::vec3& Camera::GetRotationOffset()
	{
		return rotOffset;
	}

	void Camera::SetPosition(const glm::vec3& pos)
	{
		posOffset = pos;
		isDirty = true;
	}

	void Camera::SetRotation(const glm::vec3& rot)
	{
		rotOffset = rot;
		isDirty = true;
	}


	const glm::vec3& Camera::GetCameraFront()
	{
		return front;
	}

	bool Camera::IsActive()
	{
		return active;
	}

	void Camera::SetActive(bool a)
	{
		active = a;
	}

	void Camera::SetDisplayData(float x, float y, float width, float height)
	{
		displayX = x;
		displayY = y;

		displayWidth = width;
		displayHeight = height;
	}

	void Camera::GetDisplayData(float& x, float& y, float& width, float& height)
	{
		x = displayX;
		y = displayY;

		width = displayWidth;
		height = displayHeight;
	}

	void Camera::MakeIgnored(RenderComponent* c) const
	{
		c->ignore.push_back(this);
	}

	void Camera::MakeExclusive(RenderComponent* c) const
	{
		c->exclusive = this;
	}

	void Camera::AddHUD(RenderComponent* c)
	{
		hud.push_back(c);
		c->HUD = true;
	}
}