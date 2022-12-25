#pragma once
#include "jsCreature.h"

namespace js
{
	enum class eMonsterType
	{
		Imp,
		Parent,
	};

	enum class eMonsterState
	{
		Idle,
		Move,
		Skill,
		Death,
	};

	class Image;
	class PlayerProjectile;
	class Monster : public Creature
	{
	public:
		Monster();
		Monster(Pos pos);
		virtual ~Monster();

		virtual void Initialize();
		virtual void InitComponent() override;

		// 부모 함수 호출
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		

		// None
		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		// 기능
		void SelfHit(GameObject* attaker, float damage, eStagger stagger, float power);
		void SelfDamaged(float damage);
		// 입력받은 방향으로 밀려남
		void SelfKnockBack(float dir, eStagger stagger, float power);
		// FSM 만들때 추후 추가할 예정
		void SelfStun(float power);

	private:
		eMonsterType	mMonsterType;
		eMonsterState	mState;
	};
}

