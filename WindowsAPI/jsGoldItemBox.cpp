#include "jsGoldItemBox.h"

// resource
#include "jsImage.h"

// manager
#include "jsCamera.h"

// component
#include "jsCollider.h"

namespace js
{
    js::GoldItemBox::GoldItemBox()
    {
        Initialize();
    }

    js::GoldItemBox::GoldItemBox(Pos pos)
    {
        SetPos(pos);
        Initialize();
    }

    js::GoldItemBox::~GoldItemBox()
    {
    }

    void js::GoldItemBox::Initialize()
    {
        SetImage(L"GoldBox", L"..\\Resources\\Image\\Item\\GoldBox.bmp");
        mCollider->SetPos(GetPos() + Vector2(22.0f, 5.0f));
        mCollider->SetSize(Size(95.0f, 60.0f));
    }

    void js::GoldItemBox::Tick()
    {
    }

    void js::GoldItemBox::Render(HDC hdc)
    {
        Pos pos = Camera::CalculatePos(GetPos());
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

        GameObject::Render(hdc);
    }

    void js::GoldItemBox::OnCollisionEnter(Collider* other)
    {
    }

    void js::GoldItemBox::OnCollisionStay(Collider* other)
    {
    }

    void js::GoldItemBox::OnCollisionExit(Collider* other)
    {
    }
}