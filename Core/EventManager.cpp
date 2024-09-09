#include "pch.h"
#include "EventManager.h"

namespace Event
{
	EventManager::EventManager() : subscribers()
	{

	}

	EventManager::~EventManager()
	{
		for (auto a : subscribers)
		{
			if (a.second)
			{
				for (EventCallbackBase* b : *(a.second))
				{
					delete b;
				}
				delete a.second;
			}
		}
	}
}