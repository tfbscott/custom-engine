#pragma once
#include "InputKey.h"
#include <functional>
#include <unordered_map>

enum class InputDeviceType
{
	KeyboardAndMouse,
	Gamepad,
	Unknown
};

struct InputDeviceState
{
	float Value = 0.0f;
};

//This function is called to get the state of the device by index
//using InputDeviceStateCallbackFunc = std::function<const std::unordered_map<InputKey, InputDeviceState>&(int)>;

struct InputDevice
{
	InputDevice(InputDeviceType t = InputDeviceType::Unknown, int i = 0) : Type(t), Index(i), CurrentState(), NextState(){}

	InputDeviceType Type;
	int Index;
	std::unordered_map < InputKey, InputDeviceState> CurrentState;
	std::unordered_map < InputKey, InputDeviceState> NextState;
	//UpdateState is used yo get values for input devices without callbacks
	virtual void UpdateStates() {};
};

