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
        SetImage(L"GoldBox", L"..\\Resources\\Image\\Item\\GoldBox.bmp");
        mEventCollider->SetSize(Size(80.0f, 45.0f));
        mEventCollider->SetOffset(Vector2(23.0f, 10.0f));
        // 상자와 대응하는 아이템 생성
        mItemObject = object::Instantiate<ItemObject>(eColliderLayer::EventObject);
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
    }
    void GoldenChest::OnCollisionStay(Collider* other)
    {
        Chest::OnCollisionStay(other);
    }
    void GoldenChest::OnCollisionExit(Collider* other)
    {
    }
    void GoldenChest::Trigger()
    {
        // 아이템 종류
        srand((unsigned int)time(NULL));
        int rare = 10 + (rand() % 4);

        // 아이템 불러오기
        mItemObject->Active(GetPos(), (eItemList)rare);

        // 비활성화 하기
        mAble = false;
    }
}