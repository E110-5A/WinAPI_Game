#pragma once
#include "jsCollisionBlock.h"

namespace js
{
	class Collider;
	class Platform : public CollisionBlock
	{
	public:
		Platform();
		Platform(Pos pos);
		~Platform();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		// 대상의 Ground상태 변경, 점프카운트 초기화, Climb 예외처리
		void TargetSetGround(GameObject* target, bool isGround);
		void TargetJumpCountReset(GameObject* target);

	};
}