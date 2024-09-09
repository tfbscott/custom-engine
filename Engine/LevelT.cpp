#include "LevelT.h"
#include "Transform.h"
#include "Kinematics.h"
#include "RenderComponent.h"
#include "Collider.h"
#include "Camera.h"
#include "Shape.h"
#include "PlayerBehavior.h"
#include "glm/glm.hpp"

namespace Gamestate
{


	void LevelT::Load() 
	{
		/*
		std::vector<glm::vec3> v;
		v.push_back(glm::vec3(1.0, 1.0, 0.0));
		v.push_back(glm::vec3(1.0, -1.0, 0.0));
		v.push_back(glm::vec3(-1.0, 1.0, 0.0));
		v.push_back(glm::vec3(-1.0, -1.0, 0.0));

		std::vector<glm::ivec3> i;
		i.push_back(glm::ivec3(0, 1, 2));
		i.push_back(glm::ivec3(1, 2, 3));

		box = new Component::Shape;
		box->SetShape(v, i);
		box->MakeVAO(true);


		Object::GameObject* player = CreateGameObject();

		player->SetIdentifier("Player");

		Component::Transform* ptran = CreateComponent<Component::Transform>(player);

		Component::Camera* pcam = CreateComponent<Component::Camera>(player);

		Component::Kinematics* pphys = CreateComponent<Component::Kinematics>(player);

		Component::PlayerBehavior* pbeh = CreateComponent<Component::PlayerBehavior>(player);
		pbeh->projShape = box;

		Component::Collider* pcol = CreateComponent<Component::Collider>(player);

		ptran->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));

		pcam->SetRotation(glm::vec3(0.0f, -90.0, 0.0f));

		objects.push_back(player);


		Object::GameObject* test = CreateGameObject();

		Component::Transform* tran = CreateComponent<Component::Transform>(test);

		Component::RenderComponent* mesh = CreateComponent<Component::RenderComponent>(test);

		tran->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));

		mesh->SetShape(box);

		mesh->SetColor(glm::vec3(0, 0, 1));*/
	};

	void LevelT::Init() {};

	void LevelT::Update(float dt) {};

	void LevelT::Shutdown() {};

	void LevelT::UnLoad() {
       

		for (auto o : objects)
			o->Destroy();
    };

}