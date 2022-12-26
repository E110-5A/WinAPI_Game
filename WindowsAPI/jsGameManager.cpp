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


namespace js
{
	// 오브젝트
	Player*				GameManager::mPlayer = nullptr;
	PlayerProjectile*	GameManager::mPlayerAttack[PLAYER_PROJECTILE_POOL] = {};
	Monster*			GameManager::mMonster[MONSTER_POOL] = {};
	Chest*				GameManager::mChest[CHEST_POOL] = {};
	BossMonster*		GameManager::mBossMonster = nullptr;

	// 게임 정보
	bool		GameManager::mPlayable = false;

	int			GameManager::mPlayerItems[(UINT)eItemList::End] = {};
	PlayerInfo*	GameManager::mPlayerInfo = nullptr;
	PlayerStat*	GameManager::mDefaultStat = nullptr;

	float*		GameManager::mDifficultyTime = nullptr;
	int*		GameManager::mDifficulty = nullptr;


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

		// 오브젝트 할당
		InitObject();
	}
	void GameManager::InitObject()
	{
		// 플레이어 생성
		mPlayer = new Player();
		mPlayer->SetType(eColliderLayer::Player);

		for (int idx = 0; idx < PLAYER_PROJECTILE_POOL; ++idx)
		{
			// 투사체 생성
			mPlayerAttack[idx] = new PlayerProjectile();
			mPlayerAttack[idx]->SetType(eColliderLayer::Player_Projectile);
			mPlayerAttack[idx]->SetPlayerInfo(mPlayer);
		}		
		for (int idx = 0; idx < MONSTER_POOL; ++idx)
		{
			// 몬스터 생성
			mMonster[idx] = new Monster();
			mMonster[idx]->SetType(eColliderLayer::Monster);
		}
		for (int idx = 0; idx < CHEST_POOL; ++idx)
		{
			// 상자 생성
			mChest[idx] = new Chest();
			mChest[idx]->SetType(eColliderLayer::Chest);
		}
	}

	void GameManager::AddObject()
	{
		Scene* scene = SceneManager::GetPlayScene();

		// 플레이어 추가
		scene->AddGameObject(mPlayer, eColliderLayer::Player);
		mPlayer->AddComponentScene();

		for (int idx = 0; idx < PLAYER_PROJECTILE_POOL; ++idx)
		{
			// 플레이어 투사체 추가
			scene->AddGameObject(mPlayerAttack[idx], eColliderLayer::Player_Projectile);			
		}

		for (int idx = 0; idx < MONSTER_POOL; ++idx)
		{
			// 몬스터 추가, 몬스터 초기화
			mMonster[idx]->AddMonster();
			mMonster[idx]->AddComponentScene();
		}

		for (int idx = 0; idx < CHEST_POOL; ++idx)
		{
			// 상자 추가, 상자 초기화
			mChest[idx]->AddChest();

		}
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
	void GameManager::Playing()
	{
		if (true == mPlayable)
		{
			*mDifficultyTime += Time::GetDeltaTime();
		}

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
	}
	void GameManager::PickUpItems(eItemList item)
	{
		++mPlayerItems[(UINT)item];
	}

	void GameManager::StageClear()
	{
	}
}