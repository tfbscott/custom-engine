#include "LevelB.h"
#include "Transform.h"
#include "Kinematics.h"
#include "RenderComponent.h"
#include "Collider.h"
#include "Camera.h"
#include "Shape.h"
#include "PlayerBehavior.h"

namespace Gamestate
{


	void LevelB::Load() 
	{
		/*
		//This is the verticies and indicies for a cube
		const float cubehalf = 0.5f;
		std::vector<glm::vec3> v;
		v.push_back(glm::vec3(cubehalf, cubehalf, cubehalf));
		v.push_back(glm::vec3(cubehalf, -cubehalf, cubehalf));
		v.push_back(glm::vec3(-cubehalf, cubehalf, cubehalf));
		v.push_back(glm::vec3(-cubehalf, -cubehalf, cubehalf));
		v.push_back(glm::vec3(cubehalf, cubehalf, -cubehalf));
		v.push_back(glm::vec3(cubehalf, -cubehalf, -cubehalf));
		v.push_back(glm::vec3(-cubehalf, cubehalf, -cubehalf));
		v.push_back(glm::vec3(-cubehalf, -cubehalf, -cubehalf));

		std::vector<glm::ivec3> i;
		i.push_back(glm::ivec3(0, 1, 2));
		i.push_back(glm::ivec3(1, 2, 3));
		i.push_back(glm::ivec3(2, 7, 3));
		i.push_back(glm::ivec3(2, 6, 7));
		i.push_back(glm::ivec3(6, 4, 0));
		i.push_back(glm::ivec3(2, 6, 0));
		i.push_back(glm::ivec3(0, 5, 1));
		i.push_back(glm::ivec3(0, 4, 5));
		i.push_back(glm::ivec3(1, 5, 7));
		i.push_back(glm::ivec3(1, 7, 3));
		i.push_back(glm::ivec3(4, 5, 6));
		i.push_back(glm::ivec3(5, 6, 7));


		box = new Component::Shape;
		box->SetShape(v, i);
		box->MakeVAO();

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

		//pphys->SetVelocity(glm::vec3(0.0f, 0.0f, 1.0f));
		
		
		Object::GameObject* floor = CreateGameObject();
		
		Component::Transform* tran = CreateComponent<Component::Transform>(floor);
		
		Component::Kinematics* phys = CreateComponent<Component::Kinematics>(floor);
		
		Component::Collider* col = CreateComponent<Component::Collider>(floor);
		
		tran->SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));
		
		glm::vec3 scalevec = glm::vec3(40.0f, 1.0f, 40.0f);
		
		tran->SetScale(scalevec);
		
		phys->SetAcceleration(glm::vec3(0.0f, 0.0f, 0.0f));
		
		col->SetBoundingBox(scalevec / 2.0f);

		col->SetStatic(true);
		
		Component::RenderComponent* mesh = CreateComponent<Component::RenderComponent>(floor);
		
		mesh->SetShape(box);

		mesh->SetColor(glm::vec3(0, 0, 1));

		
		std::vector<glm::vec3> treepos;
		treepos.push_back(glm::vec3(5.0f, 0.0f, 0.0f));
		treepos.push_back(glm::vec3(7.0f, 0.0f, -2.0f));
		treepos.push_back(glm::vec3(3.0f, 0.0f, 2.0f));
		treepos.push_back(glm::vec3(4.0f, 0.0f, 3.0f));
		treepos.push_back(glm::vec3(1.0f, 0.0f, -1.0f));

		glm::vec3 treeVec = glm::vec3(0.5f, 10.0f, 0.5f);

		//Create some trees
		//Peak Bob Ross in this code motha fucka
		for (glm::vec3& pos : treepos)
		{

			Object::GameObject* treea = CreateGameObject();

			treea->SetIdentifier("Tree");

			Component::Transform* tatran = CreateComponent<Component::Transform>(treea);
			tatran->SetScale(treeVec);
			tatran->SetPosition(pos);

			Component::Collider* tacol = CreateComponent<Component::Collider>(treea);
			tacol->SetStatic(true);
			tacol->SetBoundingBox(treeVec / 2.0f);

			Component::RenderComponent* tamesh = CreateComponent<Component::RenderComponent>(treea);
			tamesh->SetShape(box);
			tamesh->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));


			objects.push_back(treea);
		}
		Object::GameObject* boxb = CreateGameObject();

		boxb->SetIdentifier("Hole");

		Component::Transform* bbtran = CreateComponent<Component::Transform>(boxb);

		Component::Kinematics* bbphys = CreateComponent<Component::Kinematics>(boxb);

		Component::Collider* bbcol = CreateComponent<Component::Collider>(boxb);

		Component::RenderComponent* bbmesh = CreateComponent<Component::RenderComponent>(boxb);

		bbtran->SetPosition(glm::vec3(10.0f, 0.0f, 1.0f));

		bbcol->SetStatic(true);

		//bbphys->SetVelocity(glm::vec3(0.0f, 0.0f, -1.0f));

		bbmesh->SetShape(box);

		bbmesh->SetColor(glm::vec3(0, 1, 1));
		
		objects.push_back(player);
		objects.push_back(floor);
		
		objects.push_back(boxb);
		
		*/
	};

	void LevelB::Init() {};

	void LevelB::Update(float dt) {};

	void LevelB::Shutdown() {};

	void LevelB::UnLoad() {
        delete box;


		for (auto o : objects)
			o->Destroy();
    };

}