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
	class Monster : public Creature
	{
	public:
		Monster();
		Monster(Pos pos);
		virtual ~Monster();

		virtual void Initialize();

		void SetAnimator();

		void ImpInit();
		void ParentInit();




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
			// Ÿ�� ���ϱ�
			srand((unsigned int)time(NULL));
			// 0, 1
			int myType = rand() % 2;
			if (0 == myType)
				mMonsterType = eMonsterType::Imp;
			else if (1 == myType)
				mMonsterType = eMonsterType::Parent;
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

		eMonsterState	mState;
		Player*			mTarget;
	};
}

