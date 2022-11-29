#include "jsCollider.h"
#include "jsGameObject.h"
#include "jsApplication.h"
#include "jsCamera.h"
namespace js
{
	Collider::Collider()
		:Component(eComponentType::Collider)
		, mOffset(Vector2::Zero)
		, mPos(Vector2::Zero)
		, mSize(Vector2::One)
	{
		SetSize(Size(50.f, 50.f));
	}
	Collider::~Collider()
	{
	}
	void Collider::Tick()
	{
		GameObject* owner = GetOwner();
		if (owner->IsDeath())
			return;
		mPos = owner->GetPos() + mOffset;
	}
	void Collider::Render(HDC hdc)
	{
		GameObject* owner = GetOwner();
		if (owner->IsDeath())
			return;


		HPEN green = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN red = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN prevPen = NULL;

		HBRUSH tr = Application::GetInstance().GetBrush(eBrushColor::Transparent);
		Brush brush(hdc, tr);

		if (0 < mCollisionCount)
			prevPen = (HPEN)SelectObject(hdc, red);
		else
			prevPen = (HPEN)SelectObject(hdc, green);
		
		mPos = Camera::CalculatePos(mPos);

		Rectangle(hdc, (mPos.x - mSize.x / 2.f), (mPos.y - mSize.y / 2.f),
			(mPos.x + mSize.x / 2.f), (mPos.y + mSize.y / 2.f));
		
		SelectObject(hdc, prevPen);
		DeleteObject(red);
		DeleteObject(green);

	}


	void Collider::OnCollisionEnter(Collider* other)
	{
		++mCollisionCount;
		GetOwner()->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);

	}
	void Collider::OnCollisionExit(Collider* other)
	{
		--mCollisionCount;
		GetOwner()->OnCollisionExit(other);

	}
}