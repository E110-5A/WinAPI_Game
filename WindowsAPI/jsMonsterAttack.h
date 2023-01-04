#pragma once
#include "jsGameObject.h"

namespace js
{
	class Creature;
	class MonsterAttack : public GameObject
	{
	public:
		MonsterAttack();
		MonsterAttack(Creature* owner);

		~MonsterAttack();


		virtual void Tick() override;

		virtual void Render(HDC hdc) override;

		void Process();


		// 타격 대상의 함수 호출
		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		// 외부에서 호출됨
		void Active();
		void InActive()
		{
			// 유지시간 초기화
			mDeltaTime = 0.0f;
			// 비활성화
			SetAble(false);
		}
		bool IsActive() { return mAble; }

	private:
		Collider*			mCollider;
		Creature*			mOwner;
		MonsterSkillInfo	mInfo;
	private:
		float				mRange;
		float				mDeltaTime;
		float				mLifeTime;
	};
}