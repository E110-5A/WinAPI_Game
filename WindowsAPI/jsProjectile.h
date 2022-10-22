#pragma once
#include "jsGameObject.h"

namespace js
{

	class jsProjectile :
		public jsGameObject
	{
	public:
		jsProjectile();
		~jsProjectile();

		virtual void Tick() override;
		virtual void Render(HDC _hdc) override;

	private:
		float m_fSpeed;
	};
}

