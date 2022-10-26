#pragma once
#include "jsEntity.h"

namespace js
{
	class Component : public Entity
	{
	public:
		Component() = delete;
		Component(eComponentType type);
		virtual ~Component();

		virtual void Tick() = 0;
		virtual void Render(HDC hdc);

	private:
		const eComponentType mType;
	};
}