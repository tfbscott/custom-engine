#pragma once
#include "GameStateManager.h"
#include "Transform.h"

namespace Component
{
    class Shape;
	class Texture;
}

namespace Gamestate
{


	class LevelA : public GameState
	{
		virtual void Load();

		virtual void Init();

		virtual void Update(float dt);

		virtual void Shutdown();

		virtual void UnLoad();

		void ReadLevel(const char* s);

		Object::GameObject* CreateBox(const char* name, float x, float y, float z, float sx = 1.0f, float sy = 1.0f, float sz = 1.0f, float r = 0.8f, float g = 0.8f, float b  = 0.8f);

        Component::Shape* box;
		Component::Shape* square;
		Component::Texture* texA;

		std::vector<glm::vec3> startingPos;
        std::vector<Object::GameObject*> objects;
	};
}