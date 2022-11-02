#pragma once
#include "Common.h"

namespace js
{
	class Scene;
	class Collider;
	class CollisionManager
	{
	public:
		static void Tick();
		static void SetLayer(eColliderLayer left, eColliderLayer right, bool value);

		// 레이어간 충돌 확인
		static void LayerCollision(Scene* scene, eColliderLayer left, eColliderLayer right);
		// 충돌체간 충돌 확인
		static void ColliderCollision(Collider* left, Collider* right);


		static bool Intersect(Collider* left, Collider* right);

	private:
		static WORD mMatrix[_COLLIDER_LAYER];
		static std::map<UINT64, bool> mCollisionInfo;
	};
}