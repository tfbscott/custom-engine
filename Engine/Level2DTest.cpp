#include "Level2DTest.h"
#include "Shape.h"
#include "Kinematics.h"
#include "Transform.h"
#include "Camera.h"
#include "MetroidVaniaPlayerBehavior.h"
#include "Collider.h"
#include "RenderComponent.h"
#include "ReadWriteTools.h"
#include "glm/vec3.hpp"



namespace Gamestate {

	void Level2DTest::Load()
	{
		Component::Shape* square = Tools::ReadShape("Assets/Generic/Square_2D.txt");

		//Create the player
		Object::GameObject* player = CreateGameObject("Player_2D");
		objects.push_back(player);

		Component::Transform* playerTransform = CreateComponent<Component::Transform>(player);
		Component::Kinematics* playerPhysics = CreateComponent<Component::Kinematics>(player);  
		Component::Collider* playerCollider = CreateComponent<Component::Collider>(player);
		Component::MetroidVaniaPlayerBehavior* playerBehavior = CreateComponent<Component::MetroidVaniaPlayerBehavior>(player);
		Component::RenderComponent* playerRenderer = CreateComponent<Component::RenderComponent>(player);
		playerTransform->SetPosition(glm::vec3(0, 0, 0));
		playerRenderer->SetShape(square);
		playerCollider->SetBoundingBox(glm::vec3(1, 1, 1));
		playerTransform->SetScale(glm::vec3(2, 2, 1));

		Object::GameObject* camera = CreateGameObject("Camera_2D");
		objects.push_back(camera);
		Component::Transform* cameraTransform = CreateComponent<Component::Transform>(camera);
		Component::Camera* cameraCamera = CreateComponent<Component::Camera>(camera);

		cameraTransform->SetPosition(glm::vec3(0, 0, -5));
		cameraTransform->SetRotation(glm::vec3(0, -90, 0));

		Object::GameObject* floor = CreateGameObject("Floor_2D");
		objects.push_back(camera);

		Component::Transform* floorTransform = CreateComponent<Component::Transform>(floor);
		Component::Collider* floorCollider = CreateComponent<Component::Collider>(floor);
		floorTransform->SetPosition(glm::vec3(0, -2, 0));
		floorCollider->SetBoundingBox(glm::vec3(20, 1, 1));
		floorCollider->SetStatic(true);
	}

	void Level2DTest::Init()
	{

	}

	void Level2DTest::Update(float dt)
	{

	}

	void Level2DTest::UnLoad()
	{
		for (auto o : objects)
		{
			o->Destroy();
		}
	}

	void Level2DTest::Shutdown()
	{

	}

}