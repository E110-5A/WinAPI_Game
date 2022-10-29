#include "jsCollisionManager.h"
#include "jsScene.h"
#include "jsSceneManager.h"
#include "jsGameObject.h"
#include "jsCollider.h"

namespace js
{
	WORD CollisionManager::mMatrix[_COLLIDER_LAYER] = {};

	void CollisionManager::Tick()
	{
		Scene* playScene = SceneManager::GetCurScene();

		for (size_t row = 0; row < _COLLIDER_LAYER; row++)
		{
			for (size_t col = 0; col < _COLLIDER_LAYER; col++)
			{
				if (mMatrix[row] & (1 << col))
				{
					LayerCollision(playScene, (eColliderLayer)row, (eColliderLayer)col);
				}
			}
		}
	}

	void CollisionManager::SetLayer(eColliderLayer left, eColliderLayer right, bool value)
	{
		// 더 작은 숫자가 행
		UINT row = 0;
		UINT col = 0;

		UINT iLeft = (UINT)left;
		UINT iRight = (UINT)right;

		if (iLeft < iRight)
		{
			row = iLeft;
			col = iRight;
		}
		else
		{
			row = iRight;
			col = iLeft;
		}

		if (true == value)
		{
			mMatrix[row] |= (1 << col);
		}
		else
		{
			mMatrix[row] &= ~(1 << col);
		}


	}
	void CollisionManager::LayerCollision(Scene* scene, eColliderLayer left, eColliderLayer right)
	{
		std::vector<GameObject*>& lefts = scene->GetGameObjects(left);
		std::vector<GameObject*>& rights = scene->GetGameObjects(right);

		// iterator를 사용해서 코드가 매우 길어지기 때문에 auto 사용
		for (auto leftObject : lefts)
		{
			if (nullptr == leftObject->GetComponent<Collider>())
				continue;

			for (auto rightObject : rights)
			{
				if (nullptr == rightObject->GetComponent<Collider>())
					continue;

				if (leftObject == rightObject)
					continue;

				if (Intersect(leftObject->GetComponent<Collider>(), rightObject->GetComponent<Collider>()))
				// 충돌
				{
					int a = 0;
				}
				else
				// 안충돌
				{
					int a = 0;
				}
			}
		}
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Pos leftPos = left->GetPos();
		Scale leftScale = left->GetScale();

		Pos rightPos = right->GetPos();
		Scale rightScale = right->GetScale();

		float xGap = leftPos.x - rightPos.x;
		float yGap = leftPos.y - rightPos.y;

		float xRange = leftScale.x / 2.f + rightScale.x / 2.f;
		float yRange = leftScale.y / 2.f + rightScale.y / 2.f;

		// Range 거리보다 Gap 거리가 적으면 충돌중임
		if (fabs(xGap) < fabs(xRange)
			&& fabs(yGap) < fabs(yRange))
		{
			return true;
		}
		return false;
	}
}