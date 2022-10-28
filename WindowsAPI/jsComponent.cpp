#include "jsComponent.h"

namespace js
{
	Component::Component(eComponentType type)
		: mType(type)
		, mOwner(nullptr)
	{
	}
	Component::~Component()
	{
	}
	void Component::Render(HDC hdc)
	{
	}
}