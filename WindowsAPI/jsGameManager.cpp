#include "jsGameManager.h"

// manager
#include "jsTime.h"
#include "jsSceneManager.h"

// scene
#include "jsScene.h"

// object
#include "jsPlayer.h"
#include "jsPlayerProjectile.h"

namespace js
{
	Player*				GameManager::mPlayer = nullptr;
	PlayerProjectile*	GameManager::mPlayerAttack[PLAYER_PROJECTILE_POOL] = {};

	PlayerInfo*	GameManager::mPlayerInfo = nullptr;
	PlayerStat*	GameManager::mDefaultStat = nullptr;
	int			GameManager::mPlayerItems[(UINT)eItemList::End] = {};

	float		GameManager::mDifficultyTime = 0.0f;



	void GameManager::Initialize()
	{
		// 플레이어 설정
		mPlayerInfo = new PlayerInfo();
		mDefaultStat = new PlayerStat();
		InitStat(mPlayerInfo);
		mDefaultStat = mPlayerInfo->stat;
		PlayerLevelUp();

		// 오브젝트 할당
		InitObject();
	}
	void GameManager::InitObject()
	{
		// 플레이어와 투사체 풀 생성
		mPlayer = new Player();
		mPlayer->SetType(eColliderLayer::Player);
		for (int idx = 0; idx < PLAYER_PROJECTILE_POOL; ++idx)
		{
			mPlayerAttack[idx] = new PlayerProjectile();
			mPlayerAttack[idx]->SetType(eColliderLayer::Player_Projectile);
			mPlayerAttack[idx]->SetPlayerInfo(mPlayer);
		}
	}

	void GameManager::AddObject()
	{
		Scene* scene = SceneManager::GetPlayScene();
		scene->AddGameObject(mPlayer, eColliderLayer::Player);
		mPlayer->AddComponentScene();

		for (int idx = 0; idx < PLAYER_PROJECTILE_POOL; ++idx)
		{
			scene->AddGameObject(mPlayerAttack[idx], eColliderLayer::Player_Projectile);
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
		mDifficultyTime += Time::GetDeltaTime();

		// 레벨관련 로직
		if (mPlayerInfo->curExp >= mPlayerInfo->maxExp)
		{
			float overExp = mPlayerInfo->curExp - mPlayerInfo->maxExp;
			PlayerLevelUp();
			mPlayerInfo->curExp = overExp;
		}
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
	void GameManager::PickUpItems(eItemList item)
	{
		++mPlayerItems[(UINT)item];
	}

	void GameManager::StageClear()
	{
	}
}