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
        // ������ �̹��� ����
        SetImage(L"Items", L"..\\Resources\\Image\\Item\\Items.bmp");

        // �ݶ��̴� ����
        mCollider->SetPos(GetPos());
        mCollider->SetSize(Size(ITEM_SIZE / 2, ITEM_SIZE / 2));

        // �̺�Ʈ ����
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

    void ItemObject::Active(Pos pos, int index)
    {
        // ������ ���� ��ġ
        SetPos(pos);
        // ������ ���� �� �̹��� ����
        SetIndex(index);
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

        mOnTrigger();
    }
    void ItemObject::OnCollisionStay(Collider* other)
    {
    }
    void ItemObject::OnCollisionExit(Collider* other)
    {
    }
}