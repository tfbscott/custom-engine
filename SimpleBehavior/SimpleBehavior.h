#pragma once
#include "Core.h"
#include "GameObject.h"
#include "BaseInputManager.h"
#include <functional>

namespace System
{
	class SimpleBehaviorSystem;
}

namespace Component
{
	class SimpleBehavior : public BaseComponent
	{
		friend class System::SimpleBehaviorSystem;
	public:
		//Simple default constructor
		SimpleBehavior();
		/*
			pure virtual start function
			to be filled in by the complete events
		*/
		virtual void OnStart() = 0;
		/*
			pure virtual update function
			to be filled in by the complete events
		*/
		virtual void OnUpdate(float) = 0;

		/*
			Function that is called on Behaviors deleteion
			Is here to handle deletion of subscribed events;
		*/
		virtual void OnDelete();
		/*
			virtual OnCollision function
			Complete events can fill this in, or leave it blank
		*/
		virtual void OnCollision(Object::GameObject* me, Object::GameObject* them) {}
		/*
			A wrapper for the OnCollision function
			User doesnt need to worry about the EventDDta class
		*/
		void CollisionEventFunction(Event::CollisionEventData* e);
		/*
			A wrapper for subscribing to the collion event
		*/
		void SubCollisionEventCallback();
		/*
			Returns the state of the key pressed
			Key code and return value depend on the current input manager
		*/
		template <class T>
		void BindKeyAction(std::string action, T* i, bool(T::* callbackFunc)(int, float))
		{
			Engine::InputManager::ActionCallback callback;
			callback.Ref = behID + '_' + action;
			callback.Func = std::bind(callbackFunc, i, std::placeholders::_1, std::placeholders::_2);

			keyCallbacks.push_back(action);
			
			GetParent()->GetCore()->inputManager->RegisterActionCallback(action, callback);
		}

		/*
			The update function the system calls, handles OnStart and OnUpdate

			DISABLED DUE TO PARALLEL BUGS
		*/
		void Update(float);
	private:
		//A value used to assigned behavior id, which is used in removing key callbacks
		static unsigned int totalBehaviorCount;

		bool first_;

		std::list<std::string> keyCallbacks;

		std::string behID;
	};
}