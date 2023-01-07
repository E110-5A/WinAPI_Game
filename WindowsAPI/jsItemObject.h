#pragma once
#include "jsEventobject.h"

namespace js
{
	class Sound;
	class ItemObject : public EventObject
	{
	public:
		ItemObject();
		virtual ~ItemObject();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void SetItemIndex(UINT index);

		void Active(Pos pos, eItemList index);
		void InActive();

		void PickUp();

	private:
		Sound*		mPickupSound;
		
		Event		mOnTrigger;
		
		// 아틀라스 이미지 설정 값
		eItemList	mIndex;
		// 이미지 LT 좌표
		UINT		mX;
		UINT		mY;

		bool		mDrop;
		float		mDropTime;
	};
}