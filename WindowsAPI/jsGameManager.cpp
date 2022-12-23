#include "jsGameManager.h"

// manager
#include "jsTime.h"
#include "jsPlayerManager.h"
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

	PlayerInfo	GameManager::mPlayerInfo = {};
	PlayerStat	GameManager::mDefaultStat = {};
	int			GameManager::mPlayerItems[(UINT)eItemList::End] = {};

	float		GameManager::mDifficultyTime = 0.0f;



	void GameManager::Initialize()
	{
		// 오브젝트 할당
		InitObject();

		// 플레이어 설정
		InitStat(mPlayerInfo.stat);
		mDefaultStat = mPlayerInfo.stat;
		PlayerLevelUp();

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


	void GameManager::InitStat(PlayerStat& stat)
	{
		stat.playerHealth.maxHP = 110;
		stat.playerHealth.curHP = 110;
		stat.playerHealth.healthRegen = 0.6;
		stat.playerHealth.defance = 0;
		stat.playerOffence.damage = 12;
		stat.playerOffence.attackSpeed = 1;
		stat.playerOffence.range = 700;
		stat.playerUtility.moveSpeed = 1.3;
		stat.playerUtility.maxJumpCount = 1;
		stat.playerUtility.curJumpCount = 0;
		stat.playerUtility.jumpPower = 600;
	}
	void GameManager::Tick()
	{
		mDifficultyTime += Time::GetDeltaTime();

		// 레벨관련 로직
		if (mPlayerInfo.curExp >= mPlayerInfo.maxExp)
		{
			float overExp = mPlayerInfo.curExp - mPlayerInfo.maxExp;
			PlayerLevelUp();
			mPlayerInfo.curExp = overExp;
		}
	}
	void GameManager::AddObjects()
	{
		Scene* scene = SceneManager::GetPlayScene();
	}
	void GameManager::PlayerLevelUp()
	{
		++mPlayerInfo.level;
		mPlayerInfo.stat.playerHealth.maxHP = (mDefaultStat.playerHealth.maxHP + (32 * mPlayerInfo.level) - 32);
		mPlayerInfo.stat.playerHealth.healthRegen = (mDefaultStat.playerHealth.healthRegen + (0.12 * mPlayerInfo.level) - 0.12);
		mPlayerInfo.stat.playerHealth.defance = (mDefaultStat.playerHealth.defance + (2 * mPlayerInfo.level) - 2);
		mPlayerInfo.stat.playerOffence.damage = (mDefaultStat.playerOffence.damage + (3 * mPlayerInfo.level) - 3);
	}
	void GameManager::PickUpItems(eItemList item)
	{
		++mPlayerItems[(UINT)item];
	}

	void GameManager::StageClear()
	{
	}
}