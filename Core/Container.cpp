#include "pch.h"
#include "Core.h"
#include "Container.h"
#include <list>
#include <vector>

//Using the hourglass technique to fix std lib errors!

namespace Container
{
	template<class C>
	struct _ListWrapper
	{
		_ListWrapper() : list() {}

		void Add(Component::BaseComponent* c)
		{
			list.push_back(c);
		}

		void ForEach(void (*func)(Component::BaseComponent*))
		{
			for (auto i = list.begin(); i != list.end(); i++)
			{
				func(*i);
			}
		}

		void DeleteAll()
		{
			for (auto i = list.begin(); i != list.end(); i++)
			{
				delete* i;
			}
		}

		std::vector<C*> list;
	};


	struct _ComponentList : public _ListWrapper<Component::BaseComponent>
	{
		void Remove(Component::BaseComponent* b)
		{
			//The index value should be the location of the component

		//Replace the location of b with the last component
			list[b->index_] = list[list.size() - 1];
			//Update the index value
			list[b->index_]->index_ = b->index_;
			//Calles the components delete function
			b->OnDelete();
			//Remove the last component from the list
			list.pop_back();
		}
	};

	class _SystemList
	{

	};


	ComponentList ComponentListCreate()
	{
		return new _ComponentList;
	}

	void ComponentListAdd(ComponentList cl, Component::BaseComponent* b)
	{
		cl->Add(b);
	}

	void ComponentListForEach(ComponentList cl, void(*func)(Component::BaseComponent*))
	{
		cl->ForEach(func);
	}

	void ComponentListRemove(ComponentList cl, Component::BaseComponent* b)
	{
		cl->Remove(b);
	}

	void ComponentListDelete(ComponentList cl)
	{
		delete cl;
	}

}