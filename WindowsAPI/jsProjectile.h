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

	private:
		float m_fSpeed;
	};
}

