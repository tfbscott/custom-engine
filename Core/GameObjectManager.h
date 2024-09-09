#pragma once
#include "GameObject.h"
#include <list>

namespace Engine
{
	class GameObjectManager
	{
	public:
		GameObjectManager();

		~GameObjectManager();

		void Add(Object::GameObject*);

		void CleanupDestroyedObjects();

		void DeleteAllObjects();
		
	private:
		std::list<Object::GameObject*> gameObjects_;


	};
}