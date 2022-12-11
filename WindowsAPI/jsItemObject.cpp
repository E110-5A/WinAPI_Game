#include "jsItemObject.h"

// manager
#include "jsCamera.h"

// resource
#include "jsResources.h"
#include "jsImage.h"
// component
#include "jsCollider.h"

namespace js
{
    ItemObject::ItemObject()
        : mIndex(0)
        , mY(-1)
        , mX(-1)        
    {
        Initialize();
    }
    ItemObject::~ItemObject()
    {
    }

    void ItemObject::Initialize()
    {
        // 아이템 이미지 세팅
        SetImage(L"Items", L"..\\Resources\\Image\\Item\\Items.bmp");

        // 콜라이더 설정
        mCollider->SetPos(GetPos());
        mCollider->SetSize(Size(ITEM_SIZE / 2, ITEM_SIZE / 2));

        // 이벤트 설정
        mOnTrigger = std::bind(&ItemObject::PickUp, this);

    }
    void ItemObject::Tick()
    {
        if (false == mActive)
            return;
        EventObject::Tick();
    }
    void ItemObject::Render(HDC hdc)
    {
        if (false == mActive)
            return;
        if (nullptr == mImage)
            return;

        // 씬에서 그려질 위치
        Pos nowPos = GetPos();
        Pos renderPos = Camera::CalculateObjectPos(nowPos);

        // 아틀라스 영역에서 가져올 아이템 이미지
        int ItemImageX = mX * ITEM_SIZE;
        int ItemImageY = mY * ITEM_SIZE;

        TransparentBlt(hdc, renderPos.x, renderPos.y,
            ITEM_SIZE * TILE_SCALE, ITEM_SIZE * TILE_SCALE,
            mImage->GetDC(), ItemImageX, ItemImageY,
            ITEM_SIZE, ITEM_SIZE,
            RGB(255, 0, 255));
    }

    void ItemObject::SetIndex(UINT index)
    {
        // 인덱스 변경
        mIndex = index;

        // 이미지 LT 변경
        int maxColum = mImage->GetWidth() / ITEM_SIZE;
        int maxRow = mImage->GetHeight() / ITEM_SIZE;
        mY = index / maxColum;
        mX = index % maxColum;
    }

    void ItemObject::Active(Pos pos, int index)
    {
        // 아이탬 생성 위치
        SetPos(pos);
        // 아이템 유형 및 이미지 설정
        SetIndex(index);
        mActive = true;
    }
    void ItemObject::InActive()
    {
        // 초기화?
        mIndex = 0;
        mY = -1;
        mX = -1;

        // 내가 없어져볼게
        mActive = false;
    }
    void ItemObject::PickUp()
    {
        // 게임매니저의 아이템리스트 갱신;
        int a = 0;
        InActive();
    }
    void ItemObject::OnCollisionEnter(Collider* other)
    {
        // 플레이어만 충돌 가능 (씬에서 충돌대상 설정할것)
        if (eColliderLayer::Player != other->GetOwner()->GetType())
            return;

        mOnTrigger();
    }
    void ItemObject::OnCollisionStay(Collider* other)
    {
    }
    void ItemObject::OnCollisionExit(Collider* other)
    {
    }
}