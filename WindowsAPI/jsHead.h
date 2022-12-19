#pragma once
#include "jsCollisionCheck.h"

namespace js
{
	class Collider;
	class Creature;
	class Head : public CollisionCheck
	{
	public:
		Head();
		~Head();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

	protected:
		// 천장에 충돌했을때
		virtual void Process() override;
	};
}