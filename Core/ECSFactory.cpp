#include "pch.h"
#include "ECSFactory.h"
#include "GameObjectManager.h"

namespace Engine
{
	void ECSFactory::SetParent(Core* c)
	{
		core_ = c;
	}

	Object::GameObject* ECSFactory::CreateGameObject()
	{
		Object::GameObject* go = new Object::GameObject;

		core_->ObjectManager->Add(go);

		go->SetCore(core_);

		return go;
	}
}