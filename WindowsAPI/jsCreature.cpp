#include "jsCreature.h"

// component
#include "jsCollider.h"
#include "jsAnimator.h"
#include "jsRigidbody.h"

// object
#include "jsObject.h"
#include "jsFoot.h"
#include "jsHead.h"

namespace js
{
	Creature::Creature()
		: mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mHeadCollider(nullptr)
		, mBodyCollider(nullptr)
		, mFootCollider(nullptr)
		, mHealthStat{}
		, mOffenceStat{}
		, mUtilityStat{}
		, mResistance{}
		, mFootObject(nullptr)
		, mHeadObject(nullptr)
		, mSpriteImage(nullptr)
	{
	}
	Creature::Creature(Pos pos)
		: mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mHeadCollider(nullptr)
		, mBodyCollider(nullptr)
		, mFootCollider(nullptr)
		, mHealthStat{}
		, mOffenceStat{}
		, mUtilityStat{}
		, mResistance{}
		, mFootObject(nullptr)
		, mHeadObject(nullptr)
		, mSpriteImage(nullptr)
	{
	}
	Creature::~Creature()
	{
	}

	void Creature::Initialize()
	{
		InitComponent();
	}

	void Creature::Tick()
	{
		GameObject::Tick();
		mFootObject->Tick();
		mHeadObject->Tick();
	}
	void Creature::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		mFootObject->Render(hdc);
		mHeadObject->Render(hdc);
	}

	void Creature::OnCollisionEnter(Collider* other)
	{
	}
	void Creature::OnCollisionStay(Collider* other)
	{
	}
	void Creature::OnCollisionExit(Collider* other)
	{
	}

	void Creature::InitComponent()
	{
		mAnimator = AddComponent<Animator>();
		mRigidbody = AddComponent<Rigidbody>();

		// body
		mBodyCollider = AddComponent<Collider>();
		// foot
		mFootObject = new Foot();
		mFootObject->SetType(eColliderLayer::Foot);
		mFootObject->SetOwner(this);
		mFootCollider = mFootObject->GetComponent<Collider>();
		// head
		mHeadObject = new Head();
		mHeadObject->SetType(eColliderLayer::Head);
		mHeadObject->SetOwner(this);
		mHeadCollider = mHeadObject->GetComponent<Collider>();
	}

	void Creature::AddComponentScene()
	{
		Scene* scene = SceneManager::GetPlayScene();
		scene->AddGameObject(mFootObject, eColliderLayer::Foot);
		scene->AddGameObject(mHeadObject, eColliderLayer::Head);
	}

	void Creature::BodyCollision(GameObject* other)
	{
		// 벽과 나의 위치 구하기
		Vector2 targetPos = other->GetPos();
		Vector2 myPos = GetPos();

		// 상대적인 벽 방향 찾기
		Vector2 wallLocationDir = myPos - targetPos;
		if (0 < wallLocationDir.x)					// x가 양수일 경우 벽위치는 내 왼쪽
			wallLocationDir = Vector2::Left;
		else
			wallLocationDir = Vector2::Right;

		// 벽을 향할 경우 x 속력을 0으로 만들기
		if (wallLocationDir == mDir)
		{
			mRigidbody->EraseVelocity(wallLocationDir, mRigidbody->GetVelocity());
		}
	}

	void Creature::SelfHit(GameObject* attaker, float damage, eStagger stagger, float power)
	{
		SelfDamaged(damage);
		SelfKnockBack(attaker->GetDir().x, stagger, power);
	}
	void Creature::SelfDamaged(float damage)
	{
		// 방어력 계산해서 피 까기
		float finalDamage = damage - mHealthStat->defance;

		// 최소 피해량
		if (1 > damage - mHealthStat->defance)
			finalDamage = 1;

		mHealthStat->curHP -= finalDamage;
	}
	void Creature::SelfKnockBack(float dir, eStagger stagger, float power)
	{
		// 저항력이 관통력보다 낮은 경우
		if (stagger >= mResistance)		// 관통이 0이고 저항력이 0이면 넉백
		{
			// 넉백
			Vector2 knockBack = mRigidbody->GetVelocity();
			knockBack.x = dir * power * 2.5f;
			mRigidbody->SetVelocity(knockBack);

			// 관통력이 쌔면 기절
			if (eStagger::Heave == stagger)
				SelfStun(power);
		}
	}
	// 미완
	void Creature::SelfStun(float power)
	{
	}
}