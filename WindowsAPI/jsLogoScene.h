#pragma once
#include "jsScene.h"

namespace js
{
	class jsLogoScene :
		public jsScene
	{
	public:
		jsLogoScene();
		~jsLogoScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC _dc) override;
	};

}
