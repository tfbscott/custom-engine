#include "pch.h"
#include "Renderer.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "GameObject.h"

#include "BaseInputManager.h"
#include "GLFWInputDevice.h"
#include "Camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "StreamReadWrite.h"

//#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

//SHITTY ASYNC
#include <algorithm>
#include <execution>

namespace Engine
{
	//THIS IS HERE DUE TO JOYSTICK CALLBACK
	InputManager* globalIM;

	void Renderer::Initalize()
	{
		//Initalize GLFW
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		width = 1280;
		height = 720;

		//Create the glfwWindow
		window = glfwCreateWindow(width, height, "CustomEngine", NULL, NULL);
		if (window == NULL)
		{
			glfwTerminate();
			std::cout << "Failed to create Window" << std::endl;
			return;
		}

		glfwMakeContextCurrent(window);

		//Initalize GLAD
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			//Failed to load glad
			std::cout << "Failed to load GLAD" << std::endl;
			return;
		}

		//Define the window size
		glViewport(0, 0, 800, 600);

		//Sets a function (lambda) that is called whenever the window size is changed
		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
			});

		/*

		vertices = new float[] {
			-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.0f, 0.5f, 0.0f
		};
		count = 3;
		stride = 3;

		//Create a vertex Buffer Objectr
		glGenBuffers(1, &VBO);
		//Create the Vertex Array Object
		glGenVertexArrays(1, &VAO);
		//Bind the VAO, so the data is stored in it
		glBindVertexArray(VAO);
		//Bind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//Configure the VBO
		//first param is type of buffer
		//second is size of data
		//third is the data
		//forth is how we want th graphics card to manage the data

		*/

		/*
		GL_STREAM_DRAW: data set once and used a few times
		GL_STATIC_DRAW: data set once and used many times
		GL_DYNAMIC_DRAW: data is changed a lot and used many times
		*/
		//glBufferData(GL_ARRAY_BUFFER, /*sizeof(vertices)*/count * stride*sizeof(float), vertices, GL_STATIC_DRAW);
		
		//Tell OpenGL how to interpret the vertex gata
		/*
		First parameter is which vertex attribute we want to configure, vertex shader layout = 0, so 0
		Second is size of the vertex attribute (vec3)
		Third is type of data
		Forth is if we want the data to be normalized
		Fith is stride, or space between consecutive vertex attributes
		Final is offset of where the position starts (posistion data is at front of array so value is just 0)
		*/
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0);
		//Used when we use the indicies buffer
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//Create the vertex and fragment shaders
		/*
		You can create and compile shaders at runtime using 
		glCreateShader, glShaderSource, and glCompile Shader
		*/

		//Tell OpenGL how to interpret the vertex data

		

		/*const char* vSource = Tools::ReadFile("shader.vert");
		//THESE SHOULD BE READ IN FROM EXTERNAL FILES FOR EASE OF ACCESS LATER
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vSource, NULL);
		glCompileShader(vertexShader);

		const char* fSource = Tools::ReadFile("shader.frag");
		//THESE SHOULD BE READ IN FROM EXTERNAL FILES FOR EASE OF ACCESS LATER
		unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fSource, NULL);
		glCompileShader(fragShader);

		oldSP = glCreateProgram();
		glAttachShader(oldSP, vertexShader);
		glAttachShader(oldSP, fragShader);
		glLinkProgram(oldSP);

		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);*/

		shaderProgram = new Graphics::ShaderProgram();
		

		shaderProgram->CompileShaderFromFile("shader.vert", GL_VERTEX_SHADER);
		shaderProgram->CompileShaderFromFile("shader.frag", GL_FRAGMENT_SHADER);

		shaderProgram->LinkProgram();


		
		//Enable Wireframe mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//Enable Depth Test
		glEnable(GL_DEPTH_TEST);


		m4Identity = glm::identity<glm::mat4>();
	}

	void Renderer::Update()
	{
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProcessInput();
	}

	void Renderer::Draw()
	{
		//Not using this, plan to remove
	}

	//THIS IS THE FUNCTION BEING USED
	void Renderer::Draw(std::vector<Component::BaseComponent*>& c)
	{
		//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

		//glm::vec3 cameraUp = glm::cross(cameraDirection, glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection)));

		glfwGetFramebufferSize(window, &width, &height);


		//The World View Matrix
		//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		//The World Projection Matrix
		//projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < cameras_.size(); i++)
		{
			
			


			float xP = 0, yP = 0, widthP = 1, heightP = 1;

			cameras_[i]->GetDisplayData(xP, yP, widthP, heightP);

			int viewportX = int(width * xP), viewportY = int(height * yP), viewportWidth = int(width * widthP), viewportHeight = int(height * heightP);

			glViewport(viewportX, viewportY, viewportWidth, viewportHeight);

			glEnable(GL_DEPTH_TEST);

			projection = glm::perspective(glm::radians(45.0f), ((float)width * widthP) / ((float)height * heightP), 0.1f, 100.0f);
			//Drawing the object
			orthoProjection = glm::ortho(-static_cast<float>(width * widthP), static_cast<float>(width * widthP), -static_cast<float>(height * heightP), static_cast<float>(height * heightP), -0.1f, 100.0f);
			

			//glUseProgram(oldSP);
			shaderProgram->UseProgram();


			//Set the World View
			unsigned int loc, viewLoc, projLoc;

			viewLoc = glGetUniformLocation(shaderProgram->programID, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(cameras_[i]->Get()));
			projLoc = glGetUniformLocation(shaderProgram->programID, "projection");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			//Draw 3D objects
			for (Component::BaseComponent* b : c)
			//std::for_each()
			{

				//INDEX 0 SHOULD BE A TRANSFORM
				//Component::Transform* t = dynamic_cast<Component::Transform*> (b->GetParent()->GetComponent(0));
				Component::RenderComponent* r = dynamic_cast<Component::RenderComponent*>(b);

				//glBindVertexArray(r->GetVAO());

				//Check if we should draw said object
				//If we shouldn't, go to next object
				if (r->ShouldCameraRender(cameras_[i]) == false)
					continue;



				//First param is primative we want to draw (triangles)
				//Second is starting index in the vertex array
				//Third is number of verticies to go through
				//glDrawArrays(GL_TRIANGLES, 0, 3);

				//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

				r->Draw(shaderProgram);

				/*
				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, count);
				//Unbind the array
				glBindVertexArray(0);
				*/
			}
			//DRAW HUD
			glDisable(GL_DEPTH_TEST);
			glClear(GL_DEPTH_BUFFER_BIT);
			//Switch to 2D projection
			//save matrix state?
			//reset?
			//set 2d projection matrix
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(orthoProjection));
			//switch to modelview matrix
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m4Identity));
			//save state
			//reset
			for (Component::RenderComponent* r : cameras_[i]->hud)
			{
				//glEnable(GL_DEPTH_TEST);

				//Draw HUD

				 //Set the transform
				 loc = glGetUniformLocation(shaderProgram->programID, "model");
				 glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(r->GetPosition()));

				 //Set the color
				 loc = glGetUniformLocation(shaderProgram->programID, "color");
				 glUniform3fv(loc, 1, &(r->GetColor())[0]);

				 

				 r->Draw(shaderProgram);
			}
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	void Renderer::Exit()
	{
		delete shaderProgram;

		glfwTerminate();
	}

	bool Renderer::WindowClosing()
	{
		return glfwWindowShouldClose(window);
	}


	void Renderer::AddComponent(Component::BaseComponent* b)
	{
		components_.push_back(b);
	}


	void Renderer::ProcessInput()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
		
	}


	void Renderer::UseShader()
	{
		 shaderProgram->UseProgram(); 
	}

	void Renderer::GetWindowSize(int& w, int& h)
	{
		w = width;
		h = height;
	}

	void Renderer::SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	void Renderer::SetKeyCallback(GLFWkeyfun callback)
	{
		glfwSetKeyCallback(window, callback);
	}

	void Renderer::SetMouseCallback(GLFWcursorposfun callback)
	{
		glfwSetCursorPosCallback(window, callback);
	}

	void Renderer::SetMouseButtonCallback(GLFWmousebuttonfun callback)
	{
		glfwSetMouseButtonCallback(window, callback);
	}

	void Renderer::SetWindowUserPointer(void* p)
	{
		glfwSetWindowUserPointer(window, p);
	}

	void Renderer::SetJoystickUserPointer(void* p)
	{
		//For every possible joystick, set the user pointer
		for (int i = 0; i <= GLFW_JOYSTICK_LAST; i++)
			glfwSetJoystickUserPointer(i, p);
	}

	void Renderer::CreateInputDevices(Engine::InputManager* im)
	{
		globalIM = im;

		SetWindowUserPointer(im);

		SetJoystickUserPointer(im);

		globalIM = im;

		GLFWKeyboardAndMouse* Keyboard = new GLFWKeyboardAndMouse;
		Keyboard->Type = InputDeviceType::KeyboardAndMouse;
		Keyboard->Index = 0;

		im->RegisterDevice(Keyboard);

		SetKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
			Engine::InputManager* manager = static_cast<Engine::InputManager*>( glfwGetWindowUserPointer(window));

			InputDevice* Keyboard = manager->GetDeviceByIndex(0);

			switch (key)
			{
			case GLFW_KEY_W:
				Keyboard->NextState[InputKey::KEY_W].Value = (float)action;
				break;
			case GLFW_KEY_A:
				Keyboard->NextState[InputKey::KEY_A].Value = (float)action;
				break;
			case GLFW_KEY_S:
				Keyboard->NextState[InputKey::KEY_S].Value = (float)action;
				break;
			case GLFW_KEY_D:
				Keyboard->NextState[InputKey::KEY_D].Value = (float)action;
				break;
			case GLFW_KEY_SPACE:
				Keyboard->NextState[InputKey::KEY_SPACE].Value = (float)action;
				break;
			}
			});

		SetMouseCallback([](GLFWwindow* window, double xpos, double ypos) {
			Engine::InputManager* manager = static_cast<Engine::InputManager*>(glfwGetWindowUserPointer(window));
			GLFWKeyboardAndMouse* Keyboard = dynamic_cast<GLFWKeyboardAndMouse*>(manager->GetDeviceByIndex(0));

			Keyboard->CurrentMousePos.x = (float)xpos;
			Keyboard->CurrentMousePos.y = (float)ypos;
			
			/*static bool first = true;
			static float lastx = 0;
			static float lasty = 0;



			if (first)
			{
				lastx = xpos;
				lasty = ypos;
				first = false;
			}

			Keyboard->NextState[InputKey::MOUSE_POS_X].Value = xpos - lastx;
			Keyboard->NextState[InputKey::MOUSE_POS_Y].Value = ypos - lasty;

			lastx = xpos;
			lasty = ypos;*/
			});

		SetMouseButtonCallback([](GLFWwindow* window, int button, int action, int mods) {
			Engine::InputManager* manager = static_cast<Engine::InputManager*>(glfwGetWindowUserPointer(window));
			InputDevice* Keyboard = manager->GetDeviceByIndex(0);

			InputKey convert;

			switch (button)
			{
			case GLFW_MOUSE_BUTTON_1:
				convert = InputKey::MOUSE_1;
				break;
			case GLFW_MOUSE_BUTTON_2:
				convert = InputKey::MOUSE_2;
				break;
			case GLFW_MOUSE_BUTTON_3:
				convert = InputKey::MOUSE_3;
				break;
			case GLFW_MOUSE_BUTTON_4:
				convert = InputKey::MOUSE_4;
				break;
			case GLFW_MOUSE_BUTTON_5:
				convert = InputKey::MOUSE_5;
				break;
			case GLFW_MOUSE_BUTTON_6:
				convert = InputKey::MOUSE_6;
				break;
			case GLFW_MOUSE_BUTTON_7:
				convert = InputKey::MOUSE_7;
				break;
			case GLFW_MOUSE_BUTTON_8:
				convert = InputKey::MOUSE_8;
				break;
			default:
				break;
			}

			Keyboard->NextState[convert].Value = float(action);

			});

		//JOYSTICK SUPPORT
		//First of all, we need a callback for when a joystick is connected/disconnected
		glfwSetJoystickCallback([](int id, int event) {
			Engine::InputManager* manager = globalIM;
			//If the joystick is an actual gamepad
			if (event == GLFW_CONNECTED)
			{
				if (glfwJoystickIsGamepad(id))
				{
					InputDevice* Gamepad = new GLFWGamepad;
					Gamepad->Type = InputDeviceType::Gamepad;
					Gamepad->Index = id;
					//Joystick of said id is attatched
					manager->RegisterDevice(Gamepad);
				}
			}
			else if (event == GLFW_DISCONNECTED)
			{
				//Joystick of said id is removed
				manager->RemoveDevice(InputDeviceType::Gamepad, id);
			}
			
		});

		//We need to check if gamepads are already plugged in
		for (int i = 0; i <= GLFW_JOYSTICK_LAST; i++)
		{
			//If joystick exists
			if (glfwJoystickPresent(i) && glfwJoystickIsGamepad(i))
			{
				InputDevice* Gamepad = new GLFWGamepad;
				Gamepad->Type = InputDeviceType::Gamepad;
				Gamepad->Index = i;
				//Joystick of said id is attatched
				im->RegisterDevice(Gamepad);
			}
		}
		
	}

	void Renderer::CaptureCursor()
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Renderer::ClearCameras()
	{
		cameras_.clear();
	}

	void Renderer::AddCamera(Component::Camera* c)
	{
		cameras_.push_back(c);
	}
}