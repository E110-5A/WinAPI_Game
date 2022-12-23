#include "jsDamageObject.h"

// component
#include "jsCollider.h"

namespace js
{
	DamageObject::DamageObject()
		: mCollider(nullptr)
	{
		Initialize();
	}
	DamageObject::DamageObject(Pos pos)
		: mCollider(nullptr)
	{
		SetPos(pos);
		Initialize();
	}
	DamageObject::~DamageObject()
	{
	}


	void DamageObject::Initialize()
	{
		// �������̹Ƿ� �̹����� �ʿ����
		mCollider = AddComponent<Collider>();
		mOffence.damage = 20;
	}
	void DamageObject::Tick()
	{
		GameObject::Tick();
	}
	void DamageObject::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	void DamageObject::OnCollisionEnter(Collider* other)
	{
	}
	void DamageObject::OnCollisionStay(Collider* other)
	{
	}
	void DamageObject::OnCollisionExit(Collider* other)
	{
	}
}