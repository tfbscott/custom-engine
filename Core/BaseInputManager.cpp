#include "pch.h"
#include "BaseInputManager.h"

namespace Engine
{
	InputManager::~InputManager()
	{
		//Free the device memory
		for (auto d : devices)
		{
			delete d;
		}
	}

	void InputManager::RegisterActionCallback(const std::string& actionName, ActionCallback callback)
	{
		actionCallbacks[actionName].emplace_back(callback);
	}
	void InputManager::RemoveActionCallback(const std::string& actionName, std::string callbackRef)
	{
		for (auto c = actionCallbacks[actionName].begin(); c != actionCallbacks[actionName].end(); c++)
		{
			if (c->Ref == callbackRef)
			{
				//Moves the iterator along
				//pointless but looks nice
				c = actionCallbacks[actionName].erase(c);
				return;
			}
		}
	}

	void InputManager::MapInputToAction(InputKey key, const std::string& action)
	{
		//std move allows for efficient transfer of resources, by moving the data in action
		inputActionMap[key].emplace(action);
	}
	void InputManager::UnmapInputFromAction(InputKey key, const std::string& action)
	{
		inputActionMap[key].erase(action);
	}

	void InputManager::ProcessInput()
	{
		std::vector<ActionEvent> events{};
		for (InputDevice* device : devices)
		{
			//Get new state for device, if needed
			device->UpdateStates();

			for (auto& keyState : device->NextState)
			{
				if (device->CurrentState[keyState.first].Value != keyState.second.Value)
				{
					auto es = GenerateActionEvent(device->Type, device->Index, keyState.first, keyState.second.Value);
					//Generate Device Action Event

					//This puts all of the actions events in a container
					//There might be a faster way to move the events over
					for (auto& e : es)
						events.push_back(e);

					//Override current value with new state value
					device->CurrentState[keyState.first].Value = keyState.second.Value;
				}
			}
		}

		//Fire all the action events
		for (auto& event : events)
		{
			PropagateActionEvent(event);
		}
	}


	std::vector<InputManager::ActionEvent> InputManager::GenerateActionEvent(InputDeviceType Source, int deviceIndex, InputKey key, float newVal)
	{
		std::vector<ActionEvent> actionEvents{};
		auto& actions = inputActionMap[key];

		/*In the tutorial, there is a MASSIVE switch function that turns key types into Device types, and there are
		two enums for device types.
		Here I have removed one of the enums and passed the device type in from the above function
		This might cause problems in the future, but right now I don't see why not
		*/

		for (auto& action : actions)
		{
			//Generte the action event
			//MAKE THIS AN INIT LIST

			actionEvents.emplace_back(action, Source, deviceIndex, newVal);
			/*ActionEvent {
		.ActionName = action,
		.Source = Source,
		.SourceIndex = deviceIndex,
		.Value = newVal;
			}*/
		}




		return actionEvents;
	}

	void InputManager::PropagateActionEvent(ActionEvent& event)
	{
		//Get the list of action events with the action event name
		//Walks the list backwards, most recent event called first
		for (auto i = actionCallbacks[event.ActionName].rbegin(); i != actionCallbacks[event.ActionName].rend(); ++i)
		{
			auto& action = *i;

			//If the function returns true, break??
			//Not sure why this is here, or if we need it
			if (action.Func(/*event.Source,*/ event.SourceIndex, event.Value))
				break;
		}
	}


	void InputManager::RegisterDevice(InputDevice* device)
	{
		devices.push_back(device);
	}


	void InputManager::RemoveDevice(InputDeviceType type, int index)
	{
		for (auto i = devices.begin(); i != devices.end(); ++i)
		{
			if ((*i)->Type == type && (*i)->Index == index)
			{
				i = devices.erase(i);
				break;
			}

		}
	}

}