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

        SetImage(L"LargeBox", L"..\\Resources\\Image\\Item\\LargeBox.bmp");
        mEventCollider->SetSize(Size(60.0f, 40.0f));
        mEventCollider->SetOffset(Vector2(19.0f, 12.0f));
        // 상자와 대응하는 아이템 생성
        mItemObject = object::Instantiate<ItemObject>(eColliderLayer::EventObject);
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
    }
    void LargeChest::OnCollisionStay(Collider* other)
    {
        Chest::OnCollisionStay(other);
    }
    void LargeChest::OnCollisionExit(Collider* other)
    {
    }

    void LargeChest::Trigger()
    {
        // 아이템 종류
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
    }
}