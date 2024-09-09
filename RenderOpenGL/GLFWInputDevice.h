#pragma once
#include "InputDevice.h"
#include <GLFW/glfw3.h>

//Mouse and Keyboard device
struct GLFWKeyboardAndMouse : public InputDevice
{
public:
	GLFWKeyboardAndMouse(int i = 0) : InputDevice(InputDeviceType::KeyboardAndMouse, i) {}

	virtual void UpdateStates()
	{
		if (first)
		{
			LastMousePos = CurrentMousePos;
			first = false;
		}

		NextState[InputKey::MOUSE_X].Value = CurrentMousePos.x - LastMousePos.x;
		NextState[InputKey::MOUSE_Y].Value = CurrentMousePos.y - LastMousePos.y;

		LastMousePos = CurrentMousePos;
	}

	glm::vec2 CurrentMousePos{};
	

private:
	glm::vec2 LastMousePos{};
	bool first = true;
};

//Gamepad support
struct GLFWGamepad : public InputDevice
{
	GLFWGamepad(int i = 0) : InputDevice(InputDeviceType::Gamepad, i), state() {}
	//GLFW doesnt have callbacks for gamepads, so we need to use this
	virtual void UpdateStates()
	{
		if (glfwGetGamepadState(Index, &state))
		{
			//Update button inputs
			for (int i = 0; i < GLFW_GAMEPAD_BUTTON_LAST; i++)
				NextState[GetButton(i)].Value = state.buttons[i];

			//Update Axes
			for (int i = 0; i < GLFW_GAMEPAD_AXIS_LAST; i++)
				NextState[GetAxes(i)].Value = state.axes[i];
			
		}
	}

	//A struct that stores the gamepad state
	GLFWgamepadstate state;

	InputKey GetButton(int k)
	{
		switch (k)
		{
		case GLFW_GAMEPAD_BUTTON_A:
			return InputKey::GAMEPAD_A;
		case GLFW_GAMEPAD_BUTTON_B:
			return InputKey::GAMEPAD_B;
		case GLFW_GAMEPAD_BUTTON_X:
			return InputKey::GAMEPAD_X;
		case GLFW_GAMEPAD_BUTTON_Y:
			return InputKey::GAMEPAD_Y;
		case GLFW_GAMEPAD_BUTTON_LEFT_BUMPER:
			return InputKey::GAMEPAD_LEFT_BUMPER;
		case GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER:
			return InputKey::GAMEPAD_RIGHT_BUMPER;
		case GLFW_GAMEPAD_BUTTON_BACK:
			return InputKey::GAMEPAD_BACK;
		case GLFW_GAMEPAD_BUTTON_START:
			return InputKey::GAMEPAD_START;
		case GLFW_GAMEPAD_BUTTON_GUIDE:
			return InputKey::GAMEPAD_GUIDE;
		case GLFW_GAMEPAD_BUTTON_LEFT_THUMB:
			return InputKey::GAMEPAD_LEFT_THUMB;
		case GLFW_GAMEPAD_BUTTON_RIGHT_THUMB:
			return InputKey::GAMEPAD_RIGHT_THUMB;
		case GLFW_GAMEPAD_BUTTON_DPAD_UP:
			return InputKey::GAMEPAD_DPAD_UP;
		case GLFW_GAMEPAD_BUTTON_DPAD_RIGHT:
			return InputKey::GAMEPAD_DPAD_RIGHT;
		case GLFW_GAMEPAD_BUTTON_DPAD_DOWN:
			return InputKey::GAMEPAD_DPAD_DOWN;
		case GLFW_GAMEPAD_BUTTON_DPAD_LEFT:
			return InputKey::GAMEPAD_DPAD_LEFT;
		}
	}

	InputKey GetAxes(int a)
	{
		switch (a)
		{
		case GLFW_GAMEPAD_AXIS_LEFT_X:
			return InputKey::GAMEPAD_LEFT_STICK_X;
		case GLFW_GAMEPAD_AXIS_LEFT_Y:
			return InputKey::GAMEPAD_LEFT_STICK_Y;
		case GLFW_GAMEPAD_AXIS_RIGHT_X:
			return InputKey::GAMEPAD_RIGHT_STICK_X;
		case GLFW_GAMEPAD_AXIS_RIGHT_Y:
			return InputKey::GAMEPAD_RIGHT_STICK_Y;
		case GLFW_GAMEPAD_AXIS_LEFT_TRIGGER:
			return InputKey::GAMEPAD_LEFT_TRIGGER;
		case GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER:
			return InputKey::GAMEPAD_RIGHT_TRIGGER;
		}
	}
};