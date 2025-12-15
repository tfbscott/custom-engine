#include "pch.h"
#include "Collider.h"
#include "Transform.h"
#include "Kinematics.h"
#include "GameObject.h"

#include <algorithm>


//Writing a few helper functions because I cant find Clamp in algo

template<class T>
const T& clamp(const T& v, const T& lo, const T& hi)
{
	return std::max(lo, std::min(v, hi));
}

namespace Component
{
	Collider::Collider() : half_(0.5f), static_(false)
	{

	}

	void Collider::Update(float dt)
	{

	}

	bool Collider::IntersectAABB(const Collider* other, Hit& hit)
	{
		Transform* ta = GetParent()->GetComponent<Transform>();
		Transform* tb = other->parent->GetComponent<Transform>();

		glm::vec3 d = tb->GetPosition() - ta->GetPosition();

		float px = (other->half_.x + half_.x) - abs(d.x);
		if (px <= 0)
			return false;

		float py = (other->half_.y + half_.y) - abs(d.y);
		if (py <= 0)
			return false;

		float pz = (other->half_.z + half_.z) - abs(d.z);
		if (pz <= 0)
			return false;

		//If we get here there was a collision
		//If x collides first
		if (px < py && px < pz)
		{
			//sx is the sign of d.x
			float sx = d.x < 0.0f ? -1.0f : 1.0f;
			
			hit.delta.x = px * sx;
			hit.normal.x = sx;
			hit.pos.x = ta->GetPosition().x + (half_.x * sx);
			hit.pos.y = tb->GetPosition().y;
			hit.pos.z = tb->GetPosition().z;
		}
		//If y collides first
		else if (py < px && py < pz)
		{
			float sy = d.y < 0.0f ? -1.0f : 1.0f;

			hit.delta.y = py * sy;
			hit.normal.y = sy;
			hit.pos.x = tb->GetPosition().x;
			hit.pos.y = ta->GetPosition().y + (half_.y * sy);
			hit.pos.z = tb->GetPosition().z;
		}
		//then z must collide first
		else
		{
			float sz = d.z < 0.0f ? -1.0f : 1.0f;

			hit.delta.z = pz * sz;
			hit.normal.z = sz;
			hit.pos.x = tb->GetPosition().x;
			hit.pos.y = tb->GetPosition().y;
			hit.pos.z = ta->GetPosition().z + (half_.z * sz);
		}

		return true;
	}

	bool Collider::IntersectLine(const glm::vec3& point, const glm::vec3& delta, const glm::vec3& padding, Hit& hit)
	{
		const glm::vec3& pos = GetParent()->GetComponent<Transform>()->GetPosition();

		float tmin = 0;
		float tmax = 1;
		//TRYING NEW CODE
		for (int a = 0; a < 3; a++)
		{
			float invD = 1.0f / delta[a];
			float t0 = (pos[a] - half_[a] - point[a]) * invD;
			float t1 = (pos[a] + half_[a] - point[a]) * invD;
			if (invD < 0.0f)
				std::swap(t0, t1);
			tmin = t0 > tmin ? t0 : tmin;
			tmax = t1 < tmax ? t1 : tmax;
			if (tmax <= tmin)
				return false;
		}

		hit.time = tmin;
		hit.pos = point + delta * hit.time;
		return true;

		//OLD COLLISION CODEs
		/*
		//Defining here so if multithreading changes how we get pos we can quickly fix it

		glm::vec3 scale = glm::vec3(delta.x != 0 ? 1.0f / delta.x : 0, delta.y != 0 ? 1.0f / delta.y : 0, delta.z != 0 ? 1.0f / delta.z : 0);
		//Get the sign of the delta inverse
		glm::vec3 sign;
		 sign.x = scale.x < 0 ? -1.0f : 1.0f;
		 sign.y = scale.y < 0 ? -1.0f : 1.0f;
		 sign.z = scale.z < 0 ? -1.0f : 1.0f;
		//Find the time at which the point interacts with the near and far edges
		 glm::vec3 nearTime = (pos - sign * (half_ + padding) - pos) * scale;
		 glm::vec3 farTime = (pos + sign * (half_ + padding) - pos) * scale;

		 //In 2D, there is no collision if the closest time on the axis is further than the
		 //Farthest time on the other axis
		 //Assuming this means if it is further than either fatherest times.

		 if (nearTime.x > farTime.y || nearTime.x > farTime.z
			 || nearTime.y > farTime.x || nearTime.y > farTime.z
			 || nearTime.z > farTime.x || nearTime.z > farTime.y
			 )
			 //No Collision
			 return false;

		 //Get the largest near and lesser far points
		 float nearestTime = nearTime.x > nearTime.y ? nearTime.x : nearTime.y;
		 nearestTime = nearestTime > nearTime.z ? nearestTime : nearTime.z;
		 float farestTime = farTime.x < farTime.y ? farTime.x : farTime.y;
		 farestTime = farestTime < farTime.z ? farestTime : farTime.z;

		 //If near time is >= 1 or far time is <= 0 the line doesn't actually touch the box
		 if (nearestTime >= 1 || farestTime <= 0)
			 return false;
		 
		 //If we are here, the line hits the box
		 
		 hit.time = clamp(nearestTime, 0.0f, 1.0f);//std::max(0.0f, std::min(nearestTime, 1.0f));
		 //If the hit is on the x side
		 if (nearTime.x > nearTime.y && nearTime.x > nearTime.z)
		 {
			 //Not 100% sure if we need the extra 0's
			 hit.normal.x = -sign.x;
			 //hit.normal.y = 0;
			 //hit.normal.z = 0;
		 }
		 else if (nearTime.y > nearTime.x && nearTime.y > nearTime.z)
		 {
			 hit.normal.y = -sign.y;
		 }
		 else
		 {
			 hit.normal.z = -sign.z;
		 }

		 hit.delta = (1.0f - hit.time) * -delta;
		 hit.pos = pos + delta * hit.time;

		 return true;

		 */
	}

	bool Collider::SweepAABB(const Collider* other, const glm::vec3& delta, Sweep& sweep)
	{
		//Defining here so if multithreading changes how we get pos we can quickly fix it
		const glm::vec3& tpos = GetParent()->GetComponent<Transform>()->GetPosition();
		const glm::vec3& opos = other->GetParent()->GetComponent<Transform>()->GetPosition();
		//The result
		bool r;
		//if Box isn't moving
		if (delta.length() == 0)
		{
			sweep.pos = opos;
			
			r = IntersectAABB(other, sweep.hit);
			sweep.time = r ? (sweep.hit.time = 0) : 1;
			return r;
		}

		//Else the box is moving
		r = IntersectLine(opos, delta, other->half_, sweep.hit);
		if (r)
		{
			//Tutorial says to use epsilon here, am confused why
			sweep.time = clamp(sweep.hit.time - std::numeric_limits<float>::epsilon(), 0.0f, 1.0f);
			sweep.pos = opos + delta * sweep.time;
			
			glm::vec3 dir = glm::normalize(delta);
			sweep.pos.x = clamp(sweep.hit.pos.x + dir.x * other->half_.x, tpos.x - half_.x, tpos.x + half_.x);
			sweep.pos.y = clamp(sweep.hit.pos.y + dir.y * other->half_.y, tpos.y - half_.y, tpos.y + half_.y);
			sweep.pos.z = clamp(sweep.hit.pos.z + dir.z * other->half_.z, tpos.z - half_.z, tpos.z + half_.z);
		}
		else
		{
			sweep.pos = opos + delta;
			sweep.time = 1;
		}
		return r;
		
	}

	void Collider::SetBoundingBox(const glm::vec3& max)
	{
		half_ = max;
	}

	const glm::vec3& Collider::GetBoundingBox() const
	{
		return half_;
	}

	bool Collider::IsStatic()
	{
		return static_;
	}

	void Collider::SetStatic(bool s)
	{
		static_ = s;
	}
}