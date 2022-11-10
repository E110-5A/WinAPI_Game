#include "jsMonster.h"
#include "jsResources.h"
#include "jsCollider.h"
#include "jsImage.h"
#include "jsCamera.h"

namespace js
{
	Monster::Monster()
		: mImage(nullptr)
	{
		SetPos(Pos(600.f, 100.f));
		SetScale(Size(2.f, 2.f));

		Init();
	}
	Monster::Monster(Pos pos)
		: mImage(nullptr)
	{
		SetPos(pos);
		SetScale(Size(2.f, 2.f));

		Init();
	}
	Monster::~Monster()
	{
	}

	void Monster::Init()
	{
		if (nullptr == mImage)
		{
			mImage = Resources::Load<Image>
				(L"Mon", L"..\\Resources\\Image\\Enemy\\testMonster.bmp");
		}
		// 콜라이더 설정
		Collider* monCollider = new Collider();
		monCollider->SetPos(GetPos());
		monCollider->SetScale(Size(45.f, 70.f) * GetScale());
		// AddComponent(monCollider);
	}

	void Monster::Tick()
	{
		GameObject::Tick();

	}
	void Monster::Render(HDC hdc)
	{
		Pos pos = GetPos();
		Size scale = GetScale();

		Vector2 finalPos;
		finalPos.x = (pos.x - mImage->GetWidth() * (scale.x / 2.f));
		finalPos.y = (pos.y - mImage->GetHeight() * (scale.y / 2.f));

		finalPos = Camera::CalculatePos(finalPos);

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		int alpha = 225;
		BLENDFUNCTION func = {};
		func.AlphaFormat = AC_SRC_ALPHA;
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.SourceConstantAlpha = alpha;

		AlphaBlend(hdc,
			finalPos.x, finalPos.y,
			rect.x, rect.y,
			mImage->GetDC(), 0, 0,
			mImage->GetWidth(), mImage->GetHeight(), func);


		GameObject::Render(hdc);
	}
	void Monster::OnCollisionEnter(Collider* other)
	{
		// hp가 0아래면 destroy

		// 플레이어인 경우 ret

		// 투사체인 경우 -hp

		// 점프대인 경우 위로 점프
	}
	void Monster::OnCollisionStay(Collider* other)
	{
	}
	void Monster::OnCollisionExit(Collider* other)
	{
	}
}