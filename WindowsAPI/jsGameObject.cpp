#include "jsGameObject.h"
#include "jsComponent.h"

namespace js
{
	GameObject::GameObject()
		: mPos { 0.f, 0.f }
		, mScale { 1.f, 1.f }
	{
	}

	GameObject::~GameObject()
	{
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;
			delete component;
			component = nullptr;
		}
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Tick()
	{
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;
			component->Tick();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;
			component->Render(hdc);
		}
	}
	void GameObject::AddComponent(Component* component)
	{
		mComponents.push_back(component);
	}
}