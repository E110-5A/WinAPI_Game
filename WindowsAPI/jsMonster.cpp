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
		SetScale(Size(3.f, 3.f));

		if (nullptr == mImage)
		{
			mImage = Resources::Load<Image>
				(L"Mon", L"..\\Resources\\Image\\Enemy\\testMonster.bmp");
		}
		Collider* collMon = new Collider;
		collMon->SetScale(Size(100.f, 100.f));
		AddComponent(collMon);
	}
	Monster::~Monster()
	{
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

		//TransparentBlt(hdc,
		//	finalPos.x, finalPos.y,
		//	rect.x, rect.y,
		//	mImage->GetDC(), 0, 0,
		//	mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(hdc);
	}
	void Monster::OnCollisionEnter(Collider* other)
	{
		this->Death();
	}
	void Monster::OnCollisionStay(Collider* other)
	{
	}
	void Monster::OnCollisionExit(Collider* other)
	{
	}
}