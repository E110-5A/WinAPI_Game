#include "jsEventObject.h"

// Component
#include "jsCollider.h"

// Resource
#include "jsResources.h"
#include "jsImage.h"


namespace js
{
	js::EventObject::EventObject()
	{
		Initialize();
	}

	js::EventObject::~EventObject()
	{
	}

	void EventObject::Initialize()
	{
		SetScale(Vector2(2.0f, 2.0f));
		mCollider = AddComponent<Collider>();
	}

	void EventObject::Tick()
	{
		GameObject::Tick();
	}

	void EventObject::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	void EventObject::OnCollisionEnter(Collider* other)
	{
	}

	void EventObject::OnCollisionStay(Collider* other)
	{
	}

	void EventObject::OnCollisionExit(Collider* other)
	{
	}

	void EventObject::SetImage(const std::wstring& key, const std::wstring& path)
	{
		mImage = Resources::Load<Image>(key, path);
	}
	void EventObject::SetImage(const std::wstring& key)
	{
		mImage = Resources::Find<Image>(key);
	}
}

