#include "pch.h"
#include "GameObjectManager.h"

namespace Engine
{

	GameObjectManager::GameObjectManager() : gameObjects_()
	{

	}

	GameObjectManager::~GameObjectManager()
	{
		//We shouldn't need this now
		for (Object::GameObject* o : gameObjects_)
		{
			o->DeleteComponents();
			delete o;
		}
	}

	void GameObjectManager::Add(Object::GameObject* o)
	{
		gameObjects_.push_back(o);
	}

	void GameObjectManager::CleanupDestroyedObjects()
	{
		for (auto i = gameObjects_.begin(); i != gameObjects_.end();)
		{
			//If the gameobject is destroyed
			if ((*i)->IsDestroyed())
			{
				Object::GameObject* go = (*i);
				//Delete the gameobjects components
				(go)->DeleteComponents();
				//Delete the object
				delete go;
				//Remove the gameobject from the list
				//This increments
				i = gameObjects_.erase(i);
			}
			else
			{
				//If we dont delete increment normally
				i++;
			}
		}
	}

	void GameObjectManager::DeleteAllObjects()
	{
		for (auto i = gameObjects_.begin(); i != gameObjects_.end(); /*deletion auto increments*/)
		{	
			Object::GameObject* go = (*i);
			//Delete the gameobjects components
			(go)->DeleteComponents();
			//Delete the object
			delete go;
			//Remove the gameobject from the list
			i = gameObjects_.erase(i);
			
		}

	}
}