#pragma once
#include "Events.h"
#include <list>
#include <unordered_map>
#include <typeindex>

namespace Event
{

	class EventCallbackBase
	{
	public:
		EventCallbackBase() {}

		void exec(EventData* e) { call(e); }

		virtual void call(EventData*) = 0;
	};

	template<class E, class C>
	class EventCallbackHandler : public EventCallbackBase
	{
	public:
		typedef void (C::* Callback)(E*);

		EventCallbackHandler(C* i, Callback c) :EventCallbackBase(), instance_(i), func_(c) {}

		void call(EventData* a)
		{
			(instance_->*func_)(dynamic_cast<E*>(a));
		}

	private:
		C* instance_;

		Callback func_;
	};

	typedef std::list<EventCallbackBase*> CallbackList;
	class EventManager
	{
	public:
		EventManager();

		~EventManager();

		template<class E, class T>
		void SetCallback(T* i, void (T::* callbackFunc)(E*))
		{
			CallbackList* handlers = subscribers[std::type_index(typeid(E))];

			if (handlers == nullptr)
			{
				handlers = new CallbackList;
				subscribers[std::type_index(typeid(E))] = handlers;
			}

			handlers->push_back(new EventCallbackHandler<E, T>(i, callbackFunc));
		}

		template<class E>
		void FireCallback(EventData* e)
		{
			CallbackList* handlers = subscribers[std::type_index(typeid(E))];

			if (handlers == nullptr)
				return;
			for (EventCallbackBase* handler : *handlers)
			{
				if (handler != nullptr)
					handler->exec(e);
			}
		}

	protected:

		std::unordered_map<std::type_index, CallbackList*> subscribers;
	};
}
