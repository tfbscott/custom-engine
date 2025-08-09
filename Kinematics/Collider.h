#pragma once
#include "Core.h"
#include "glm/glm.hpp"

namespace Object
{
	class GameObject;
}

namespace Component
{

	struct Hit
	{
	public:
		Hit() : pos(0, 0, 0), delta(0, 0, 0), normal(0, 0, 0), time(0) {}

		//Estimated point of intersection
		glm::vec3 pos;
		//Overlap between objects
		glm::vec3 delta;
		//Surface normal of contact point
		glm::vec3 normal;
		//How far along the collision occured
		float time;
	};


	struct Sweep
	{
	public:
		Hit hit;
		glm::vec3 pos;
		float time;
	};

	struct RaycastReturn
	{
		Hit Hit;
		Object::GameObject* GameObject;
	};

	class Collider : public BaseComponent
	{
	public:
		Collider();

		void Update(float);

		bool CheckAgainst(const Collider* other);
		/*
		other | The static box we are colliding against [WE ARE ALSO STATIC]
		hit | if intersection, the values of hit are filled in with the hit result
		*/
		bool IntersectAABB(const Collider* other, Hit& h);
		/*
		point | starting point of line
		delta | direction and length of line
		padding | value added to the radius of the check
		hit | if intersection, the values of hit are filled in with the hit result
		*/
		bool IntersectLine(const glm::vec3& point, const glm::vec3& delta, const glm::vec3& padding, Hit& h);
		/*
		other | The dynamic box we are colliding against [WE ARE STATIC]
		delta | The movement of the dynamic box
		s | The sweep struct that will be filled in if there is a collision
		*/
		bool SweepAABB(const Collider* other, const glm::vec3& delta, Sweep& s);

		void SetBoundingBox(const glm::vec3& max);
		
		const glm::vec3& GetBoundingBox() const;

		//Returns if the object should move on collisions
		bool IsStatic();

		void SetStatic(bool s);

	private:
		//For the sake of simplicity, we will be using Axis Alligned Bounding Boxes to start

		glm::vec3 half_;

		bool static_;
	};
}