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
    // 상자와 대응하는 아이템 생성
    mItemObject = object::Instantiate<ItemObject>(eColliderLayer::Item);

    // 활성화
    mActive = true;
}

void js::LargeChest::Tick()
{
    if (false == mActive)
        return;
    EventObject::Tick();
}

void js::LargeChest::Render(HDC hdc)
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
        mImage->GetWidth(), mImage->GetHeight(), func);

    EventObject::Render(hdc);
}

void js::LargeChest::OnCollisionEnter(Collider* other)
{
}

void js::LargeChest::OnCollisionStay(Collider* other)
{
    if (false == mActive)
        return;
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
    // 아이템 종류
    srand((unsigned int)time(NULL));
    int common = 0 + (rand() % 5);
    int uncommon = 5 + (rand() % 5);
    int active = 15 + (rand() % 3);

    int randomItem = (rand() % 50);
    
    // 아이템 불러오기
    if (0 <= randomItem && 20 > randomItem)                      // 0~2  common
    {
        mItemObject->Active(GetPos(), rand() % common);
    }
    else if (20 <= randomItem && 40 > randomItem)                 // 3~4  uncommon
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
