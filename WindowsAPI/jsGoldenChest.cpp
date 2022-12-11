#include "jsGoldenChest.h"

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

namespace js
{
    js::GoldenChest::GoldenChest()
    {
        Initialize();
    }

    js::GoldenChest::GoldenChest(Pos pos)
    {
        SetPos(pos);
        Initialize();
    }

    js::GoldenChest::~GoldenChest()
    {
    }

    void js::GoldenChest::Initialize()
    {
        SetImage(L"GoldBox", L"..\\Resources\\Image\\Item\\GoldBox.bmp");
        mCollider->SetPos(GetPos());
        mCollider->SetOffset(Vector2(23.0f, 10.0f));
        mCollider->SetSize(Size(80.0f, 45.0f));

        mOnTrigger = std::bind(&GoldenChest::Trigger, this);
        // ���ڿ� �����ϴ� ������ ����
        mItemObject = object::Instantiate<ItemObject>(eColliderLayer::Item);

        // Ȱ��ȭ
        mActive = true;
    }

    void js::GoldenChest::Tick()
    {
        if (false == mActive)
            return;
        EventObject::Tick();
    }

    void js::GoldenChest::Render(HDC hdc)
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

    void js::GoldenChest::OnCollisionEnter(Collider* other)
    {
    }

    void js::GoldenChest::OnCollisionStay(Collider* other)
    {
        if (false == mActive)
            return;
        if (KEY_DOWN(eKeyCode::A))
        {
            mOnTrigger();
        }
    }

    void js::GoldenChest::OnCollisionExit(Collider* other)
    {
    }
    void GoldenChest::Trigger()
    {
        // ������ ����
        srand((unsigned int)time(NULL));
        int rare = 10 + (rand() % 4);
                
        // ������ �ҷ�����
        mItemObject->Active(GetPos(), rare);
        // ��Ȱ��ȭ �ϱ�
        mActive = false;
    }
}