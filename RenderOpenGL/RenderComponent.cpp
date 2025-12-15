 #include "pch.h"
#include "RenderComponent.h"
#include "Shape.h"
#include "Texture.h"

#include "ShaderProgram.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"



namespace Component
{

	RenderComponent::RenderComponent() : position(1.0f), shape(nullptr), texture(nullptr), color (1.0f, 0.5f, 0.0), vertices(nullptr), count(0), stride(0), ignore(), exclusive(nullptr), HUD(false) {}

	RenderComponent::~RenderComponent()
	{
		delete[] vertices;
	}

	void RenderComponent::Update(float dt)
	{

	}

	
	void RenderComponent::Draw(Graphics::ShaderProgram* shaderProgram)
	{
		
		//Set the transform
		unsigned int loc = glGetUniformLocation(shaderProgram->programID, "model");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(GetPosition()));

		//Set the color
		loc = glGetUniformLocation(shaderProgram->programID, "color");
		glUniform3fv(loc, 1, glm::value_ptr(GetColor()));

		loc = glGetUniformLocation(shaderProgram->programID, "useTex");
		glUniform1i(loc, texture != nullptr);

		//Bind the texture
		if (texture)
			texture->BindTexture();

		if (shape)
			shape->Draw();

		//Unbind the texture
		if (texture)
			texture->UnbindTexture();
	}

	void RenderComponent::SetShape(Shape* s)
	{
		shape = s;
	}

	void RenderComponent::SetTexture(Texture* t)
	{
		texture = t;
	}

	void RenderComponent::SetColor(const glm::vec3& c)
	{
		color = c;
	}

	

	const glm::vec3& RenderComponent::GetColor()
	{
		return color;
	}

	void RenderComponent::SetPosition(const glm::mat4& p)
	{
		position = p;
	}

	const glm::mat4& RenderComponent::GetPosition()
	{
		return position;
	}

	bool RenderComponent::ShouldCameraRender(const Camera* c)
	{
 		if (HUD)
			return false;

		if (exclusive != nullptr)
		{
			if (c == exclusive)
				return true;
			else
				return false;
		}

		for (const Camera* t : ignore)
		{
			if (c == t)
				return false;
		}

		return true;
	}
}