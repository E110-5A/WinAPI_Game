#include "jsMonster.h"
#include "jsResources.h"
#include "jsCollider.h"
#include "jsImage.h"

namespace js
{
	Monster::Monster()
		: mImage(nullptr)
	{
		SetPos(Pos(1600 / 2, 900 / 2));
		SetScale(Size(3.f, 3.f));

		if (nullptr == mImage)
		{
			mImage = Resources::Load<Image>
				(L"Mon", L"..\\Resources\\Image\\Enemy\\testMonster.bmp");
		}
		AddComponent(new Collider);
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

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;


		TransparentBlt(hdc,
			finalPos.x, finalPos.y,
			rect.x, rect.y,
			mImage->GetDC(), 0, 0,
			mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(hdc);
	}
}