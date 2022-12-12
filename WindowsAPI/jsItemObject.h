#pragma once
#include "jsEventobject.h"

namespace js
{
	class ItemObject : public EventObject
	{
	public:
		ItemObject();
		virtual ~ItemObject();
		void Initialize();
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void SetIndex(UINT index);
		void Active(Pos pos, eItemList index);
		void InActive();

		void PickUp();

	private:
		Event		mOnTrigger;

		// ��Ʋ�� �̹��� ���� ��
		eItemList	mIndex;
		// �̹��� LT ��ǥ
		UINT		mX;
		UINT		mY;

		bool		mAble;
		float		mAbleTime;
	};
}