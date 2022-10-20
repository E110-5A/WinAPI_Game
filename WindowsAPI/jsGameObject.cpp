#include "jsGameObject.h"

namespace js
{
	jsGameObject::jsGameObject()
		: m_Pos { 0.f, 0.f }
		, m_Scale { 1.f, 1.f }
	{
	}

	jsGameObject::~jsGameObject()
	{
	}

	void jsGameObject::Initialize()
	{
	}

	void jsGameObject::Tick()
	{
	}

	void jsGameObject::Render(HDC _dc)
	{
	}
}