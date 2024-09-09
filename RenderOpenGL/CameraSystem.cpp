#include "pch.h"
#include "CameraSystem.h"
#include "Renderer.h"

namespace System
{
	void CameraSystem::Update(float dt)
	{
		Engine::Renderer* r = dynamic_cast<Engine::Renderer*>(GetParent()->renderer_);

		//Remove the previous active cameras
		r->ClearCameras();

		for (Component::BaseComponent* comp : components_)
		{
			Component::Camera* c = dynamic_cast<Component::Camera*>(comp);
			if (c->IsActive())
			{
				//Add the camera to the render list
				r->AddCamera(c);
			}
		}
	}
}