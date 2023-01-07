#pragma once
#include "jsEventObject.h"
#include "jsItemObject.h"

#define ChestSizeX 46
#define ChestSizeY 32

namespace js
{
	enum class eChestType
	{
		Golden,
		Large,
		Small,
	};
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
	class Sound;
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

		// ���� �߰��� �� �������� �� ���� Ÿ���� ������
		void AddChest(int type);

		void SetGoldenChest() { SetIndex((UINT)eChestIndex::Golden); mChestType = eChestType::Golden; }
		void SetLargeChest() { SetIndex((UINT)eChestIndex::Large); mChestType = eChestType::Large; }
		void SetSmallChest() { SetIndex((UINT)eChestIndex::Small); mChestType = eChestType::Small; }

		void GoldenChestTrigger()
		{
			// ������ ����
			srand((unsigned int)time(NULL));
			int rare = 10 + (rand() % 4);

			// ������ �ҷ�����
			mItemObject->Active(GetPos(), (eItemList)rare);

			// ��Ȱ��ȭ �ϱ�
			mAble = false;
			SetIndex((UINT)eChestIndex::Golden_Open);
		}
		void LargeChestTrigger()
		{
			// ������ ����
			srand((unsigned int)time(NULL));
			// ���� �������� ���
			int randomItem = (rand() % 50);

			// ��޿� �ش��ϴ� ������
			int common = 0 + (rand() % 5);
			int uncommon = 5 + (rand() % 5);
			int active = 15 + (rand() % 3);

			// ������ �ҷ�����
			if (0 <= randomItem && 20 > randomItem)
				mItemObject->Active(GetPos(), (eItemList)(common));     // 0~2  common
			else if (20 <= randomItem && 40 > randomItem)
				mItemObject->Active(GetPos(), (eItemList)(uncommon));   // 3~4  uncommon
			else
				mItemObject->Active(GetPos(), (eItemList)(active));     // 5    active

			// ��Ȱ��ȭ �ϱ�
			mAble = false;
			SetIndex((UINT)eChestIndex::Large_Open);
		}
		void SmallChestTrigger()
		{
			// ������ ����
			srand((unsigned int)time(NULL));
			int common = 0 + (rand() % 5);
			int uncommon = 5 + (rand() % 5);
			int active = 15 + (rand() % 3);

			int randomItem = (rand() % 50);

			// ������ �ҷ�����
			if (0 <= randomItem && 30 > randomItem)
				mItemObject->Active(GetPos(), (eItemList)(common));     // 0~2  common
			else if (30 <= randomItem && 40 > randomItem)
				mItemObject->Active(GetPos(), (eItemList)(uncommon));   // 3~4  uncommon
			else
				mItemObject->Active(GetPos(), (eItemList)(active));     // 5    active

			// ��Ȱ��ȭ �ϱ�
			mAble = false;
			SetIndex((UINT)eChestIndex::Small_Open);
		}

		void SetIndex(UINT index);

	protected:
		Image*		mTextImage;
		ItemObject* mItemObject;
		bool		mCollisionPlayer;

		// ��Ʋ�� �̹��� ���� ��
		eChestIndex	mIndex;
		// �̹��� LT ��ǥ
		UINT		mX;
		UINT		mY;

	private:
		eChestType	mChestType;
		Sound*		mOpenSound;
	};
}