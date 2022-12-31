#pragma once
#include "jsGameObject.h"

namespace js
{
	class Monster;
	class MonsterAttack : public GameObject
	{
	public:
		MonsterAttack();
		MonsterAttack(Monster* owner);

		~MonsterAttack();


		virtual void Tick() override;

		virtual void Render(HDC hdc) override;

		void Process();


		// Ÿ�� ����� �Լ� ȣ��
		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		// �ܺο��� ȣ���
		void Active();
		void InActive()
		{
			// �����ð� �ʱ�ȭ
			mDeltaTime = 0.0f;
			// ��Ȱ��ȭ
			mAble = false;
		}
		bool IsActive() { return mAble; }

	private:
		Collider*			mCollider;
		Monster*			mOwner;
		MonsterSkillInfo	mInfo;
	private:
		float				mRange;
		float				mDeltaTime;
		float				mLifeTime;
	};
}