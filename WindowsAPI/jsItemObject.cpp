#include "jsItemObject.h"

// manager
#include "jsCamera.h"
#include "jsTime.h"
#include "jsGameManager.h"

// resource
#include "jsResources.h"
#include "jsImage.h"
// component
#include "jsCollider.h"

namespace js
{
    ItemObject::ItemObject()
        : mIndex(eItemList::End)
        , mY(-1)
        , mX(-1)
        , mDrop(false)
        , mDropTime(0.f)
    {
        Initialize();
    }
    ItemObject::~ItemObject()
    {
    }

    void ItemObject::Initialize()
    {
        EventObject::Initialize();
        // ������ �̹��� ����
        SetImage(L"Items", L"..\\Resources\\Image\\EventObject\\Items.bmp");

        // �ݶ��̴� ����
        mEventCollider->SetSize(Size(ITEM_SIZE * TILE_SCALE, ITEM_SIZE * TILE_SCALE));
        mEventCollider->SetOffset(Vector2(ITEM_SIZE, ITEM_SIZE));

        // �̺�Ʈ ����
        mOnTrigger = std::bind(&ItemObject::PickUp, this);
        mAble = false;

    }
    void ItemObject::Tick()
    {
        if (false == mAble)
            return;

        if (1.0f >= mDropTime)
            mDropTime += Time::GetDeltaTime();
        if (0.8f <= mDropTime)
            mDrop = true;
        EventObject::Tick();
    }
    void ItemObject::Render(HDC hdc)
    {
        if (false == mAble)
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

    void ItemObject::SetItemIndex(UINT index)
    {
        // �ε��� ����
        mIndex = (eItemList)index;

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
        SetItemIndex((UINT)index);
        mAble = true;
    }
    void ItemObject::InActive()
    {
        // �ʱ�ȭ?
        mIndex = eItemList::End;
        mY = -1;
        mX = -1;

        // ���� ����������
        mAble = false;
        mDrop = false;
        mDropTime = 0.f;
    }
    void ItemObject::PickUp()
    {
        // ���ӸŴ����� �����۸���Ʈ ����;
        GameManager::PickUpItems(mIndex);
        InActive();
    }
    void ItemObject::OnCollisionEnter(Collider* other)
    {
        // �÷��̾ �浹 ���� (������ �浹��� �����Ұ�)
        if (eColliderLayer::Player != other->GetOwner()->GetType())
            return;

        if (true == mDrop)
            PickUp();
    }
    void ItemObject::OnCollisionStay(Collider* other)
    {
        if (eColliderLayer::Player != other->GetOwner()->GetType())
            return;
        if (true == mDrop)
            PickUp();
    }
    void ItemObject::OnCollisionExit(Collider* other)
    {
    }
}