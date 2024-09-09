#pragma once
#include "dlldef.h"
#include <vector>
#include "Core.h"
#include "GameObject.h"
#include "ECSFactory.h"
//Not DLL safe, change
#include <string>

/*namespace Object
{
	class GameObject;
}

namespace Component
{
	class BaseComponent;
}*/

namespace Engine
{
	class Core;
	class ECSFactory;

}

namespace Gamestate
{
	class CE_CORELIB_API GameState
	{
		friend class Engine::GameStateManager;
	public:

		//Load and unload are not pure virtual by design

		virtual void Load() {};

		virtual void Init() = 0;

		virtual void Update(float dt) = 0;

		virtual void Shutdown() = 0;

		virtual void UnLoad() {};

		Object::GameObject* CreateGameObject();

		Object::GameObject* CreateGameObject(std::string id);

		template<class C>
		C* CreateComponent(Object::GameObject* g)
		{
			C* c = factory_->CreateComponent<C>();
			g->AddComponent(c);
			return c;
		}

	private:

		Engine::ECSFactory* factory_;
	};
}

namespace Engine{

	class GameStateManager
	{
	public:

		GameStateManager();

		~GameStateManager();

		void Update(float dt);

		CE_CORELIB_API void AddGamestate(Gamestate::GameState*);

		void SetParent(Core*);

		CE_CORELIB_API void SetNextGameState(int);

		CE_CORELIB_API int GetCurrentState() { return current; }

	private:
		int current;
		int next;

		Core* core_;

		std::vector<Gamestate::GameState*> gamestates;


	};
}