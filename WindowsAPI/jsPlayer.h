#pragma once
#include "jsGameObject.h"

namespace js
{
	class Image;
	class Player :
		public GameObject
	{
	public:
		Player();
		~Player();
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		float mSpeed;
		js::Image* mImage;
	};
}

