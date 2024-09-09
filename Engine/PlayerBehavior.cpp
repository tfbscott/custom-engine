#include "PlayerBehavior.h"
#include "GameObject.h"
#include "Kinematics.h"
#include "Transform.h"
#include "Camera.h"
#include "ECSFactory.h"
#include "Collider.h"
#include "RenderComponent.h"
#include "ProjectileBehavior.h"
#include "ShrinkAndKill.h"
//For raycasting
#include "CollisionSystem.h"

//DEBUG ONLY
#include <iostream>

#define MOUSE_SEN	1.5f
#define DEADZONE 0.1f

namespace Component
{


	void PlayerBehavior::OnStart()
	{
		phys = parent->GetComponent<Component::Kinematics>();
		tran = parent->GetComponent<Transform>();
		cam = parent->GetComponent<Camera>();
		fire_ = false;
		canFire = true;
		camSpeedX = 0;
		camSpeedY = 0;
		speed = 10.0f;
		onGround = false;
		isDead = false;

		movement = glm::vec3(0.0f, 0.0f, 0.0f);
		startingScale = tran->GetScale();

		BindKeyAction("Walk_Y", this, &PlayerBehavior::WalkY);
		BindKeyAction("Walk_X", this, &PlayerBehavior::WalkX);
		//These exist until custom axes work
		BindKeyAction("Walk_For", this, &PlayerBehavior::WalkFor);
		BindKeyAction("Walk_Back", this, &PlayerBehavior::WalkBack);
		BindKeyAction("Walk_Left", this, &PlayerBehavior::WalkLeft);
		BindKeyAction("Walk_Right", this, &PlayerBehavior::WalkRight);

		BindKeyAction("Jump", this, &PlayerBehavior::Jump);

		BindKeyAction("Camera_X", this, &PlayerBehavior::CameraX);
		BindKeyAction("Camera_Y", this, &PlayerBehavior::CameraY);

		BindKeyAction("Shoot", this, &PlayerBehavior::Shoot);
	}

	void PlayerBehavior::OnUpdate(float dt)
	{
		glm::vec3 forward = cam->GetCameraFront();
		glm::vec3 right = glm::cross(cam->GetCameraFront(), glm::vec3(0, 1.0f, 0));

		if (CheckGround())
		{
			onGround = true;
			phys->SetAcceleration(glm::vec3(0.0f, 0.0f, 0.0f));
			jump = 0.0f;
		}
		else
		{
			onGround = false;
			phys->SetAcceleration(glm::vec3(0.0f, -20.0f, 0.0f));
		}

		if (!isDead)
		{

			//Update camera rotation


			tran->SetRotation(tran->GetRotation() + glm::vec3(0, camSpeedX, 0));
			
			cam->SetRotation(cam->GetRotationOffset() + glm::vec3(camSpeedY, 0, 0));

			//Prevent the camera from looping
			const glm::vec3 a = cam->GetRotationOffset();
			if (a.x > 90)
				cam->SetRotation(glm::vec3(90, a.y, a.z));
			else if (a.x < -90)
				cam->SetRotation(glm::vec3(-90, a.y, a.z));

			glm::vec3 movenorm = movement;
			if (movement.x + movement.y + movement.z > 0)
				movenorm = glm::normalize(movement);

			glm::vec3 movevec = (movenorm * speed);


			//OKAY LETS SEE IF I KNOW MATH
			//This creates a change of basis matrix
			glm::mat3 cob{ forward * glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), right * glm::vec3(1.0f, 0.0f, 1.0f) };

			movevec = cob * movevec;

			phys->SetVelocity(movevec + (phys->GetVelocity() * glm::vec3(0, 1, 0)));

		}
		else
		{
			glm::vec3 scale = tran->GetScale();

			if (scale.x > 0)
				tran->SetScale(scale - glm::vec3(1.5f * dt));
			else
			{
				//tran->SetScale(glm::vec3(0));
				//GetParent()->Destroy();

				Respawn();
				
			}
		}
	}

	void PlayerBehavior::OnCollision(Object::GameObject* me, Object::GameObject* them)
	{
		//std::cout << "Working Collision Events" << std::endl;
		
	}

	bool PlayerBehavior::Jump(int index, float val)
	{
		if ((index == PlayerIndex) && onGround && !isDead)
		{
			jump = 5.0f;
			phys->SetVelocity(glm::vec3(0, jump, 0));
			
			
		}

		return false;
	}

	bool PlayerBehavior::WalkY(int index, float val)
	{
		if (index == PlayerIndex)
			if (abs(val) > DEADZONE)
				movement.x = -val;
			else
				movement.x = 0.0f;

		return false;
	}

	bool PlayerBehavior::WalkX(int index, float val)
	{
		if (index == PlayerIndex)
			if (abs(val) > DEADZONE)
				movement.z = val;
			else
				movement.z = 0.0f;

		return false;
	}

	bool PlayerBehavior::WalkFor(int index, float val)
	{
		if (index == PlayerIndex)
			if (abs(val) > DEADZONE)
				movement.x = val;
			else
				movement.x = 0.0f;

		return false;
	}
	bool PlayerBehavior::WalkBack(int index, float val)
	{
		if (index == PlayerIndex)
			if (abs(val) > DEADZONE)
				movement.x = -val;
			else
				movement.x = 0.0f;

		return false;
	}
	bool PlayerBehavior::WalkLeft(int index, float val)
	{
		if (index == PlayerIndex)
			if (abs(val) > DEADZONE)
				movement.z = val;
			else
				movement.z = 0.0f;

		return false;
	}
	bool PlayerBehavior::WalkRight(int index, float val)
	{
		if (index == PlayerIndex)
			if (abs(val) > DEADZONE)
				movement.z = -val;
			else
				movement.z = 0.0f;

		return false;
	}

	bool PlayerBehavior::CameraX(int index, float val)
	{

		float offset = -val * MOUSE_SEN;
		if (abs(offset) < DEADZONE)
			offset = 0;

		if (index == PlayerIndex)
			camSpeedX = offset;

		return false;
	}

	bool PlayerBehavior::CameraY(int index, float val)
	{
		float offset = (val) * MOUSE_SEN;
		if (abs(offset) < DEADZONE)
			offset = 0;
		
		if (index == PlayerIndex)
			camSpeedY = -offset;

		return false;
	}

	bool PlayerBehavior::Shoot(int index, float val)
	{
		if (index == PlayerIndex && val == 1)
			RaycastShoot();

		return false;
	}

	void PlayerBehavior::ThrowDisk(float speed, float x, float y)
	{
		glm::vec3 forward = cam->GetCameraFront();
		glm::vec3 right = glm::cross(cam->GetCameraFront(), glm::vec3(0, 1.0f, 0));

		//Fire the projectile here
		const float spawnDist = 1.25f;

		//Create the projectle object
		Engine::ECSFactory* factory = GetParent()->GetCore()->Factory;
		Object::GameObject* proj = factory->CreateGameObject();
		Transform* ptran = factory->CreateComponent<Transform>(proj);
		Kinematics* pphys = factory->CreateComponent<Kinematics>(proj);
		RenderComponent* pmesh = factory->CreateComponent<RenderComponent>(proj);
		Collider* pcol = factory->CreateComponent<Collider>(proj);
		ProjectileBehavior* pbeh = factory->CreateComponent<ProjectileBehavior>(proj);
		pbeh->thrower = GetParent();

		glm::vec3 scale(0.5f, 0.25f, 0.5f);

		//ptran->SetRotation(tran->GetRotation());
		ptran->SetPosition(tran->GetPosition() + (glm::normalize(cam->GetCameraFront()) * spawnDist));
		ptran->SetScale(scale);

		pmesh->SetShape(projShape);

		pphys->SetVelocity((glm::normalize((forward * x) + (right * y)) * speed));

		pphys->SetAcceleration(glm::vec3(0.0f, -1.0f, 0.0f));

		pcol->SetBoundingBox(scale / 2.0f);
	}

	void PlayerBehavior::RaycastShoot()
	{
		glm::vec3 forward = cam->GetCameraFront();
		const float dist = 100.0f;

		//Alright, shoddy raycast shooting lets GO!
		System::CollisionSystem* colSys = GetParent()->GetCore()->GetSystem<System::CollisionSystem>();

		System::RaycastData rdata;

		rdata.ignore.push_back(GetParent());

		Component::RaycastReturn hit;

		glm::vec3 start = cam->GetPositionOffset() + tran->GetPosition() + (glm::normalize(forward) * 1.0f);

		if (colSys->PerfromRayCast(start, glm::normalize(forward) * dist, hit, rdata))
		{
			//If we hit something
			if (hit.GameObject->GetIdentifier() == "Player")
			{
				std::cout << "Player " << PlayerIndex << " killed Player " << hit.GameObject->GetComponent<PlayerBehavior>()->PlayerIndex << std::endl;
				hit.GameObject->GetComponent<PlayerBehavior>()->Kill();
			}
			else
				std::cout << "Player " << PlayerIndex << " hit the " << hit.GameObject->GetIdentifier() << std::endl;


			SpawnHitMarker(hit.Hit.pos);
		}
	}
	
	bool PlayerBehavior::CheckGround()
	{
		glm::vec3 start = tran->GetPosition() - glm::vec3(0, 1.5f, 0);

		System::CollisionSystem* colSys = GetParent()->GetCore()->GetSystem<System::CollisionSystem>();

		System::RaycastData rdata;

		rdata.ignore.push_back(GetParent());

		Component::RaycastReturn hit;

		return colSys->PerfromRayCast(start, glm::vec3(0, -0.01f, 0), hit, rdata);
	}

	void PlayerBehavior::Kill()
	{
		isDead = true;
		parent->GetComponent<RenderComponent>()->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
	}

	void PlayerBehavior::SpawnHitMarker(const glm::vec3& position)
	{
		Engine::ECSFactory* factory = GetParent()->GetCore()->Factory;
		Object::GameObject* proj = factory->CreateGameObject();
		Transform* ptran = factory->CreateComponent<Transform>(proj);
		RenderComponent* pmesh = factory->CreateComponent<RenderComponent>(proj);
		ShrinkandKill* pbeh = factory->CreateComponent<ShrinkandKill>(proj);

		pmesh->SetShape(projShape);
		pmesh->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

		ptran->SetPosition(position);
		ptran->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	}


	void PlayerBehavior::Respawn()
	{
		tran->SetScale(startingScale);
		isDead = false;
		unsigned int loc = rand() % respawnLocations->size();
		tran->SetPosition((*respawnLocations)[loc]);
	}
}