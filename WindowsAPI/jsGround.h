#pragma once
#include "jsGameObject.h"

namespace js
{
	class Ground : public GameObject
	{
	public:
		Ground();
		Ground(Pos pos);
		~Ground();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;
	private:

	};
}