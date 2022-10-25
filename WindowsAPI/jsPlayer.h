#pragma once
#include "jsGameObject.h"

namespace js
{
	class jsImage;
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
		js::jsImage* m_Image;
	};
}

