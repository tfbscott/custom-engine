#pragma once
#include "Core.h"
#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"
#include <list>

namespace Engine
{
	class Renderer;
}

namespace Component
{
	class RenderComponent;

	class Camera : public BaseComponent
	{
	public:
		friend class Engine::Renderer;

		Camera();

		void Update(float dt);

		const glm::mat4& Get();

		const glm::vec3& GetPositionOffset();

		const glm::vec3& GetRotationOffset();

		void SetPosition(const glm::vec3&);

		void SetRotation(const glm::vec3&);

		const glm::vec3& GetCameraFront();

		bool IsActive();

		void SetActive(bool);

		//THESE VALUES ARE PERCENTAGES, 0 to 1
		void SetDisplayData(float x, float y, float width, float height);

		void GetDisplayData(float& x, float& y, float& width, float& height);

		void MakeIgnored(RenderComponent* c) const;

		void MakeExclusive(RenderComponent* c) const;

		void AddHUD(RenderComponent* c);

	private:
		
		glm::vec3 posOffset;
		glm::vec3 rotOffset;

		glm::vec3 front;
		glm::vec3 WorldUp;

		glm::mat4 view;

		bool isDirty;

		bool active;

		float displayX;
		
		float displayY;
		
		float displayWidth;
		
		float displayHeight;

		std::list<RenderComponent*> hud;

	};
}