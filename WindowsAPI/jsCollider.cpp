#include "jsCollider.h"
#include "jsGameObject.h"
#include "jsApplication.h"

namespace js
{
	Collider::Collider()
		:Component(eComponentType::Collider)
		, mOffset(Vector2::Zero)
		, mPos(Vector2::Zero)
		, mScale(Vector2::One)
	{
		SetScale(Size(50.f, 50.f));
	}
	Collider::~Collider()
	{
	}
	void Collider::Tick()
	{
		GameObject* owner = GetOwner();
		mPos = owner->GetPos() + mOffset;

	}
	void Collider::Render(HDC hdc)
	{
		HPEN green = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		Pen pen(hdc, green);

		HBRUSH tr = Application::GetInstance().GetBrush(eBrushColor::Transparent);
		Brush brush(hdc, tr);

		Rectangle(hdc, (mPos.x - mScale.x /2.f), (mPos.y - mScale.y / 2.f), 
			(mPos.x + mScale.x / 2.f), (mPos.y + mScale.y / 2.f));
	}
}