#pragma once
#include "jsEntity.h"
#include "jsComponent.h"

namespace js
{
	class Collider;
	class GameObject : public Entity
	{
	public:
		GameObject();
		GameObject(Pos pos);
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetPos(Pos pos) { mPos = pos; }
		Pos GetPos() { return mPos; }
		
		void SetScale(Size scale) { mScale = scale; }
		Size GetScale() { return mScale; }

		void SetDir(Vector2 dir) { mDir = dir; }
		Vector2 GetDir() { return mDir; }



		void Death() { mDead = true; }
		bool IsDeath() { return mDead; }
		void SetDeath(float time);
		void DeathLoop();

		void AddComponent(Component* component);
		template <typename T>
		__forceinline T* AddComponent()
		{
			T* component = new T();
			GameObject::AddComponent(component);
			return component;
		}
		
		
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
		Vector2 mDir;

		bool	mDead;
		float	mDeathTime;
		bool	mBeDeath;
	};
}

