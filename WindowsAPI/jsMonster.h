#pragma once
#include "jsGameObject.h"

namespace js
{
	class Image;
	class Monster : public GameObject
	{
	public:
		Monster();
		Monster(Pos pos);
		~Monster();

		void Init();
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		// 몬스터 rigidbody를 통해서 뒤로 밀리도록 한다
		void KnockBack() {};

		// 피해량 입력
		void Hit(float value) {};

	private:
		Image* mImage;
	};
}

