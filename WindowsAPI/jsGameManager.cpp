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
	// 오브젝트
	Player*				GameManager::mPlayer = nullptr;
	PlayerProjectile*	GameManager::mPlayerAttack[PLAYER_PROJECTILE_POOL] = {};
	Monster*			GameManager::mMonster[MONSTER_POOL] = {};
	Chest*				GameManager::mChest[CHEST_POOL] = {};
	BossMonster*		GameManager::mBossMonster = nullptr;
	Teleporter*			GameManager::mTeleporter = nullptr;

	Platform*			GameManager::mSpawnPlatform = nullptr;

	// 게임 정보
	bool			GameManager::mPlayable = false;

	int				GameManager::mPlayerItems[(UINT)eItemList::End] = {};
	PlayerInfo*		GameManager::mPlayerInfo = nullptr;
	PlayerStat*		GameManager::mDefaultStat = nullptr;

	float*			GameManager::mDifficultyTime = nullptr;
	int*			GameManager::mDifficulty = nullptr;
	float			GameManager::mSpawnTime = 0;

	void GameManager::Initialize()
	{
		// 플레이어 설정
		mPlayerInfo = new PlayerInfo();
		mDefaultStat = new PlayerStat();
		mDifficultyTime = new float;
		mDifficulty = new int;
		InitStat(mPlayerInfo);
		mDefaultStat = mPlayerInfo->stat;
		PlayerLevelUp();

		*mDifficultyTime = 0;
		*mDifficulty = 0;
		// 오브젝트 할당
		InitObject();
	}
	void GameManager::InitObject()
	{
		// 플레이어 생성
		mPlayer = new Player();
		mPlayer->SetType(eColliderLayer::Player);
		// 투사체 생성
		for (int idx = 0; idx < PLAYER_PROJECTILE_POOL; ++idx)
		{			
			mPlayerAttack[idx] = new PlayerProjectile();
			mPlayerAttack[idx]->SetType(eColliderLayer::Player_Projectile);
			mPlayerAttack[idx]->SetPlayerInfo(mPlayer);
		}	
		// 몬스터 생성
		for (int idx = 0; idx < MONSTER_POOL; ++idx)
		{			
			mMonster[idx] = new Monster();
			mMonster[idx]->SetType(eColliderLayer::Monster);
		}
		// 상자 생성
		for (int idx = 0; idx < CHEST_POOL; ++idx)
		{			
			mChest[idx] = new Chest();
			mChest[idx]->SetType(eColliderLayer::Chest);
		}
		// 보스 생성
		mBossMonster = new BossMonster();
		mBossMonster->SetType(eColliderLayer::Monster);
		// 텔레포터 생성
		mTeleporter = new Teleporter();
		mTeleporter->SetType(eColliderLayer::Teleporter);
	}

	void GameManager::AddObject()
	{
		Scene* scene = SceneManager::GetPlayScene();
		srand(Time::GetDeltaTime());
		// 플레이어 추가
		scene->AddGameObject(mPlayer, eColliderLayer::Player);
		mPlayer->AddComponentScene();

		// 씬에 플레이어 투사체 풀 추가
		for (int idx = 0; idx < PLAYER_PROJECTILE_POOL; ++idx)
		{
			// 플레이어 투사체 추가
			scene->AddGameObject(mPlayerAttack[idx], eColliderLayer::Player_Projectile);			
		}


		// 씬에 몬스터 풀 추가
		for (int idx = 0; idx < MONSTER_POOL; ++idx)
		{
			// 몬스터 추가, 몬스터 초기화
			mMonster[idx]->AddMonster();
			mMonster[idx]->AddComponentScene();
		}
		// 씬에 상자 풀 추가
		for (int idx = 0; idx < CHEST_POOL; ++idx)
		{
			// 타입 변경			
			// small 3 large 2 golden 1
			int myType = rand() % 10;       // 0 ~ 9
			// 상자 추가, 상자 초기화
			mChest[idx]->AddChest(myType);
		}

		// 씬에 보스 추가
		mBossMonster->AddBoss();
		mBossMonster->AddComponentScene();

		// 씬에 텔레포터 추가
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


		// (5 + 난이도)초마다 몬스터 스폰
		if (10 + (float)(*mDifficulty) <= mSpawnTime)
		{
			// TO만큼 몬스터를 추가함
			for (int count = 0; count < monsterTO; ++count)
			{
				// 몬스터 풀에서 가용인원을 스폰함
				for (int idx = 0; idx < MONSTER_POOL; ++idx)
				{
					if (false == mMonster[idx]->IsAble())
					{
						// 스폰 위치 정하기 // Platform Pos , Size 값 받아와서 랜덤 돌리기

						// 스폰위치 (X값: LT.x~ LT.x+Size.x, Y값 : LT.y - 본인->Size.y

						Vector2 spawnLT = mSpawnPlatform->GetPos();
						float spawnWidth = mSpawnPlatform->GetComponent<Collider>()->GetSize().x;
						float monsterHight = mMonster[idx]->GetBodyCollider()->GetSize().y;
						float monsterWidth = mMonster[idx]->GetBodyCollider()->GetSize().x;

						float spawnPosX = spawnLT.x + (rand() % (int)spawnWidth - monsterWidth);

						// 스폰 위치 설정
						mMonster[idx]->SetPos(Vector2(spawnPosX, spawnLT.y - monsterHight));
						mMonster[idx]->Spawn(mSpawnPlatform);
						break;
					}
				}
			}
			

			// 마지막에 스폰시간 초기화
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

		// 레벨관련 로직
		if (mPlayerInfo->curExp >= mPlayerInfo->maxExp)
		{
			float overExp = mPlayerInfo->curExp - mPlayerInfo->maxExp;
			PlayerLevelUp();
			mPlayerInfo->curExp = overExp;
		}
		// 난이도 관련 로직
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