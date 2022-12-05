#include "jsImp.h"

// 매니저
#include "jsInput.h"

// 리소스
#include "jsResources.h"
#include "jsImage.h"

// 컴포넌트
#include "jsAnimator.h"
#include "jsCollider.h"
#include "jsRigidbody.h"

namespace js
{
    Imp::Imp()
    {
        SetPos(Vector2(600.0f, 400.0f));
        SetScale(Vector2::One);
        SetDir(Vector2::Right);
        Initialize();
    }
    Imp::Imp(Pos pos)
    {
        SetPos(pos);
        SetScale(Vector2::One * 2);
        SetDir(Vector2::Right);
        Initialize();
    }
    Imp::~Imp()
    {
    }

    void Imp::Initialize()
    {
        Monster::Initialize();
        // 애니메이션 스프라이트 불러오기
        if (nullptr == GetImage())
        {
            SetImage(Resources::Load<Image>
                (L"Imp", L"..\\Resources\\Image\\Enemy\\imp.bmp"));
        }   
        InitAnimator();
        InitCollider();
        InitRigidbody();
        InitStat();
		mAnimator->Play(L"ImpIdleL");
    }
    void Imp::InitCollider()
    {
        mCollider = AddComponent<Collider>();
        mCollider->SetPos(GetPos());
        mCollider->SetSize(Size(20.f,25.f)* GetScale());
        mCollider->SetOffset(Vector2(8.f, 13.f));
    }
    void Imp::InitAnimator()
    {
        
        Image* image = GetImage();

        mAnimator = AddComponent<Animator>();

        mAnimator->CreateAnimation(L"ImpIdleR", image, Pos(0.f, 0.f), Size(17.f, 21.f)
            , Vector2(0.f, 0.f), 1, 0.1f);
        mAnimator->CreateAnimation(L"ImpIdleL", image, Pos(0.f, 21.f), Size(17.f, 21.f)
            , Vector2(0.f, 0.f), 1, 0.1f);

        mAnimator->CreateAnimation(L"ImpMoveR", image, Pos(0.f, 42.f), Size(18.0f, 25.f)
            , Vector2(0.f, 0.f), 6, 0.1f);
        mAnimator->CreateAnimation(L"ImpMoveL", image, Pos(0.f, 67.f), Size(18.0f, 25.f)
            , Vector2(0.f, 0.f), 6, 0.1f);

        mAnimator->CreateAnimation(L"ImpTeleportR", image, Pos(0.f, 92.f), Size(17.f, 21.f)
            , Vector2(0.f, 0.f), 3, 0.1f);
        mAnimator->CreateAnimation(L"ImpTeleportL", image, Pos(0.f, 113.f), Size(17.f, 21.f)
            , Vector2(0.f, 0.f), 3, 0.1f);

        mAnimator->CreateAnimation(L"ImpAttackR", image, Pos(0.f, 134.f), Size(33.f, 21.f)
            , Vector2(-7.f, 0.f), 11, 0.1f);
        mAnimator->CreateAnimation(L"ImpAttackL", image, Pos(0.f, 155.f), Size(33.f, 21.f)
            , Vector2(-10.f, 0.f), 11, 0.1f);

        mAnimator->CreateAnimation(L"ImpDeathR", image, Pos(0.f, 176.f), Size(26.0f, 21.f)
            , Vector2(-5.f, 0.f), 8, 0.1f);
        mAnimator->CreateAnimation(L"ImpDeathL", image, Pos(0.f, 197.f), Size(26.0f, 21.f)
            , Vector2(-5.f, 0.f), 8, 0.1f);

    }
    void Imp::InitRigidbody()
    {
        mRigidbody = AddComponent<Rigidbody>();
    }
    void Imp::InitStat()
    {
        SetMaxHp(310.0f);
        SetCurHp(310.0f);
        SetDef(0.0f);
        SetMoveSpeed(16.0f);
        SetAtt(13.0f);
    }

    void Imp::Tick()
    {
        GameObject::Tick();

        // 에니메이션 테스트용
		if (KEY_DOWN(eKeyCode::L))
		{
			mAnimator->Play(L"ImpMoveR");
            SetDir(Vector2::Right);
		}
		if (KEY_DOWN(eKeyCode::J))
		{
			mAnimator->Play(L"ImpMoveL");
            SetDir(Vector2::Left);
		}
		if (KEY_DOWN(eKeyCode::U))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ImpTeleportR", false);
			else
				mAnimator->Play(L"ImpTeleportL", false);
		}
		if (KEY_DOWN(eKeyCode::O))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ImpAttackR", false);
			else
				mAnimator->Play(L"ImpAttackL", false);
		}
		if (KEY_DOWN(eKeyCode::P))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ImpDeathR", false);
			else
				mAnimator->Play(L"ImpDeathL", false);
		}
		if (KEY_UP(eKeyCode::L))
		{
			mAnimator->Play(L"ImpIdleR");
		}
		if (KEY_UP(eKeyCode::J))
		{
			mAnimator->Play(L"ImpIdleL");
		}
    }
    void Imp::Render(HDC hdc)
    {
        GameObject::Render(hdc);
    }
    void Imp::OnCollisionEnter(Collider* other)
    {
    }
    void Imp::OnCollisionStay(Collider* other)
    {
    }
    void Imp::OnCollisionExit(Collider* other)
    {
    }
}