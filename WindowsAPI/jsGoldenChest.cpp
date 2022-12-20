#include "jsGoldenChest.h"

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
    GoldenChest::GoldenChest()
    {
        Initialize();
    }

    GoldenChest::GoldenChest(Pos pos)
    {
        SetPos(pos);
        Initialize();
    }

    GoldenChest::~GoldenChest()
    {
    }

    void GoldenChest::Initialize()
    {
        Chest::Initialize();
        SetIndex((UINT)eChestIndex::Golden);
    }

    void GoldenChest::Tick()
    {
        Chest::Tick();
    }

    void GoldenChest::Render(HDC hdc)
    {
        Chest::Render(hdc);
    }

    void GoldenChest::OnCollisionEnter(Collider* other)
    {
        Chest::OnCollisionEnter(other);
    }
    void GoldenChest::OnCollisionStay(Collider* other)
    {
        Chest::OnCollisionStay(other);
    }
    void GoldenChest::OnCollisionExit(Collider* other)
    {
        Chest::OnCollisionExit(other);
    }
    void GoldenChest::Trigger()
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
}