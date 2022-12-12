#include "jsItemObject.h"

// manager
#include "jsCamera.h"
#include "jsTime.h"
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
        , mAble(false)
        , mAbleTime(0.f)
    {
        Initialize();
    }
    ItemObject::~ItemObject()
    {
    }

    void ItemObject::Initialize()
    {        
        // ������ �̹��� ����
        SetImage(L"Items", L"..\\Resources\\Image\\Item\\Items.bmp");

        // �ݶ��̴� ����
        mCollider->SetPos(GetPos());
        mCollider->SetSize(Size(ITEM_SIZE * TILE_SCALE, ITEM_SIZE * TILE_SCALE));
        mCollider->SetOffset(Vector2(ITEM_SIZE, ITEM_SIZE));
        // �̺�Ʈ ����
        mOnTrigger = std::bind(&ItemObject::PickUp, this);

    }
    void ItemObject::Tick()
    {
        if (false == mActive)
            return;
        if (0.5f >= mAbleTime)
            mAbleTime += Time::GetDeltaTime();
        if (0.4f <= mAbleTime)
            mAble = true;
        EventObject::Tick();
    }
    void ItemObject::Render(HDC hdc)
    {
        if (false == mActive)
            return;
        if (nullptr == mImage)
            return;

        // ������ �׷��� ��ġ
        Pos nowPos = GetPos();
        Pos renderPos = Camera::CalculateObjectPos(nowPos);

        // ��Ʋ�� �������� ������ ������ �̹���
        int ItemImageX = mX * ITEM_SIZE;
        int ItemImageY = mY * ITEM_SIZE;

        TransparentBlt(hdc, renderPos.x, renderPos.y,
            ITEM_SIZE * TILE_SCALE, ITEM_SIZE * TILE_SCALE,
            mImage->GetDC(), ItemImageX, ItemImageY,
            ITEM_SIZE, ITEM_SIZE,
            RGB(255, 0, 255));

        EventObject::Render(hdc);
    }

    void ItemObject::SetIndex(UINT index)
    {
        // �ε��� ����
        mIndex = index;

        // �̹��� LT ����
        int maxColum = mImage->GetWidth() / ITEM_SIZE;
        int maxRow = mImage->GetHeight() / ITEM_SIZE;
        mY = index / maxColum;
        mX = index % maxColum;
    }

    void ItemObject::Active(Pos pos, eItemList index)
    {
        
        // ������ ���� ��ġ
        SetPos(pos + Vector2(-10.f,-30.0f));
        // ������ ���� �� �̹��� ����
        SetIndex((UINT)index);
        mActive = true;
    }
    void ItemObject::InActive()
    {
        // �ʱ�ȭ?
        mIndex = 0;
        mY = -1;
        mX = -1;

        // ���� ����������
        mActive = false;
        mAble = false;
        mAbleTime = 0.f;
    }
    void ItemObject::PickUp()
    {
        // ���ӸŴ����� �����۸���Ʈ ����;
        int a = 0;
        InActive();
    }
    void ItemObject::OnCollisionEnter(Collider* other)
    {
        // �÷��̾ �浹 ���� (������ �浹��� �����Ұ�)
        if (eColliderLayer::Player != other->GetOwner()->GetType())
            return;

        if (true == mAble)
            PickUp();
    }
    void ItemObject::OnCollisionStay(Collider* other)
    {
        if (eColliderLayer::Player != other->GetOwner()->GetType())
            return;
        if (true == mAble)
            PickUp();
    }
    void ItemObject::OnCollisionExit(Collider* other)
    {
    }
}