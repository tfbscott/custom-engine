#include "pch.h"	//NEED IN DLL
#include "Core.h"
#include "ECSFactory.h"
#include "GameStateManager.h"
#include "GameObjectManager.h"
#include "BaseInputManager.h"

#include <chrono>
#include <algorithm>
#include <execution>


#define ALLOW_THREADING 0

#if ALLOW_THREADING
#include <thread>
#endif

namespace Component
{
	BaseComponent::BaseComponent() :parent(nullptr), index_(0), system_(nullptr)
	{

	}

	Object::GameObject* BaseComponent::GetParent() const
	{
		return parent;
	}
}

namespace System
{
	BaseSystem::~BaseSystem()
	{
		for (Component::BaseComponent* c : components_)
		{
			delete c;
		}
	}

	void BaseSystem::Initalize()
	{

	}


	//Creating a functor for the Update loop
	struct UpdateFunctor
	{
		float dt = 0;

		void operator() (Component::BaseComponent* c)
		{
			c->Update(dt);
		}
	};


	void BaseSystem::Update(float dt)
	{

		UpdateFunctor func;
		func.dt = dt;
		//Should be parrallel, unless overridden
		std::for_each(std::execution::par, components_.begin(), components_.end(), func);

		//for (Component::BaseComponent* c : components_)
		//{
		//	c->Update(dt);
		//}
	}

	void BaseSystem::Exit()
	{

	}

	void BaseSystem::Sync()
	{

	}

	void BaseSystem::AddComponent(Component::BaseComponent* b)
	{
		components_.push_back(b);
		b->index_ = (unsigned int)components_.size() - 1;
		b->system_ = this;
	}

	void BaseSystem::RemoveComponent(Component::BaseComponent* b)
	{
		//The index value should be the location of the component
		
		//Replace the location of b with the last component
		components_[b->index_] = components_[components_.size() - 1];
		//Update the index value
		components_[b->index_]->index_ = b->index_;
		//Calles the components delete function
		b->OnDelete();
		//Remove the last component from the list
		components_.pop_back();
	}
}

namespace Engine
{
	//HELPER FUNCTION
	void Core::ThreadUpdate(int thread, float dt)
	{
		for (System::BaseSystem* s : threads_[thread])
		{
			s->Update(dt);
		}
	}



	Core::Core() : StateManager(nullptr), ObjectManager(nullptr), Factory(nullptr), systems_(), renderer_(nullptr), inputManager(nullptr), isRunning_(true)
	{
		StateManager = new GameStateManager;
		StateManager->SetParent(this);

		ObjectManager = new GameObjectManager;

		Factory = new ECSFactory;
		Factory->SetParent(this);
	}

	Core::~Core()
	{
		delete StateManager;
		delete ObjectManager;
		delete Factory;
	}

	void Core::AddSystem(System::BaseSystem* s, unsigned int thread)
	{
		systems_.push_back(s);
		s->SetParent(this);

#if ALLOW_THREADING
		if (threads_.size() == thread)
			threads_.push_back(std::vector<System::BaseSystem*>());

		threads_[thread].push_back(s);
#endif
	}

	void Core::Init()
	{
		if (renderer_)
			renderer_->Initalize();

		//On first start, init systems
		for (System::BaseSystem* s : systems_)
		{
			s->Initalize();
		}
	}

	void Core::Run()
	{
		auto lastTime = std::chrono::steady_clock::now();

		
		//While is running and the renderer exists and the window isn't closing
		while (isRunning_ && ((renderer_)?!renderer_->WindowClosing():true))
		{
			auto currTime = std::chrono::steady_clock::now();
			auto durr = std::chrono::duration<float>(currTime - lastTime);
			float dt = durr.count();
			lastTime = currTime;

			//Currently does nothing...
			if (inputManager)
				inputManager->ProcessInput();

			
			//This one actually processes the input
			if (renderer_)
				renderer_->Update();

			for (System::BaseSystem* s : systems_)
			{
				s->Sync();
			}

#if ALLOW_THREADING
			//MULTITHREADING
			std::list<std::thread> threadObj;

			//The ++ on begin is to skip thread 1, will be using current thread
			//DOES NOT WORK
			for (int i = 1; i < threads_.size(); i++)
			{
				threadObj.emplace_back(&Core::ThreadUpdate, this, i, dt);
			}

			for (System::BaseSystem* s : threads_[0])
			{
				s->Update(dt);
			}

			for (std::thread& t : threadObj)
			{
				t.join();
			}
#else
			for (System::BaseSystem* s : systems_)
			{
				s->Update(dt);
			}
#endif

			//State manager happens after the game loop
			StateManager->Update(dt);

			//Cleanup objects flagged as destroyed
			ObjectManager->CleanupDestroyedObjects();

			//if (renderer_)
			//	renderer_->Draw();
		}

	}


	void Core::AddGameState(Gamestate::GameState* gs)
	{
		StateManager->AddGamestate(gs);
	}

	void Core::Exit()
	{
		//Delete all gameobjects that still exist, for some reason
		ObjectManager->DeleteAllObjects();
		//Exiting, close systems
		for (System::BaseSystem* s : systems_)
		{
			s->Exit();
		}

		if (renderer_)
			renderer_->Exit();
	}

	void Core::SetRenderer(BaseRenderer* r)
	{
		renderer_ = r;
	}

	void Core::SetInputManager(InputManager* i)
	{
		inputManager = i;
	}
}