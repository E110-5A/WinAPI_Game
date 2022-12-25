#include "jsChest.h"

// manager
#include "jsCamera.h"
#include "jsInput.h"

// resource
#include "jsResources.h"
#include "jsImage.h"

// component
#include "jsCollider.h"

// object
#include "jsObject.h"
#include "jsItemObject.h"

namespace js
{
    Chest::Chest()
        : mItemObject(nullptr)
        , mTextImage(nullptr)
        , mCollisionPlayer(false)
        , mChestType(eChestType::Golden)
        , mIndex(eChestIndex::Golden)
        , mX(0)
        , mY(0)
    {
    }

    Chest::Chest(Pos pos)
        : mItemObject(nullptr)
        , mTextImage(nullptr)
        , mCollisionPlayer(false)
        , mIndex(eChestIndex::Golden)
        , mX(0)
        , mY(0)
    {
    }

    Chest::~Chest()
    {
    }

    void Chest::Initialize()
    {
        EventObject::Initialize();
        SetImage(L"ChestSprite", L"..\\Resources\\Image\\EventObject\\Chests.bmp");
        mTextImage = Resources::Load<Image>(L"ChestText", L"..\\Resources\\Image\\EventObject\\ChestText.bmp");
        // 상자와 대응하는 아이템 생성

        mItemObject = new ItemObject();
        mItemObject->SetType(eColliderLayer::Item);

        mEventCollider->SetSize(Size(ChestSizeX, ChestSizeY));
        mEventCollider->SetOffset(Vector2(ChestSizeX / 2, ChestSizeY / 2));
    }

    void Chest::Tick()
    {
        if (false == mAble)
            return;

        EventObject::Tick();
    }

    void Chest::Render(HDC hdc)
    {
        // ImageInfo
        Pos pos = Camera::CalculateObjectPos(GetPos());
        Size scale = GetScale();
                
        BLENDFUNCTION func = {};
        func.AlphaFormat = AC_SRC_ALPHA;
        func.BlendOp = AC_SRC_OVER;
        func.BlendFlags = 0;
        func.SourceConstantAlpha = 255;

        // CollisionText Render
        if (mCollisionPlayer && mAble)
        {
            AlphaBlend(hdc,
                pos.x - 100, pos.y - 50,
                mTextImage->GetWidth(), mTextImage->GetHeight(),
                mTextImage->GetDC(), 0, 0,
                mTextImage->GetWidth(), mTextImage->GetHeight(), func);
        }

        int chestImageX = mX * ChestSizeX;
        int chestImageY = mY * ChestSizeY;

        // Chest Render
        AlphaBlend(hdc,
            pos.x, pos.y,
            ChestSizeX, ChestSizeY,
            mImage->GetDC(), chestImageX, chestImageY,
            ChestSizeX, ChestSizeY, func);

        // Collider Render
        if (mAble)
            EventObject::Render(hdc);
    }

    void Chest::OnCollisionEnter(Collider* other)
    {
        if (eColliderLayer::Player == other->GetOwner()->GetType())
            mCollisionPlayer = true;
    }

    void Chest::OnCollisionStay(Collider* other)
    {
        if (false == mAble)
            return;

        if (eColliderLayer::Player == other->GetOwner()->GetType())
        {
            if (KEY_DOWN(eKeyCode::A))
            {
                if (eChestType::Small == mChestType)
                {
                    SmallChestTrigger();
                }
                else if (eChestType::Large == mChestType)
                {
                    LargeChestTrigger();
                }
                else if (eChestType::Golden == mChestType)
                {
                    GoldenChestTrigger();
                }
            }
        }
    }

    void Chest::OnCollisionExit(Collider* other)
    {
        if (eColliderLayer::Player == other->GetOwner()->GetType())
            mCollisionPlayer = false;
    }
    void Chest::SetIndex(UINT index)
    {
        // 인덱스 변경
        mIndex = (eChestIndex)index;

        // 이미지 LT 변경
        int maxColum = mImage->GetWidth() / ChestSizeX;
        int maxRow = mImage->GetHeight() / ChestSizeY;
        mY = index / maxColum;
        mX = index % maxColum;
    }
}