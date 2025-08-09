#pragma once
#include "InputKey.h"
#include "InputDevice.h"
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include <functional>

//NOTES HERE FOR INPUT MANAGER 2.0
//Using tutorial https://youtu.be/Ms9metbS2lU
/*
	Needs
	-List of actions and associated inputs
	-List of callbacks and associated actions
	-Function to process action events
	-Function to process inputs
	-Registered Devices List/Map
	--Type
	--Index (for controllers)
	--State Callback Function (sends info to input manager)
	--Device State

	Action Event
	-Action Name
	-Value
	-Event Type (pressed/released)

	During Update
	-Process Input at top of update
	--Query registered devices
	--Compare new states to old states
	--Queue action events
	--Fire Action events

*/


namespace Engine
{

	using ActionCallbackFunc = std::function<bool(/*InputDeviceType,*/ int, float)>;
	

	class InputManager
	{
	public:
		struct ActionCallback {
			//Use hashstring to speed up
			std::string Ref;
			ActionCallbackFunc Func;
		};

		~InputManager();

		void RegisterActionCallback(const std::string& actionName, ActionCallback callback);
		void RemoveActionCallback(const std::string&, std::string callbackRef);

		void MapInputToAction(InputKey key, const std::string& action);
		void UnmapInputFromAction(InputKey key, const std::string& action);

		void RegisterDevice(InputDevice* device);
		void RemoveDevice(InputDeviceType type, int index);

		InputDevice* GetDeviceByIndex(int i) { return devices[i]; }

		//This function will get new devices states and compare them to old states
		void ProcessInput();
	private:

		struct ActionEvent
		{
			ActionEvent(std::string a, InputDeviceType s, int i, float v) : ActionName(a), Source(s), SourceIndex(i), Value(v){}

			std::string ActionName;
			InputDeviceType Source;
			int SourceIndex;
			float Value;
		};

		

		std::vector<ActionEvent> GenerateActionEvent(InputDeviceType Source, int deviceIndex, InputKey key, float newVal);

		void PropagateActionEvent(ActionEvent& event);

		std::unordered_map<InputKey, std::unordered_set<std::string>> inputActionMap;
		std::unordered_map<std::string, std::list<ActionCallback>> actionCallbacks;

		std::vector<InputDevice*> devices;
	};

}