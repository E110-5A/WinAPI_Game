#pragma once
#include "jsGameObject.h"

namespace js
{
	class PlayerProjectile : public GameObject
	{
	public:
		PlayerProjectile();
		~PlayerProjectile();

		virtual void Tick() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;
	private:
		Vector2 mDir;
		float mRange;
		float mLifeTime;
	};
}