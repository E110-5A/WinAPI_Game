#pragma once
#include "jsGameObject.h"

namespace js
{
	class jsPlayer :
		public jsGameObject
	{
	public:
		jsPlayer();
		~jsPlayer();
		virtual void Tick() override;
		virtual void Render(HDC _dc) override;

	private:
		float m_Speed;
	};
}

