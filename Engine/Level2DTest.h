#pragma once
#include "GameStateManager.h"


namespace Gamestate
{
	class Level2DTest : public GameState
	{
		virtual void Load();

		virtual void Init();

		virtual void Update(float dt);

		virtual void Shutdown();

		virtual void UnLoad();

		std::vector<Object::GameObject*> objects;
	};
}
