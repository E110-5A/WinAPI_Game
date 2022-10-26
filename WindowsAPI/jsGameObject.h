#pragma once
#include "jsEntity.h"

namespace js
{
	class Component;
	class GameObject :
		public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);

		void SetPos(Pos pos) { mPos = pos; }
		Pos GetPos() { return mPos; }
		void SetScale(Size scale) { mScale = scale; }
		Size GetScale() { return mScale; }

		void AddComponent(Component* component);

	private:
		std::vector<Component*> mComponents;
		Pos		mPos;
		Size	mScale;
	};
}

