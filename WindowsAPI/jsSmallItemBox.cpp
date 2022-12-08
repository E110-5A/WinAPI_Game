#include "jsSmallItemBox.h"

// resource
#include "jsImage.h"

// manager
#include "jsCamera.h"

// component
#include "jsCollider.h"

namespace js
{
    SmallItemBox::SmallItemBox()
    {
        Initialize();
    }
    SmallItemBox::SmallItemBox(Pos pos)
    {
        SetPos(pos);
        Initialize();
    }
    SmallItemBox::~SmallItemBox()
    {
    }
    void SmallItemBox::Initialize()
    {
        SetImage(L"SmallBox", L"..\\Resources\\Image\\Item\\SmallBox.bmp");
        mCollider->SetPos(GetPos() + Vector2(15.0f, 5.0f));
        mCollider->SetSize(Size(70.0f, 50.0f));
    }
    void SmallItemBox::Tick()
    {
    }
    void SmallItemBox::Render(HDC hdc)
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
            mImage->GetWidth() , mImage->GetHeight() , func);

        GameObject::Render(hdc);
    }
    void SmallItemBox::OnCollisionEnter(Collider* other)
    {
    }
    void SmallItemBox::OnCollisionStay(Collider* other)
    {
    }
    void SmallItemBox::OnCollisionExit(Collider* other)
    {
    }
}