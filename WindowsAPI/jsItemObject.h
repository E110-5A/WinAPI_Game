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
		
		// ��Ʋ�� �̹��� ���� ��
		eItemList	mIndex;
		// �̹��� LT ��ǥ
		UINT		mX;
		UINT		mY;

		bool		mDrop;
		float		mDropTime;
	};
}