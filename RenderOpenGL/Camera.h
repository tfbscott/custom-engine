#pragma once
#include "dlldef.h"
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

		CE_RENDEROGL_API Camera();

		CE_RENDEROGL_API void Update(float dt);

		CE_RENDEROGL_API const glm::mat4& Get();

		CE_RENDEROGL_API const glm::vec3& GetPositionOffset();

		CE_RENDEROGL_API const glm::vec3& GetRotationOffset();

		CE_RENDEROGL_API void SetPosition(const glm::vec3&);

		CE_RENDEROGL_API void SetRotation(const glm::vec3&);

		CE_RENDEROGL_API const glm::vec3& GetCameraFront();

		CE_RENDEROGL_API bool IsActive();

		CE_RENDEROGL_API void SetActive(bool);

		//THESE VALUES ARE PERCENTAGES, 0 to 1
		CE_RENDEROGL_API void SetDisplayData(float x, float y, float width, float height);

		CE_RENDEROGL_API void GetDisplayData(float& x, float& y, float& width, float& height);

		CE_RENDEROGL_API void MakeIgnored(RenderComponent* c) const;

		CE_RENDEROGL_API void MakeExclusive(RenderComponent* c) const;

		CE_RENDEROGL_API void AddHUD(RenderComponent* c);

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