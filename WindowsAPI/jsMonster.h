#pragma once
#include "jsCreature.h"


#include "jsScene.h"
#include "jsSceneManager.h"



namespace js
{
	enum class eMonsterType
	{
		Imp,
		Parent,
		End,
	};

	enum class eMonsterState
	{
		Stay,
		Chase,
		Skill,
		Stun,
		Death,
	};

	class Image;
	class SceneManager;
	class Scene;
	class Platform;
	class Player;
	class MonsterAttack;
	class Monster : public Creature
	{
	public:
		Monster();
		Monster(Pos pos);
		virtual ~Monster();

		virtual void Initialize();

		void SetAnimator();
		void ReturnIdle();
		// 충돌체, 스텟
		void InitImp();
		
		// 충돌체, 스텟
		void InitParent();
		void InitSkill(float damage, float castDelay, float coolDown);

		// 게임매니저에 의해서 스폰됨
		void Spawn(Platform* spawnPlatform);


		// 부모 함수 호출
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		

		// 상태
		void Stay();
		void Chase();
		void Attack();
		void Stun();
		void Death();

		void Cooldown();
		void SkillProcess();
		void Skill();
		void DeadCheck();

		void AddMonster()
		{
			Scene* scene = SceneManager::GetPlayScene();
			// 씬에 추가
			scene->AddGameObject(this, eColliderLayer::Monster);
			scene->AddGameObject((GameObject*)mDamageObj, eColliderLayer::DamageObject);
		}

		// None
		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		// 충돌 기능
		void SelfHit(GameObject* attaker, float damage, eStagger stagger, float power);
		void SelfDamaged(float damage);
		void SelfKnockBack(float dir, eStagger stagger, float power);
		// FSM 만들때 추후 추가할 예정
		void SelfStun(float power);

	private:
		eMonsterType	mMonsterType;
		int				mEyesight;

		eMonsterState	mState;
		Player*			mTarget;


		MonsterSkillInfo*	mSkillInfo;
		MonsterAttack*	mDamageObj;


	private:
		int				mDropExp;
	};
}

