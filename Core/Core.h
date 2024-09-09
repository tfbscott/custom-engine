#pragma once
#include "dlldef.h"

namespace Container
{
	class _ComponentList;
}

namespace Object
{
	class GameObject;
}

namespace Gamestate
{
	class GameState;
}

namespace Engine
{
	class ECSFactory;

	class GameStateManager;

	class GameObjectManager;

	class InputManager;

	class Core;
}

namespace System
{
	class BaseSystem;
}


#include <vector>
//#include "GameStateManager.h"
//#include "GameObjectManager.h"

namespace Component
{
	class CE_CORELIB_API BaseComponent
	{
	public:
		BaseComponent();

		//This function is called by a system every frame
		virtual void Update(float) = 0;

		//This function is called when the component is deleted 
		//(NOT A DESTRUCTOR DUE TO FUTURE MEMORY MANAGEMENT)
		virtual void OnDelete() {};

		Object::GameObject* GetParent() const;

	protected:
		Object::GameObject* parent;

		friend class Object::GameObject;
		friend class System::BaseSystem;
		friend class Container::_ComponentList;

	private:
		//These values are used to speed up component deletion
		unsigned int index_;
		System::BaseSystem* system_;
	};
}

namespace System
{
	class CE_CORELIB_API BaseSystem
	{
	public:

		 ~BaseSystem();

		 virtual void Initalize();

		 virtual void Update(float);

		 virtual void Exit();

		 virtual void Sync();

		 void AddComponent(Component::BaseComponent*);

		 void RemoveComponent(Component::BaseComponent*);

		 virtual bool IsCompValid(Component::BaseComponent* c) = 0;

		 void SetParent(Engine::Core* p) { parent_ = p; }

		 Engine::Core* GetParent() { return parent_; }

	protected:

		std::vector<Component::BaseComponent*> components_;

		Engine::Core* parent_;
	};

	//This class exists to allow systems to have set components
	template<class Comp>
	class AssignedSystem : public BaseSystem
	{
	public:
		bool IsCompValid(Component::BaseComponent* c)
		{
			if (dynamic_cast<Comp*>(c) != nullptr)
				return true;
			return false;
		}
	private:
	};
}

namespace Engine
{

	class CE_CORELIB_API BaseRenderer
	{
	public:
		virtual void Initalize() = 0;

		virtual void Update() = 0;

		virtual void Draw() = 0;

		virtual void Exit() = 0;

		virtual bool WindowClosing() = 0;

		virtual void UseShader() = 0;

	private:
	};


	class Core
	{
		friend class ECSFactory;
	public:
		CE_CORELIB_API Core();

		CE_CORELIB_API ~Core();

		CE_CORELIB_API void AddSystem(System::BaseSystem* s, unsigned int thread = 0);

		CE_CORELIB_API void SetRenderer(BaseRenderer* r);

		CE_CORELIB_API void SetInputManager(InputManager* i);

		CE_CORELIB_API void Init();

		CE_CORELIB_API void Run();

		CE_CORELIB_API void Exit();

		CE_CORELIB_API void AddGameState(Gamestate::GameState*);

		template<class S>
		S* GetSystem()
		{
			for (System::BaseSystem* s : systems_)
			{
				S* cast = dynamic_cast<S*>(s);
				if (cast)
					return cast;
			}
			return nullptr;
		}

		GameStateManager* StateManager;

		GameObjectManager* ObjectManager;

		ECSFactory* Factory;

		BaseRenderer* renderer_;

		InputManager* inputManager;


	private:

		void ThreadUpdate(int thread, float dt);

		std::vector<System::BaseSystem*> systems_;

		std::vector<std::vector<System::BaseSystem*>> threads_;

		


		bool isRunning_;
	};


	

}


