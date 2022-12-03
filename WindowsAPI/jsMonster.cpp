#include "jsMonster.h"

// 매니저
#include "jsCamera.h"
// 리소스
#include "jsResources.h"
#include "jsImage.h"

// 컴포넌트
#include "jsCollider.h"
#include "jsAnimator.h"
#include "jsRigidbody.h"

namespace js
{
	Monster::Monster()
		: mImage(nullptr)
	{
	}
	Monster::Monster(Pos pos)
		: mImage(nullptr)
	{
	}
	Monster::~Monster()
	{
	}


	void Monster::Initialize()
	{
	}
	void Monster::Tick()
	{
	}
	void Monster::Render(HDC hdc)
	{
	}

	void Monster::Damaged()
	{
	}

	void Monster::KnockBack()
	{
	}

	void Monster::Strun()
	{
	}

	void Monster::OnCollisionEnter(Collider* other)
	{
		
	}
	void Monster::OnCollisionStay(Collider* other)
	{
	}
	void Monster::OnCollisionExit(Collider* other)
	{
	}
}