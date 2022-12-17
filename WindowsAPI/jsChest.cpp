#include "jsChest.h"

// manager
#include "jsCamera.h"
#include "jsInput.h"

// resource
#include "jsImage.h"

// component
#include "jsCollider.h"

// object
#include "jsObject.h"
#include "jsItemObject.h"

namespace js
{
    Chest::Chest()
        : mItemObject(nullptr)
    {
    }

    Chest::Chest(Pos pos)
        : mItemObject(nullptr)
    {
    }

    Chest::~Chest()
    {
    }

    void Chest::Initialize()
    {
        EventObject::Initialize();
        
        // 상자와 대응하는 아이템 생성
        mItemObject = object::Instantiate<ItemObject>(eColliderLayer::EventObject);
    }

    void Chest::Tick()
    {
        if (false == mAble)
            return;

        EventObject::Tick();
    }

    void Chest::Render(HDC hdc)
    {
        if (false == mAble)
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
            mImage->GetWidth(), mImage->GetHeight(), func);

        EventObject::Render(hdc);
    }

    void Chest::OnCollisionEnter(Collider* other)
    {
    }

    void Chest::OnCollisionStay(Collider* other)
    {
        if (false == mAble)
            return;

        if (KEY_DOWN(eKeyCode::A))
            Trigger();
    }

    void Chest::OnCollisionExit(Collider* other)
    {
    }
}