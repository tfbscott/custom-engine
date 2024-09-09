#include "pch.h"
#include "RenderSystem.h"
#include "Renderer.h"
#include "Core.h"
#include "GameObject.h"

namespace System
{
	void RenderSystem::Update(float)
	{
		//Alright so
		//This is a bit weird
		//This gets the renderer and casts it to a specific type
		Engine::Renderer* r = dynamic_cast<Engine::Renderer*> (GetParent()->renderer_);

		//This goes through all of the components and runs the draw code
		//Can this be divide and better organized, yes!
		//Will reorganize the current render system when adding additional features
		r->Draw(components_);
	}

	void RenderSystem::Sync()
	{
		for (Component::BaseComponent* c : components_)
		{
			Component::Transform* t = dynamic_cast<Component::Transform*> (c->GetParent()->GetComponent<Component::Transform>());
			Component::RenderComponent* r = dynamic_cast<Component::RenderComponent*>(c);

			/*
			So, this sets a value inside the render component to the transforms position
			The render component will use this value while drawing
			This reduces cross talk between components when updating
			And opens the gate for multithreading
			*/
			r->SetPosition(t->Get());
		}
	}
}