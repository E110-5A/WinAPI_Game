#pragma once
#include "jsGameObject.h"

namespace js
{
	class Collider;
	class CollisionBlock : public GameObject
	{
	public:
		CollisionBlock();
		CollisionBlock(Pos pos);
		virtual ~CollisionBlock();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;


		void SetColliderSize(Size size) { mCollider->SetSize(size); }
		void SetColliderOffset(Pos pos) { mCollider->SetOffset(pos); }

	protected:
		virtual void Process(GameObject* other) {}

	protected:
		Collider* mCollider;
	};
}