#pragma once
#include "jsComponent.h"

namespace js
{
	class Collider :
		public Component
	{
	public:
		Collider();
		~Collider();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:

	};

}
