#include "jsSmallChest.h"

// resource
#include "jsImage.h"

// manager
#include "jsCamera.h"
#include "jsInput.h"
#include "jsTime.h"

// component
#include "jsCollider.h"

// object
#include "jsObject.h"
#include "jsItemObject.h"

namespace js
{
    SmallChest::SmallChest()
    {
        Initialize();
    }
    SmallChest::SmallChest(Pos pos)
    {
        SetPos(pos);
        Initialize();
    }
    SmallChest::~SmallChest()
    {
    }

    void SmallChest::Initialize()
    {
        Chest::Initialize();
        SetIndex((UINT)eChestIndex::Small);
    }

    void SmallChest::Tick()
    {
        Chest::Tick();
    }
    void SmallChest::Render(HDC hdc)
    {
        Chest::Render(hdc);
    }

    void SmallChest::OnCollisionEnter(Collider* other)
    {
        Chest::OnCollisionEnter(other);
    }
    void SmallChest::OnCollisionStay(Collider* other)
    {
        Chest::OnCollisionStay(other);
    }
    void SmallChest::OnCollisionExit(Collider* other)
    {
        Chest::OnCollisionExit(other);
    }

    void SmallChest::Trigger()
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
}