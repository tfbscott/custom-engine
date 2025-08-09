#pragma once
#include "Core.h"
//GLM IS HERE DUE TO WEIRD DLL STUFF AND COMPILATION THINGS
#include "glm/glm.hpp"

namespace Component
{
	class Transform : public BaseComponent
	{
	public:
		 Transform() : transform(0.0f), position_(1.0f), rotation_(0.0f), scale_(1.0f), dirty(false) {}

		 virtual void Update(float dt);

		 const glm::mat4& Get();

		//FOR DEBUG WHILE SETTING UP THE TRANSFORMATION FUNCTIONS
		 void Set(const glm::mat4& m) { transform = m; }

		 const glm::vec3& GetPosition();

		 const glm::vec3& GetRotation();

		 const glm::vec3& GetScale();

		 void SetPosition(const glm::vec3&);

		 void SetRotation(const glm::vec3&);

		 void SetScale(const glm::vec3&);

		 bool IsDirty();

	private:
		//add glm vectors here

		//this means...we need the lib...

		glm::mat4 transform;

		//These three vectors are the individual values
		glm::vec3 position_;
		glm::vec3 rotation_;
		glm::vec3 scale_;


		//The dirty flag is used in Get()
		bool dirty;
	};
}