#pragma once
#include "jsComponent.h"

namespace js
{
	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);


		void SetOffset(Vector2 offset) { mOffset = offset; }
		void SetPos(Pos pos) { mPos = pos; }
		void SetScale(Scale scale) { mScale = scale; }

		Vector2 GetOffset() { return mOffset; }
		Pos GetPos() { return mPos; }
		Scale GetScale() { return mScale; }


	private:
		Vector2 mOffset;
		Pos mPos;
		Scale mScale;

		size_t mCollisionCount;
	};

}
