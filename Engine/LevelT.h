#pragma once
#include "GameStateManager.h"

namespace Component
{
    class Shape;
}

namespace Gamestate
{


	class LevelT : public GameState
	{
		virtual void Load();

		virtual void Init();

		virtual void Update(float dt);

		virtual void Shutdown();

		virtual void UnLoad();

		

        Component::Shape* box;

        std::vector<Object::GameObject*> objects;
	};
}