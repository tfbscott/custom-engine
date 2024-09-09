#pragma once
#include "dlldef.h"
#include "Core.h"
#include "Transform.h"
#include "glm/glm.hpp"

#include <list>

namespace Graphics
{
	class ShaderProgram;
}

namespace Component
{
	class Shape;

	class Texture;

	class Camera;

	class RenderComponent : public BaseComponent
	{
	public:

		CE_RENDEROGL_API RenderComponent();

		CE_RENDEROGL_API ~RenderComponent();

		CE_RENDEROGL_API void Update(float dt);

		//void MakeVAO();

		CE_RENDEROGL_API void Draw(Graphics::ShaderProgram*);

		CE_RENDEROGL_API void SetShape(Shape* s);

		CE_RENDEROGL_API void SetTexture(Texture* t);

		CE_RENDEROGL_API void SetColor(const glm::vec3& c);

		CE_RENDEROGL_API const glm::vec3& GetColor();

		//void SetVerticies(float* v, unsigned int c, unsigned int s);

		//unsigned int GetVAO() { return VAOID; }

		CE_RENDEROGL_API  void SetPosition(const glm::mat4& p);

		CE_RENDEROGL_API const glm::mat4& GetPosition();

		CE_RENDEROGL_API bool ShouldCameraRender(const Camera* c);

	private:
		
		friend class Camera;

		glm::mat4 position;

		Shape* shape;

		Texture* texture;

		glm::vec3 color;

		//unsigned int VAOID;

		//unsigned int VBOID;

		float* vertices;

		unsigned int count;

		unsigned int stride;
		//Not drawn on these cameras
		std::list<const Camera*> ignore;
		//ONLY DRAWN BY THIS SINGLE CAMERA
		const Camera* exclusive;

		bool HUD;
	};
}