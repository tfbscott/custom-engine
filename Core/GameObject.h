#pragma once
#include "EventManager.h"
//NOT DLL SAFE, REPLACE LATER
#include <vector>
#include <map>
#include <typeindex>
#include <string>

//Prototype to reduce header conflicts

namespace Engine
{
	class Core;
}

namespace Component
{
	class BaseComponent;
}

namespace Object
{
	class GameObject
	{
	public:

		GameObject();

		~GameObject();

		void AddComponent(Component::BaseComponent*);

		//CURRENTLY INDEXED, ADD TEMPLATED GET LATER
		Component::BaseComponent* GetComponent(unsigned int index);

		//THIS IS INEFFICIENT AND SLOW
		//NEED A WAY TO SPEED UP
		//PLAN IS TO USE A MAP
		template<class Comp>
		Comp* GetComponent()
		{
			for (Component::BaseComponent* c : components_)
			{
				if (dynamic_cast<Comp*>(c) != nullptr)
					return dynamic_cast<Comp*>(c);
			}
			return nullptr;
		}

		Engine::Core* GetCore() const;
		//Possibly make setcore private, so user doesn't mess with it
		//Currently throws link errors on purpose
		void SetCore(Engine::Core* c);

		template<class E, class T>
		void AddEventCallback(T* i, void (T::* callbackFunc)(E*))
		{
			eventManager_.SetCallback<E, T>(i, callbackFunc);
		}

		template<class E>
		void FireEventCallback(Event::EventData* e)
		{
			eventManager_.FireCallback<E>(e);
		}

		void SetIdentifier(std::string s);

		const std::string& GetIdentifier() const;

		bool IsDestroyed() const;

		void Destroy();

		void DeleteComponents();

	private:
		std::vector<Component::BaseComponent*> components_;
		//MAP OF VECTORS
		// ALLOWS FOR MULTIPLE COMPONENTS OF THE SAME TYPE
		//std::map<std::type_index, std::vector<Component::BaseComponent*>> components_;

		//Each game object has their own event manager
		//This allows for certain events to be broadcast and subscribed to localy
		Event::EventManager eventManager_;

		Engine::Core* core_;

		std::string identifier_;

		bool isDestroyed_;
	};
}
