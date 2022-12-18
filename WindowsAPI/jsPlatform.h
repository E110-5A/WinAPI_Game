#pragma once
#include "jsCollisionBlock.h"

namespace js
{
	class Collider;
	class Platform : public CollisionBlock
	{
	public:
		Platform();
		Platform(Pos pos);
		~Platform();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;


	protected:
		virtual void Process(GameObject* other) override;
	};
}