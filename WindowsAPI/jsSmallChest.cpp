#include "jsSmallChest.h"

// resource
#include "jsImage.h"

// manager
#include "jsCamera.h"
#include "jsInput.h"

// component
#include "jsCollider.h"

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
        SetImage(L"SmallBox", L"..\\Resources\\Image\\Item\\SmallBox.bmp");
        mCollider->SetPos(GetPos());
        mCollider->SetOffset(Vector2(15.0f, 12.0f));
        mCollider->SetSize(Size(50.0f, 35.0f));

        mOnTrigger = std::bind(&SmallChest::Trigger, this);
    }
    void SmallChest::Tick()
    {
        EventObject::Tick();
    }
    void SmallChest::Render(HDC hdc)
    {
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

    }
}