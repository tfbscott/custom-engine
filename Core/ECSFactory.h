#pragma once
#include "Core.h"
#include "GameObject.h"

namespace Engine
{
	class ECSFactory
	{
	public:

		void SetParent(Core*);

		Object::GameObject* CreateGameObject();

		template<class C>
		C* CreateComponent()
		{
			C* c = new C;

			Component::BaseComponent* bc = dynamic_cast<Component::BaseComponent*>(c);

			for (System::BaseSystem* s : core_->systems_)
			{
				if (s->IsCompValid(bc))
					s->AddComponent(bc);
			}

			return c;
		}

		template<class C>
		C* CreateComponent(Object::GameObject* g)
		{
			C* c = new C;

			Component::BaseComponent* bc = dynamic_cast<Component::BaseComponent*>(c);

			for (System::BaseSystem* s : core_->systems_)
			{
				if (s->IsCompValid(bc))
					s->AddComponent(bc);
			}

			g->AddComponent(c);

			return c;
		}

	private:
		Core* core_;

	};
}
