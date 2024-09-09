#include "ShrinkAndKill.h"
#include "Transform.h"


namespace Component

{
	void ShrinkandKill::OnStart()
	{
		runTime_ = 1.0f;
		timer_ = runTime_;

		tran_ = GetParent()->GetComponent<Component::Transform>();

		startingScale_ = tran_->GetScale();
	}

	void ShrinkandKill::OnUpdate(float dt)
	{
		

		tran_->SetScale(startingScale_ * (timer_ / runTime_));

		timer_ -= dt;

		if (timer_ <= 0)
			GetParent()->Destroy();
	}
}