#pragma once
#include "jsGameObject.h"

namespace js
{
	struct MonsterStat
	{
		float maxHp;		// 310
		float curHp;
		float def;			// 0
		float moveSpeed;	// 16
		float att;			// 13
	};

	enum class eMonsterState
	{
		Idle,
		Move,
		Skill,
		Death,
	};

	class Image;
	class Monster : public GameObject
	{
	public:
		Monster();
		Monster(Pos pos);
		virtual ~Monster();

		virtual void Initialize();

		virtual void InitStat() {};
		virtual void InitCollider() {};
		virtual void InitAnimator() {};
		virtual void InitRigidbody() {};

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		// 기능
		// 입력받은 값 만큼 HP 감소
		void Damaged();
		// 입력받은 방향으로 밀려남
		void KnockBack();
		// 입력받은 값 동안 움직이지 않음
		void Strun();


		// 충돌설정
		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		// 피해량 입력
		void Hit(float value) {};

	private:
		Image* mImage;
	};
}

