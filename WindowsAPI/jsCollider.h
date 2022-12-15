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
		void SetSize(Size size) { mSize = size; }

		Vector2 GetOffset() { return mOffset; }
		Pos GetPos() { return mPos; }
		Size GetSize() { return mSize; }

	private:
		Vector2 mOffset;
		Pos mPos;
		Size mSize;

		size_t mCollisionCount;
	};

}
