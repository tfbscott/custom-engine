#pragma once

namespace Object
{
	class GameObject;
}
namespace Event
{
	struct EventData { virtual ~EventData() {} };

	/*
		This is defined here in Core to allow every custom physics/collision
		library to work with every custom behavior/script library
		in theory
	*/
	struct CollisionEventData : EventData
	{
		virtual ~CollisionEventData() {}

		Object::GameObject* me;

		Object::GameObject* them;
	};
}