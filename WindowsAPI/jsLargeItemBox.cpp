#include "jsLargeItemBox.h"

// resource
#include "jsImage.h"

// manager
#include "jsCamera.h"

// component
#include "jsCollider.h"

js::LargeItemBox::LargeItemBox()
{
	Initialize();
}

js::LargeItemBox::LargeItemBox(Pos pos)
{
	SetPos(pos);
	Initialize();
}

js::LargeItemBox::~LargeItemBox()
{
}

void js::LargeItemBox::Initialize()
{
	SetImage(L"LargeBox", L"..\\Resources\\Image\\Item\\LargeBox.bmp");
    mCollider->SetPos(GetPos() + Vector2(18.0f, 5.0f));
    mCollider->SetSize(Size(80.0f, 60.0f));
}

void js::LargeItemBox::Tick()
{
}

void js::LargeItemBox::Render(HDC hdc)
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

void js::LargeItemBox::OnCollisionEnter(Collider* other)
{
}

void js::LargeItemBox::OnCollisionStay(Collider* other)
{
}

void js::LargeItemBox::OnCollisionExit(Collider* other)
{
}
