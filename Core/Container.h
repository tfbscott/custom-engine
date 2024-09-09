#pragma once
#include "dlldef.h"

//Since we are using the Hourglass method, the code here will be C style... YAY
namespace Component
{
	class BaseComponent;
}

namespace Container
{
	class _ComponentList;
	typedef _ComponentList* ComponentList;


	ComponentList ComponentListCreate();

	void ComponentListAdd(ComponentList cl, Component::BaseComponent* b);

	void ComponentListForEach(ComponentList cl, void(*func)(Component::BaseComponent*));

	void ComponentListRemove(ComponentList cl, Component::BaseComponent*);

	void ComponentListDelete(ComponentList);



}