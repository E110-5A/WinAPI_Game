#pragma once
#include "jsEntity.h"
#include "jsComponent.h"

namespace js
{
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

		template <typename T>
		__forceinline T* GetComponent()
		{
			T* retComp;
			for (Component* component : mComponents)
			{
				retComp = dynamic_cast<T*>(component);
				if (nullptr != retComp)
					return retComp;
			}

			return nullptr;
		}

	private:
		std::vector<Component*> mComponents;
		Pos		mPos;
		Size	mScale;
	};
}

