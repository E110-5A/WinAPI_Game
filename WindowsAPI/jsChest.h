#pragma once
#include "jsEventObject.h"

#define ChestSizeX 46
#define ChestSizeY 32

namespace js
{
	enum class eChestIndex
	{
		Golden,
		Golden_Open,
		Large,
		Large_Open,
		Small,
		Small_Open,
	};
	class Image;
	class ItemObject;
	class Chest : public EventObject
	{
	public:
		Chest();
		Chest(Pos pos);
		virtual ~Chest();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void SetIndex(UINT index);

		virtual void Trigger() {}
		
	protected:
		Image*		mTextImage;
		ItemObject* mItemObject;
		bool		mCollisionPlayer;

		// ��Ʋ�� �̹��� ���� ��
		eChestIndex	mIndex;
		// �̹��� LT ��ǥ
		UINT		mX;
		UINT		mY;
	};
}