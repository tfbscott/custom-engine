#pragma once

#include "dlldef.h"
#include "Core.h"
#include "InputDevice.h"
#include "glm/glm.hpp"



//Prototype for class below
struct GLFWwindow;
namespace Graphics { class ShaderProgram; }

typedef void(*GLFWkeyfun) (GLFWwindow* window, int key, int scancode, int action, int mods);
typedef void(*GLFWcursorposfun) (GLFWwindow* window, double xpos, double ypos);
typedef void(*GLFWmousebuttonfun) (GLFWwindow* window, int button, int action, int mods);

namespace Component
{
	class Camera;
}

namespace Engine {

	class InputManager;

	class CE_RENDEROGL_API Renderer : public BaseRenderer
	{
	public:
		virtual void Initalize();

		virtual void Update();

		virtual void Draw();
		
		void Draw(std::vector<Component::BaseComponent*>& c);

		virtual void Exit();

		virtual bool WindowClosing();

		void ProcessInput();

        void AddComponent(Component::BaseComponent*);

		void UseShader();

		void GetWindowSize(int& w, int& h);
	
		void SetViewport(int, int, int, int);

		void SetKeyCallback(GLFWkeyfun);

		void SetMouseCallback(GLFWcursorposfun);

		void SetMouseButtonCallback(GLFWmousebuttonfun);

		void CreateInputDevices(Engine::InputManager*);

		void SetWindowUserPointer(void* p);

		void SetJoystickUserPointer(void* p);

		void CaptureCursor();

		void ClearCameras();

		void AddCamera(Component::Camera* c);

		glm::mat4 projection;
		glm::mat4 orthoProjection;

		glm::mat4 m4Identity;
		//glm::mat4 view;

	private:
		GLFWwindow* window;

		int height;

		int width;
        //glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

        //glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

        //glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

        float deltaTime = 0.0f;

        float lastFrame = 0.0f;

		friend class InputManager;


		//opengls shader program
		Graphics::ShaderProgram* shaderProgram;
		unsigned int oldSP;

        std::vector<Component::BaseComponent*> components_;

		std::vector<Component::Camera*> cameras_;

		//testing
		float* vertices;
		unsigned int count;
		unsigned int stride;

		unsigned int VAO;
		unsigned int VBO;

	
	};

}