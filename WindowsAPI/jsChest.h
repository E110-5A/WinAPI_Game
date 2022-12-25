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

		// 씬에 추가될 때 랜덤으로 내 상자 타입이 정해짐
		void AddChest()
		{
			Scene* scene = SceneManager::GetPlayScene();

			srand((unsigned int)time(NULL));
			// small 3 large 2 golden 1
			int myType = rand() % 6;
			if (0 <= myType && 3 > myType)
				SetSmallChest();
			else if (3 <= myType < 5)
				SetLargeChest();
			else if (5 <= myType < 6)
				SetGoldenChest();

			scene->AddGameObject(this, eColliderLayer::EventObject);
			scene->AddGameObject(mItemObject, eColliderLayer::Item);
		}

		void SetGoldenChest() { SetIndex((UINT)eChestIndex::Golden); }
		void SetLargeChest() { SetIndex((UINT)eChestIndex::Large); }
		void SetSmallChest() { SetIndex((UINT)eChestIndex::Small); }

		void GoldenChestTrigger()
		{
			// 아이템 종류
			srand((unsigned int)time(NULL));
			int rare = 10 + (rand() % 4);

			// 아이템 불러오기
			mItemObject->Active(GetPos(), (eItemList)rare);

			// 비활성화 하기
			mAble = false;
			SetIndex((UINT)eChestIndex::Golden_Open);
		}
		void LargeChestTrigger()
		{
			// 아이템 종류
			srand((unsigned int)time(NULL));
			// 뽑을 아이템의 등급
			int randomItem = (rand() % 50);

			// 등급에 해당하는 아이템
			int common = 0 + (rand() % 5);
			int uncommon = 5 + (rand() % 5);
			int active = 15 + (rand() % 3);

			// 아이템 불러오기
			if (0 <= randomItem && 20 > randomItem)
				mItemObject->Active(GetPos(), (eItemList)(common));     // 0~2  common
			else if (20 <= randomItem && 40 > randomItem)
				mItemObject->Active(GetPos(), (eItemList)(uncommon));   // 3~4  uncommon
			else
				mItemObject->Active(GetPos(), (eItemList)(active));     // 5    active

			// 비활성화 하기
			mAble = false;
			SetIndex((UINT)eChestIndex::Large_Open);
		}
		void SmallChestTrigger()
		{
			// 아이템 종류
			srand((unsigned int)time(NULL));
			int common = 0 + (rand() % 5);
			int uncommon = 5 + (rand() % 5);
			int active = 15 + (rand() % 3);

			int randomItem = (rand() % 50);

			// 아이템 불러오기
			if (0 <= randomItem && 30 > randomItem)
				mItemObject->Active(GetPos(), (eItemList)(common));     // 0~2  common
			else if (30 <= randomItem && 40 > randomItem)
				mItemObject->Active(GetPos(), (eItemList)(uncommon));   // 3~4  uncommon
			else
				mItemObject->Active(GetPos(), (eItemList)(active));     // 5    active

			// 비활성화 하기
			mAble = false;
			SetIndex((UINT)eChestIndex::Small_Open);
		}

		void SetIndex(UINT index);
				
	protected:
		Image*		mTextImage;
		ItemObject* mItemObject;
		bool		mCollisionPlayer;

		// 아틀라스 이미지 설정 값
		eChestIndex	mIndex;
		// 이미지 LT 좌표
		UINT		mX;
		UINT		mY;

	private:
		eChestType mChestType;
	};
}