#pragma once
#include "jsGameObject.h"

namespace js
{

	class DamageObject : public GameObject
	{
	public:
		DamageObject();
		DamageObject(Pos pos);
		~DamageObject();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC _hdc) override;

		// Ÿ�� ����� �Լ� ȣ��
		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		// �ܺο��� ȣ���
		Offence GetOffence() { return mOffence; }
	private:
		Collider*	mCollider;
		Offence		mOffence;
	};
}