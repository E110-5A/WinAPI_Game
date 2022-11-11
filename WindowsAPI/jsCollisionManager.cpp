#include "jsCollisionManager.h"
#include "jsScene.h"
#include "jsSceneManager.h"
#include "jsGameObject.h"
#include "jsCollider.h"

namespace js
{
	WORD CollisionManager::mMatrix[_COLLIDER_LAYER] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionInfo;

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
			Collider* leftCollider = leftObject->GetComponent<Collider>();
			if (nullptr == leftCollider)
				continue;

			for (auto rightObject : rights)
			{
				Collider* rightCollider = rightObject->GetComponent<Collider>();
				
				if (nullptr == rightCollider)
					continue;

				if (leftObject == rightObject)
					continue;


				ColliderCollision(leftCollider, rightCollider);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		ColliderID id;

		id.left = left->GetID();
		id.right = right->GetID();
		
		std::map<UINT64, bool>::iterator iter
			= mCollisionInfo.find(id.ID);

		// 이전에 없던 충돌정보라면 충돌정보를 생성해준다
		if (iter == mCollisionInfo.end())
		{
			mCollisionInfo.insert(std::make_pair(id.ID, false));
			iter = mCollisionInfo.find(id.ID);
		}

		if (Intersect(left, right))
			// 충돌
		{
			// 처음 충돌한 상태
			if (false == iter->second)
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);


				iter->second = true;
			}
			else
				// 충돌중인 상태
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
			// 안충돌
		{
			// 충돌에서 벗어난 상태
			if (true == iter->second)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);


				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		if (left->GetOwner()->IsDeath())
			return false;
		if (right->GetOwner()->IsDeath())
			return false;


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
	void CollisionManager::Clear()
	{
		memset(mMatrix, 0, sizeof(WORD) * _COLLIDER_LAYER);
		
		mCollisionInfo.clear();
	}
}