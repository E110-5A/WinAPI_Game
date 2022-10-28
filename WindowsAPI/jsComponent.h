#pragma once
#include "jsEntity.h"

namespace js
{
	class GameObject;
	class Component : public Entity
	{
	public:
		friend class GameObject; // GameObject�� Component�� �˰��ֱ� ������ friend��������
		
		Component() = delete;
		Component(eComponentType type);
		virtual ~Component();

		virtual void Tick() = 0;
		virtual void Render(HDC hdc);

		GameObject* GetOwner() { return mOwner; }
	private:
		const eComponentType mType;
		GameObject* mOwner;
	};
}