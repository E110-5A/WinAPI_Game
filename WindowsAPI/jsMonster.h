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
	class Monster : public Creature
	{
	public:
		Monster();
		Monster(Pos pos);
		virtual ~Monster();

		virtual void Initialize();

		void SetAnimator();

		// �浹ü, ����
		void ImpInit();
		
		// �浹ü, ����
		void ParentInit();

		// ���ӸŴ����� ���ؼ� ������
		void Spawn(Platform* spawnPlatform);

		void ReturnIdle();

		// �θ� �Լ� ȣ��
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		

		// ����
		void Stay();
		void Chase();
		void Skill();
		void Stun();
		void Death();

		void AddMonster()
		{
			Scene* scene = SceneManager::GetPlayScene();
			// ���� �߰�
			scene->AddGameObject(this, eColliderLayer::Monster);
		}

		// ������ ���




		// None
		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		// �浹 ���
		void SelfHit(GameObject* attaker, float damage, eStagger stagger, float power);
		void SelfDamaged(float damage);
		void SelfKnockBack(float dir, eStagger stagger, float power);
		// FSM ���鶧 ���� �߰��� ����
		void SelfStun(float power);

	private:
		eMonsterType	mMonsterType;
		int				mEyesight;

		eMonsterState	mState;
		Player*			mTarget;
	};
}

