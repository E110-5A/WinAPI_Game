#include "jsLargeChest.h"

// resource
#include "jsImage.h"

// manager
#include "jsInput.h"
#include "jsCamera.h"
#include "jsTime.h"
// component
#include "jsCollider.h"

// object
#include "jsObject.h"
#include "jsItemObject.h"

namespace js
{
    LargeChest::LargeChest()
    {
        Initialize();
    }
    LargeChest::LargeChest(Pos pos)
    {
        SetPos(pos);
        Initialize();
    }
    LargeChest::~LargeChest()
    {
    }

    void LargeChest::Initialize()
    {
        Chest::Initialize();
        SetIndex((UINT)eChestIndex::Large);
    }

    void LargeChest::Tick()
    {
        Chest::Tick();
    }
    void LargeChest::Render(HDC hdc)
    {
        Chest::Render(hdc);
    }

    void LargeChest::OnCollisionEnter(Collider* other)
    {
        Chest::OnCollisionEnter(other);
    }
    void LargeChest::OnCollisionStay(Collider* other)
    {
        Chest::OnCollisionStay(other);
    }
    void LargeChest::OnCollisionExit(Collider* other)
    {
        Chest::OnCollisionExit(other);
    }

    void LargeChest::Trigger()
    {
        // ������ ����
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
}