#include "jsLargeChest.h"

// resource
#include "jsImage.h"

// manager
#include "jsInput.h"
#include "jsCamera.h"

// component
#include "jsCollider.h"

js::LargeChest::LargeChest()
{
	Initialize();
}

js::LargeChest::LargeChest(Pos pos)
{
	SetPos(pos);
	Initialize();
}

js::LargeChest::~LargeChest()
{
}

void js::LargeChest::Initialize()
{
	SetImage(L"LargeBox", L"..\\Resources\\Image\\Item\\LargeBox.bmp");
    mCollider->SetPos(GetPos());
    mCollider->SetOffset(Vector2(19.0f, 12.0f));
    mCollider->SetSize(Size(60.0f, 40.0f));

    mOnTrigger = std::bind(&LargeChest::Trigger, this);
}

void js::LargeChest::Tick()
{
    EventObject::Tick();
}

void js::LargeChest::Render(HDC hdc)
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
        mImage->GetWidth(), mImage->GetHeight(), func);

    EventObject::Render(hdc);
}

void js::LargeChest::OnCollisionEnter(Collider* other)
{
}

void js::LargeChest::OnCollisionStay(Collider* other)
{
    if (KEY_DOWN(eKeyCode::A))
    {
        mOnTrigger();
    }
}

void js::LargeChest::OnCollisionExit(Collider* other)
{
}

void js::LargeChest::Trigger()
{
}
