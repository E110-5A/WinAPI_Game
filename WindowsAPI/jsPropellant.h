#pragma once
#include "jsEventObject.h"

namespace js
{
	class Animator;
	class Propellant : public EventObject
	{
	public:
		Propellant();
		Propellant(Pos pos);
		virtual ~Propellant();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void Process();

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void Push(Collider* other);

	private:
		Animator*	mAnimator;
		bool		mIsEruption;
		float		mEruptionTime;
		float		mEruptionDeltaTime;
		float		mDelayTime;
	};
}