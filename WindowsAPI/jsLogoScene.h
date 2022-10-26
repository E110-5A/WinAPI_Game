#pragma once
#include "jsScene.h"

namespace js
{
	class jsLogoScene :
		public Scene
	{
	public:
		jsLogoScene();
		~jsLogoScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC _dc) override;
	};

}
