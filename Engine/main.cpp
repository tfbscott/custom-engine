#include "Core.h"
#include "Renderer.h"

#include "RenderSystem.h"
#include "KinematicsSystem.h"
#include "CollisionSystem.h"
#include "SimpleBehaviorSystem.h"
#include "CameraSystem.h"

#include "InputKey.h"

#include "GameStateManager.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "InputDevice.h"

#include "LevelA.h"

int main(void)
{
	Engine::Core core;

	Engine::Renderer renderer;
    Engine::InputManager inputManager;

    System::RenderSystem renderSystem;
    System::KinematicsSystem physicsSystem;
    System::CollisionSystem collisionSystem;
    System::CameraSystem cameraSystem;
    System::SimpleBehaviorSystem behaviorSystem;

	core.SetRenderer(&renderer);
    core.SetInputManager(&inputManager);

    core.Init();

    //So can't pass member functions in, how the FUCK

    renderer.CreateInputDevices(&inputManager);
    //Start mapping inputs
    inputManager.MapInputToAction(InputKey::KEY_W, "Walk_For");
    inputManager.MapInputToAction(InputKey::KEY_A, "Walk_Right");
    inputManager.MapInputToAction(InputKey::KEY_S, "Walk_Back");
    inputManager.MapInputToAction(InputKey::KEY_D, "Walk_Left");
    inputManager.MapInputToAction(InputKey::GAMEPAD_LEFT_STICK_Y, "Walk_Y");
    inputManager.MapInputToAction(InputKey::GAMEPAD_LEFT_STICK_X, "Walk_X");
   // inputManager.MapInputToAction(InputKey::KEY_W, "Walk_X");

    inputManager.MapInputToAction(InputKey::KEY_SPACE, "Jump");
    inputManager.MapInputToAction(InputKey::GAMEPAD_A, "Jump");

    inputManager.MapInputToAction(InputKey::MOUSE_X, "Camera_X");
    inputManager.MapInputToAction(InputKey::GAMEPAD_RIGHT_STICK_X, "Camera_X");
    inputManager.MapInputToAction(InputKey::MOUSE_Y, "Camera_Y");
    inputManager.MapInputToAction(InputKey::GAMEPAD_RIGHT_STICK_Y, "Camera_Y");

    inputManager.MapInputToAction(InputKey::MOUSE_LEFT, "Shoot");
    inputManager.MapInputToAction(InputKey::GAMEPAD_RIGHT_BUMPER, "Shoot");

    /*renderer.SetMouseCallback(inputManager.MouseCallback);
    renderer.SetMouseButtonCallback(inputManager.MouseButtonCallback);*/

    renderer.CaptureCursor();
    
   
   

    
    //Use behaviors to set physics
    core.AddSystem(&behaviorSystem);
    //Run the physics
    core.AddSystem(&physicsSystem);
    //Resolve any collisions
    core.AddSystem(&collisionSystem);
    
    core.AddSystem(&cameraSystem);
    core.AddSystem(&renderSystem);


    Gamestate::LevelA* gsa = new Gamestate::LevelA;
    //THESE ARE AUTO DELETED

    //core.AddGameState(gst);
    core.AddGameState(gsa);
   
    core.StateManager->SetNextGameState(0);

	core.Run();

    core.Exit();

}