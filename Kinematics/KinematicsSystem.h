#pragma once
#include "dlldef.h"
#include "Core.h"
#include "Kinematics.h"


namespace System
{
	class KinematicsSystem : public AssignedSystem<Component::Kinematics>
	{
		//All of the updating should be handled via the automatic system structure
		//We don't even need to expose this to the DLL...
	};
}