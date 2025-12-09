#include "LevelA.h"

#include "Kinematics.h"
#include "RenderComponent.h"
#include "Collider.h"
#include "Camera.h"
#include "Shape.h"
#include "Texture.h"
#include "ShooterPlayerBehavior.h"
#include "ReadWriteTools.h"

#include <fstream>

namespace Gamestate
{
	void LevelA::Load() 
	{
		//This is the verticies and indicies for a cube
		const float cubehalf = 0.5f;

		box = Tools::ReadShape("Assets/Generic/Cube_3D.txt");// new Component::Shape;

		square = Tools::ReadShape("Assets/Generic/Square_2D.txt");//new Component::Shape;

		texA = new Component::Texture;
		texA->Read("man.jpg", true);

		int maxi = 1;
		int maxj = 2;
		
		startingPos.push_back(glm::vec3(15.0f, 2.0f, 15.0));
		startingPos.push_back(glm::vec3(-15.0f, 2.0f, 15.0));
		startingPos.push_back(glm::vec3(-15.0f, 2.0f, -15.0));
		startingPos.push_back(glm::vec3(15.0f, 2.0f, -15.0));
		startingPos.push_back(glm::vec3(25.0f, 2.0f, 25.0));
		startingPos.push_back(glm::vec3(-25.0f, 2.0f, 25.0));
		startingPos.push_back(glm::vec3(-25.0f, 2.0f, -25.0));
		startingPos.push_back(glm::vec3(25.0f, 2.0f, -25.0));
		startingPos.push_back(glm::vec3(10.0f, 2.0f, 10.0));
		startingPos.push_back(glm::vec3(-10.0f, 2.0f, 10.0));
		startingPos.push_back(glm::vec3(-10.0f, 2.0f, -10.0));
		startingPos.push_back(glm::vec3(10.0f, 2.0f, -10.0));


		int total = 0;
		for (int i = 0; i < maxi; i++)
		{
			for (int j = 0; j < maxj; j++)
			{
				glm::vec3 scalevec = glm::vec3(1.0f, 2.0f, 1.0f);

				Object::GameObject* playerA = CreateGameObject();

				playerA->SetIdentifier("Player");

				Component::Transform* ptran = CreateComponent<Component::Transform>(playerA);

				Component::Camera* pcam = CreateComponent<Component::Camera>(playerA);

				Component::Kinematics* pphys = CreateComponent<Component::Kinematics>(playerA);

				Component::ShooterPlayerBehavior* pbeh = CreateComponent<Component::ShooterPlayerBehavior>(playerA);

				Component::RenderComponent* mesh = CreateComponent<Component::RenderComponent>(playerA);
				mesh->SetShape(box);
				mesh->SetTexture(texA);
				pcam->MakeIgnored(mesh);
				//
				//mesh->SetColor(glm::vec3(0, 0, 1));

				pbeh->projShape = box;
				pbeh->PlayerIndex = total;
				pbeh->respawnLocations = &startingPos;

				Component::Collider* pcol = CreateComponent<Component::Collider>(playerA);
				pcol->SetBoundingBox(scalevec / 2.0f);

				ptran->SetPosition(startingPos[total]);

				ptran->SetScale(scalevec);

				pcam->SetRotation(glm::vec3(0.0f, -90.0, 0.0f));

				pcam->SetPosition(glm::vec3(0.0f, 0.75f, 0.0f));

				float w = (1 / (float)maxi);
				float h = (1 / (float)maxj);
				float wp = w * i, hp = h * j;

				//Wp and Hp are the position on the screen
				
				

				pcam->SetDisplayData(wp, hp, w, h);
				//pphys->SetVelocity(glm::vec3(0.0f, 0.0f, 1.0f));

				objects.push_back(playerA);

				total++;


				if (1)
				{
					Object::GameObject* playerHUD = CreateGameObject();

 					Component::Transform* htran = CreateComponent<Component::Transform>(playerHUD);
					Component::RenderComponent* hmesh = CreateComponent<Component::RenderComponent>(playerHUD);
					hmesh->SetShape(square);
					hmesh->SetColor(glm::vec3(1, 1, 1));
					pcam->AddHUD(hmesh);

					
					htran->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
					htran->SetRotation(glm::vec3(0.0f, 0.0f, 45.0f));
					htran->SetScale(glm::vec3(12.0f, 12.0f, 12.0f));

					objects.push_back(playerHUD);
				}
			}
		}
		
		
		Object::GameObject* floor = CreateBox("Floor", 0, -1, 0, 60, 1, 60);

		Object::GameObject* hole = CreateBox("Wall", 0, 1, 0, 10, 4, 10, 0.9f, 0.9f, 0.9f);

		Object::GameObject* northWall = CreateBox("Wall", /*|*/30, 1, 0, /*|*/ 1, 4, 60,/*|*/ 0.9f, 0.9f, 0.9f);
		Object::GameObject* southWall = CreateBox("Wall", /*|*/-30, 1, 0,/*|*/ 1, 4, 60,/*|*/ 0.9f, 0.9f, 0.9f);

		Object::GameObject* eastWall = CreateBox("Wall", /*|*/0, 1, 30, /*|*/ 60, 4, 1,/*|*/ 0.9f, 0.9f, 0.9f);
		Object::GameObject* westWall = CreateBox("Wall", /*|*/0, 1, -30,/*|*/ 60, 4, 1,/*|*/ 0.9f, 0.9f, 0.9f);
		


	};

	void LevelA::Init() {};

	void LevelA::Update(float dt) {};

	void LevelA::Shutdown() {};

	void LevelA::UnLoad() {
        delete box;

		for (auto o : objects)
			o->Destroy();
    };


	Object::GameObject* LevelA::CreateBox(const char* name, float x, float y, float z, float sx, float sy, float sz, float r, float g, float b)
	{
		Object::GameObject* boxob = CreateGameObject();

		boxob->SetIdentifier(name);

		Component::Transform* tran = CreateComponent<Component::Transform>(boxob);

		Component::Kinematics* phys = CreateComponent<Component::Kinematics>(boxob);

		Component::Collider* col = CreateComponent<Component::Collider>(boxob);

		tran->SetPosition(glm::vec3(x, y, z));

		glm::vec3 scalevec = glm::vec3(sx, sy, sz);

		tran->SetScale(scalevec);

		phys->SetAcceleration(glm::vec3(0.0f, 0.0f, 0.0f));

		col->SetBoundingBox(scalevec / 2.0f);

		col->SetStatic(true);

		Component::RenderComponent* mesh = CreateComponent<Component::RenderComponent>(boxob);

		mesh->SetShape(box);

		mesh->SetColor(glm::vec3(r, g, b));

		objects.push_back(boxob);

		return boxob;
	}

}