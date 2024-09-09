#include "pch.h"
#include "GameObject.h"
#include "Core.h"

namespace Object
{
	GameObject::GameObject() : components_(), eventManager_(), core_(nullptr), identifier_("Object"), isDestroyed_(false)
	{

	}

	GameObject::~GameObject()
	{

	}

	void GameObject::AddComponent(Component::BaseComponent* c)
	{
		components_.push_back(c);
		c->parent = this;
	}

	Component::BaseComponent* GameObject::GetComponent(unsigned int index)
	{
		if (index < components_.size())
			return components_[index];

		return nullptr;
	}

	Engine::Core* GameObject::GetCore() const
	{
		return core_;
	}

	void GameObject::SetCore(Engine::Core* c)
	{
		core_ = c;
	}

	void GameObject::SetIdentifier(std::string s)
	{
		identifier_ = s;
	}

	const std::string& GameObject::GetIdentifier() const
	{
		return identifier_;
	}

	bool GameObject::IsDestroyed() const
	{
		return isDestroyed_;
	}

	void GameObject::Destroy()
	{
		isDestroyed_ = true;
	}

	void GameObject::DeleteComponents()
	{
		for (Component::BaseComponent* c : components_)
		{
			//If system exists (TRANSFORM DOESN'T HAVE A SYSTEM)
			if (c->system_)
			{
				c->system_->RemoveComponent(c);
			}
			delete c;
		}
		components_.clear();
	}
}