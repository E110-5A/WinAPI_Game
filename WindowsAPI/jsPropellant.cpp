#include "jsPropellant.h"

// manager
#include "jsTime.h"

// component
#include "jsCollider.h"
#include "jsAnimator.h"
#include "jsRigidbody.h"

// object
#include "jsGameObject.h"
#include "jsCreature.h"

namespace js
{
	Propellant::Propellant()
		: mAnimator(nullptr)
		, mEruptionTime(0.60f)
		, mEruptionDeltaTime(0.0f)
		, mDelayTime(0.20f)
		, mIsEruption(false)
	{
		Initialize();
	}
	Propellant::Propellant(Pos pos)
		: mAnimator(nullptr)
		, mEruptionTime(0.60f)
		, mEruptionDeltaTime(0.0f)
		, mDelayTime(0.20f)
		, mIsEruption(false)
	{
		SetPos(pos);
		Initialize();
	}
	Propellant::~Propellant()
	{
	}

	// Propellant.bmp
	// eruption
	void Propellant::Initialize()
	{
		EventObject::Initialize();
		SetImage(L"Propellant", L"..\\Resources\\Image\\EventObject\\Propellant.bmp");
		// 콜라이더 설정
		mEventCollider->SetSize(Size(48.0f, 120.0f));
		mEventCollider->SetOffset(Vector2(14.0f,32.0f));
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Eruption", mImage, Pos(0.f, 0.f), Size(24.0f, 60.0f)
			, Vector2(0.f, 0.f), 6, 0.1f);
		mAnimator->Play(L"Eruption");
	}

	void Propellant::Tick()
	{
		EventObject::Tick();
		Process();
	}
	void Propellant::Render(HDC hdc)
	{
		// 애니메이션 재생용
		EventObject::Render(hdc);
	}


	void Propellant::Process()
	{
		mEruptionDeltaTime += Time::GetDeltaTime();

		// mDelayTime 이후부터 유효함
		if (mEruptionDeltaTime >= mDelayTime)
		{
			mIsEruption = true;
			if (mEruptionDeltaTime >= mEruptionTime)
			{
				mIsEruption = false;
				mEruptionDeltaTime = 0.0f;
			}
		}
	}



	void Propellant::OnCollisionEnter(Collider* other)
	{
		// 위로 날리기
		Push(other);
	}
	void Propellant::OnCollisionStay(Collider* other)
	{
		Push(other);
	}
	void Propellant::OnCollisionExit(Collider* other)
	{
	}
	void Propellant::Push(Collider* other)
	{
		Creature* creature = dynamic_cast<Creature*>(other->GetOwner());

		if (true == mIsEruption && nullptr != creature)
		{
			Rigidbody* targetRigidbody = creature->GetRigidbody();
			Vector2 velocity = targetRigidbody->GetVelocity();
			velocity.y -= 1000.0f;
			targetRigidbody->SetVelocity(velocity);
		}
	}
}