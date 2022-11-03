#pragma once
#include "jsGameObject.h"

namespace js
{

	class Projectile :
		public GameObject
	{
	public:
		Projectile();
		~Projectile();

		virtual void Tick() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

	private:
		float mSpeed;
		float mLifeTime;
	};
}

