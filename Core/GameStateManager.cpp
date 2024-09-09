#include "pch.h"
#include "GameStateManager.h"
#include "Core.h"


namespace Gamestate
{
	Object::GameObject* GameState::CreateGameObject()
	{
		return factory_->CreateGameObject();
	}

	Object::GameObject* GameState::CreateGameObject(std::string id)
	{
		Object::GameObject* r = factory_->CreateGameObject();
		r->SetIdentifier(id);
		return r;
	}

}
namespace Engine
{

	GameStateManager::GameStateManager() : current(-1), next(-1), core_(nullptr), gamestates()
	{
	
	}

	GameStateManager::~GameStateManager()
	{
		for (int i = 0; i < gamestates.size(); i++)
		{
			delete gamestates[i];
			//This is just here to ease my caution
			gamestates[i] = nullptr;
		}
	}

	void GameStateManager::Update(float dt)
	{
		//If changing, perform the change
		//else update normally
		if (current != next)
		{
			//TODO: Add restarting level support!

			//Change is happening
			
			if (current >= 0)
			{
				//Shutdown the current level
				gamestates[current]->Shutdown();

				//Unload the current level
				gamestates[current]->UnLoad();
			}

			//Set the current level as the level we are changing into
			current = next;

			//Load the "current" level
			gamestates[current]->Load();

			//Init the "current" level
			gamestates[current]->Init();

		}

		//This is here to prevent game from crashing if no level is added
		if(current >= 0)
			gamestates[current]->Update(dt);
	}

	void GameStateManager::AddGamestate(Gamestate::GameState* gs)
	{
		if (gs != nullptr)
		{
			gamestates.push_back(gs);
			gs->factory_ = core_->Factory;
		}
	}

	void GameStateManager::SetParent(Core* c)
	{
		core_ = c;
	}

	void GameStateManager::SetNextGameState(int n)
	{
		next = n;
	}
}