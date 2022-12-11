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
        // 이미지
        SetImage(L"SmallBox", L"..\\Resources\\Image\\Item\\SmallBox.bmp");
        // 충돌체
        mCollider->SetPos(GetPos());
        mCollider->SetOffset(Vector2(15.0f, 12.0f));
        mCollider->SetSize(Size(50.0f, 35.0f));
        // 이벤트
        mOnTrigger = std::bind(&SmallChest::Trigger, this);
        // 상자와 대응하는 아이템 생성
        mItemObject = object::Instantiate<ItemObject>(eColliderLayer::Item);
        
        // 활성화
        mActive = true;
    }
    void SmallChest::Tick()
    {
        if (false == mActive)
            return;
        EventObject::Tick();
    }
    void SmallChest::Render(HDC hdc)
    {
        if (false == mActive)
            return;
        Pos pos = Camera::CalculateObjectPos(GetPos());
        Size scale = GetScale();


        BLENDFUNCTION func = {};
        func.AlphaFormat = AC_SRC_ALPHA;
        func.BlendOp = AC_SRC_OVER;
        func.BlendFlags = 0;
        func.SourceConstantAlpha = 255;


        AlphaBlend(hdc,
            pos.x, pos.y,
            mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y,
            mImage->GetDC(), 0, 0,
            mImage->GetWidth() , mImage->GetHeight() , func);

        EventObject::Render(hdc);
    }

    void SmallChest::OnCollisionEnter(Collider* other)
    {
    }
    void SmallChest::OnCollisionStay(Collider* other)
    {
        if (false == mActive)
            return;
        if (KEY_DOWN(eKeyCode::A))
        {
            mOnTrigger();
        }
    }
    void SmallChest::OnCollisionExit(Collider* other)
    {
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
        if (0 <= randomItem && 30 > randomItem)                      // 0~2  common
        {
            mItemObject->Active(GetPos(), rand() % common);
        }
        else if (30 <= randomItem && 40 > randomItem)                 // 3~4  uncommon
        {
            mItemObject->Active(GetPos(), rand() % uncommon);
        }                                                           // 5    active
        else
        {
            mItemObject->Active(GetPos(), rand() % active);
        }
        // 비활성화 하기
        mActive = false;
    }
}