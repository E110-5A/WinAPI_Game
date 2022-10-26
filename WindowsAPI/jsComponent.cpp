#include "jsComponent.h"

namespace js
{
	Component::Component(eComponentType type)
		: mType(type)
	{
	}
	Component::~Component()
	{
	}
	void Component::Render(HDC hdc)
	{
	}
}