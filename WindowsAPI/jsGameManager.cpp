#include "jsGameManager.h"

// manager
#include "jsTime.h"
#include "jsSceneManager.h"

// scene
#include "jsScene.h"

// object
#include "jsPlayer.h"
#include "jsPlayerProjectile.h"
#include "jsMonster.h"
#include "jsChest.h"
#include "jsBossMonster.h"
#include "jsPlatform.h"
#include "jsTeleporter.h"

#include "jsCollider.h"

namespace js
{
	// ������Ʈ
	Player*				GameManager::mPlayer = nullptr;
	PlayerProjectile*	GameManager::mPlayerAttack[PLAYER_PROJECTILE_POOL] = {};
	Monster*			GameManager::mMonster[MONSTER_POOL] = {};
	Chest*				GameManager::mChest[CHEST_POOL] = {};
	BossMonster*		GameManager::mBossMonster = nullptr;
	Teleporter*			GameManager::mTeleporter = nullptr;

	Platform*			GameManager::mSpawnPlatform = nullptr;

	// ���� ����
	bool			GameManager::mPlayable = false;

	int				GameManager::mPlayerItems[(UINT)eItemList::End] = {};
	PlayerInfo*		GameManager::mPlayerInfo = nullptr;
	PlayerStat*		GameManager::mDefaultStat = nullptr;

	float*			GameManager::mDifficultyTime = nullptr;
	int*			GameManager::mDifficulty = nullptr;
	float			GameManager::mSpawnTime = 0;

	void GameManager::Initialize()
	{
		// �÷��̾� ����
		mPlayerInfo = new PlayerInfo();
		mDefaultStat = new PlayerStat();
		mDifficultyTime = new float;
		mDifficulty = new int;
		InitStat(mPlayerInfo);
		mDefaultStat = mPlayerInfo->stat;
		PlayerLevelUp();

		*mDifficultyTime = 0;
		*mDifficulty = 0;
		// ������Ʈ �Ҵ�
		InitObject();
	}
	void GameManager::InitObject()
	{
		// �÷��̾� ����
		mPlayer = new Player();
		mPlayer->SetType(eColliderLayer::Player);
		// ����ü ����
		for (int idx = 0; idx < PLAYER_PROJECTILE_POOL; ++idx)
		{			
			mPlayerAttack[idx] = new PlayerProjectile();
			mPlayerAttack[idx]->SetType(eColliderLayer::Player_Projectile);
			mPlayerAttack[idx]->SetPlayerInfo(mPlayer);
		}	
		// ���� ����
		for (int idx = 0; idx < MONSTER_POOL; ++idx)
		{			
			mMonster[idx] = new Monster();
			mMonster[idx]->SetType(eColliderLayer::Monster);
		}
		// ���� ����
		for (int idx = 0; idx < CHEST_POOL; ++idx)
		{			
			mChest[idx] = new Chest();
			mChest[idx]->SetType(eColliderLayer::Chest);
		}
		// ���� ����
		mBossMonster = new BossMonster();
		mBossMonster->SetType(eColliderLayer::Monster);
		// �ڷ����� ����
		mTeleporter = new Teleporter();
		mTeleporter->SetType(eColliderLayer::Teleporter);
	}

	void GameManager::AddObject()
	{
		Scene* scene = SceneManager::GetPlayScene();
		srand(Time::GetDeltaTime());
		// �÷��̾� �߰�
		scene->AddGameObject(mPlayer, eColliderLayer::Player);
		mPlayer->AddComponentScene();

		// ���� �÷��̾� ����ü Ǯ �߰�
		for (int idx = 0; idx < PLAYER_PROJECTILE_POOL; ++idx)
		{
			// �÷��̾� ����ü �߰�
			scene->AddGameObject(mPlayerAttack[idx], eColliderLayer::Player_Projectile);			
		}


		// ���� ���� Ǯ �߰�
		for (int idx = 0; idx < MONSTER_POOL; ++idx)
		{
			// ���� �߰�, ���� �ʱ�ȭ
			mMonster[idx]->AddMonster();
			mMonster[idx]->AddComponentScene();
		}
		// ���� ���� Ǯ �߰�
		for (int idx = 0; idx < CHEST_POOL; ++idx)
		{
			// Ÿ�� ����			
			// small 3 large 2 golden 1
			int myType = rand() % 10;       // 0 ~ 9
			// ���� �߰�, ���� �ʱ�ȭ
			mChest[idx]->AddChest(myType);
		}

		// ���� ���� �߰�
		mBossMonster->AddBoss();
		mBossMonster->AddComponentScene();

		// ���� �ڷ����� �߰�
		mTeleporter->AddTeleporter();
	}

	void GameManager::InitStat(PlayerInfo* info)
	{
		info->stat->playerHealth->maxHP = 110;
		info->stat->playerHealth->curHP = 110;
		info->stat->playerHealth->healthRegen = 0.6;
		info->stat->playerHealth->defance = 0;
		info->stat->playerOffence->damage = 12;
		info->stat->playerOffence->attackSpeed = 1;
		info->stat->playerOffence->range = 700;
		info->stat->playerUtility->moveSpeed = 1.3;
		info->stat->playerUtility->maxJumpCount = 1;
		info->stat->playerUtility->curJumpCount = 0;
		info->stat->playerUtility->jumpPower = 600;

		info->maxExp = 10;
	}
	void GameManager::Tick()
	{
		
	}
	void GameManager::PlayerLevelUp()
	{
		++mPlayerInfo->level;
		mPlayerInfo->stat->playerHealth->maxHP = (mDefaultStat->playerHealth->maxHP + (32 * mPlayerInfo->level) - 32);
		mPlayerInfo->stat->playerHealth->healthRegen = (mDefaultStat->playerHealth->healthRegen + (0.12 * mPlayerInfo->level) - 0.12);
		mPlayerInfo->stat->playerHealth->defance = (mDefaultStat->playerHealth->defance + (2 * mPlayerInfo->level) - 2);
		mPlayerInfo->stat->playerOffence->damage = (mDefaultStat->playerOffence->damage + (3 * mPlayerInfo->level) - 3);
		
		mPlayerInfo->maxExp += mPlayerInfo->maxExp / 2;
	}
	void GameManager::SpawnMonster()
	{
		srand(Time::GetDeltaTime());

		mSpawnTime += Time::GetDeltaTime();
		
		int count = 0;
		int monsterTO = 1 + (*mDifficulty) / 2;


		// (5 + ���̵�)�ʸ��� ���� ����
		if (10 + (float)(*mDifficulty) <= mSpawnTime)
		{
			// TO��ŭ ���͸� �߰���
			for (int count = 0; count < monsterTO; ++count)
			{
				// ���� Ǯ���� �����ο��� ������
				for (int idx = 0; idx < MONSTER_POOL; ++idx)
				{
					if (false == mMonster[idx]->IsAble())
					{
						// ���� ��ġ ���ϱ� // Platform Pos , Size �� �޾ƿͼ� ���� ������

						// ������ġ (X��: LT.x~ LT.x+Size.x, Y�� : LT.y - ����->Size.y

						Vector2 spawnLT = mSpawnPlatform->GetPos();
						float spawnWidth = mSpawnPlatform->GetComponent<Collider>()->GetSize().x;
						float monsterHight = mMonster[idx]->GetBodyCollider()->GetSize().y;
						float monsterWidth = mMonster[idx]->GetBodyCollider()->GetSize().x;

						float spawnPosX = spawnLT.x + (rand() % (int)spawnWidth - monsterWidth);

						// ���� ��ġ ����
						mMonster[idx]->SetPos(Vector2(spawnPosX, spawnLT.y - monsterHight));
						mMonster[idx]->Spawn(mSpawnPlatform);
						break;
					}
				}
			}
			

			// �������� �����ð� �ʱ�ȭ
			mSpawnTime = 0.0f;
		}		
	}
	void GameManager::KillBoss()
	{
		mTeleporter->BossKilled();
	}
	void GameManager::Playing()
	{
		if (false == mPlayable)
			return;

		(*mDifficultyTime) += Time::GetDeltaTime();

		// �������� ����
		if (mPlayerInfo->curExp >= mPlayerInfo->maxExp)
		{
			float overExp = mPlayerInfo->curExp - mPlayerInfo->maxExp;
			PlayerLevelUp();
			mPlayerInfo->curExp = overExp;
		}
		// ���̵� ���� ����
		if (60.0f <= *mDifficultyTime)
		{
			*mDifficulty += 1;
			*mDifficultyTime = 0.0f;
		}
		SpawnMonster();
	}
	void GameManager::PickUpItems(eItemList item)
	{
		++mPlayerItems[(UINT)item];
	}

	void GameManager::StageClear()
	{
	}
}