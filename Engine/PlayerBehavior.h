#pragma once
#include "SimpleBehavior.h"
#include "glm/vec3.hpp"

namespace Component
{
	class Kinematics;

	class Transform;

	class Camera;

	class Shape;

	class PlayerBehavior : public SimpleBehavior
	{
	public:
		virtual void OnStart();

		virtual void OnUpdate(float dt);

		virtual void OnCollision(Object::GameObject* me, Object::GameObject* them);

		bool Jump(int index, float val);

		bool WalkY(int index, float val);

		bool WalkX(int index, float val);

		//These are here until I get axis working
		bool WalkFor(int index, float val);
		bool WalkBack(int index, float val);
		bool WalkLeft(int index, float val);
		bool WalkRight(int index, float val);

		bool CameraX(int index, float val);

		bool CameraY(int index, float val);

		bool Shoot(int index, float val);

		void ThrowDisk(float speed, float x = 1.0f, float y = 0.0f);

		void RaycastShoot();

		bool CheckGround();

		void Kill();

		void SpawnHitMarker(const glm::vec3& position);

		void Respawn();

		const std::vector<glm::vec3>* respawnLocations;

		int PlayerIndex;

		Kinematics* phys;
		Transform* tran;
		Camera* cam;

		glm::vec3 startingScale;

		glm::vec3 movement;

		float jump;
		bool onGround;

		bool isDead;

		Shape* projShape;

		float speed;

		bool fire_;

		bool canFire;

		float camSpeedX;
		float camSpeedY;
	};
}