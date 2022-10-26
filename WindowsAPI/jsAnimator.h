#pragma once
#include "jsComponent.h"

namespace js 
{
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
	private:
	};
}

