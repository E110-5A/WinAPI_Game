#pragma once
#include "jsGameObject.h"

namespace js
{
	class Collider;
	class Platform : public GameObject
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


		void SetColliderSize(Size size) { mCollider->SetSize(size); }
		void SetColliderOffset(Pos pos) { mCollider->SetOffset(pos); }

	private:
		void WallProcess(GameObject* other);

	private:
		Collider* mCollider;
	};
}