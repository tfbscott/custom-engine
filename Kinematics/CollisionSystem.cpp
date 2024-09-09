#include "pch.h"
#include "CollisionSystem.h"
#include "Kinematics.h"
#include "Transform.h"
#include "GameObject.h"
#include <algorithm>

#include <iostream>


namespace System
{
	void CollisionSystem::Update(float dt)
	{
		unsigned int count = components_.size();
		for (unsigned int i = 0; i < count; i++)
		{
			for (unsigned int j = i + 1; j < count; j++)
			{
				Component::Collider* a = dynamic_cast<Component::Collider*>(components_[i]);
				Component::Collider* b = dynamic_cast<Component::Collider*>(components_[j]);

				Component::Hit hit;
				bool collide = a->IntersectAABB(b, hit);

				if (collide)
				{
					//COLLISION RESPONSE IS POSSIBLY OUTDATED
					//CollisionResolutionAABB(a, b, dt);
					//CollisionResolutionAABB(b, a, dt);

					Component::Transform* at = a->GetParent()->GetComponent<Component::Transform>();
					Component::Transform* bt = b->GetParent()->GetComponent<Component::Transform>();
					//If both are static do nothing
					if (a->IsStatic() && b->IsStatic())
					{

					}
					//If a and b are both dynamic
					else if (!(a->IsStatic()) && !(b->IsStatic()))
					{
						at->SetPosition(at->GetPosition() - (hit.delta * 0.5f));
						bt->SetPosition(bt->GetPosition() + (hit.delta * 0.5f));

						Event::CollisionEventData ceda;
						ceda.me = a->GetParent();
						ceda.them = b->GetParent();
						a->GetParent()->FireEventCallback<Event::CollisionEventData>(&ceda);

						Event::CollisionEventData cedb;
						cedb.me = b->GetParent();
						cedb.them = a->GetParent();
						b->GetParent()->FireEventCallback<Event::CollisionEventData>(&cedb);

					}
					//If only a is dynamic
					else if (!(a->IsStatic()))
					{
						at->SetPosition(at->GetPosition() - (hit.delta));
						Event::CollisionEventData ceda;
						ceda.me = a->GetParent();
						ceda.them = b->GetParent();
						a->GetParent()->FireEventCallback<Event::CollisionEventData>(&ceda);
					}
					//If only b is dynamic
					else
					{
						bt->SetPosition(bt->GetPosition() + (hit.delta));
						Event::CollisionEventData cedb;
						cedb.me = b->GetParent();
						cedb.them = a->GetParent();
						b->GetParent()->FireEventCallback<Event::CollisionEventData>(&cedb);
					}
				}

			}
		}
	}


	bool CollisionSystem::PerfromRayCast(const glm::vec3& point, const glm::vec3& delta, Component::RaycastReturn& ret, const RaycastData& data)
	{
		//Set hits time to max
		ret.Hit.time = 1.0f;
		bool r = false;
		//This is slightly slow
		//Faster implementation would be to use a quad tree to trim out extraneous colliders
		for (Component::BaseComponent* b : components_)
		{
			//Using the book due to two loops
			bool ignored = false;

			//Check if we should ignore this collider
			for (Object::GameObject* o : data.ignore)
				if (o == b->GetParent())
					ignored = true;;

			if (ignored)
				continue;

			Component::Collider* c = dynamic_cast<Component::Collider*>(b);
			Component::Hit check;
			
			if (c->IntersectLine(point, delta, glm::vec3(0.0f, 0.0f, 0.0f), check))
			{
				if (check.time < ret.Hit.time)
				{
					ret.Hit = check;
					ret.GameObject = c->GetParent();
					r = true;
				}
			}
		}

		return r;
	}
}