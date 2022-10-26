#pragma once
#include "jsGameObject.h"

namespace js
{
	class jsRain :
		public GameObject
	{
	public:
		jsRain();
		~jsRain();

		virtual void Tick();
		virtual void Render(HDC _hdc);
		void SetSpeed(float _fSpeed) { m_Speed = _fSpeed; }
		void SetRGB(int _R, int _G, int _B) { R = _R, G = _G, B = _B; }
	private:
		float m_Speed;
		int R;
		int G;
		int B;
	};


}