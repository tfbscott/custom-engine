#pragma once
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

		RenderComponent();

		~RenderComponent();

		void Update(float dt);

		//void MakeVAO();

		void Draw(Graphics::ShaderProgram*);

		void SetShape(Shape* s);

		void SetTexture(Texture* t);

		void SetColor(const glm::vec3& c);

		const glm::vec3& GetColor();

		//void SetVerticies(float* v, unsigned int c, unsigned int s);

		//unsigned int GetVAO() { return VAOID; }

		void SetPosition(const glm::mat4& p);

		 const glm::mat4& GetPosition();

		bool ShouldCameraRender(const Camera* c);

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