#pragma once
#include "jsGameObject.h"

namespace js
{
	class jsRain :
		public jsGameObject
	{
	public:
		jsRain();
		~jsRain();

		virtual void Tick();
		virtual void Render(HDC _hdc);
		void SetSpeed(float _fSpeed) { m_Speed = _fSpeed; }
	private:
		float m_Speed;
	};


}