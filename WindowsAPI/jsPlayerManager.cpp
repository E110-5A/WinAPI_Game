#include "jsPlayerManager.h"

#include "jsSceneManager.h"

#include "jsScene.h"

#include "jsPlayer.h"

namespace js
{
	Player*		PlayerManager::mPlayer = nullptr;
	PlayerInfo	PlayerManager::mPlayerInfo = {};
	PlayerStat	PlayerManager::mDefaultStat = {};

	int			PlayerManager::mPlayerItems[(UINT)eItemList::End] = {};

	void PlayerManager::Initialize()
	{
		InitStat(mPlayerInfo.stat);
		mDefaultStat = mPlayerInfo.stat;
		PlayerLevelUp();
	}

	void PlayerManager::InitStat(PlayerStat& stat)
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

	void PlayerManager::PlayerLevelUp()
	{
		++mPlayerInfo.level;
		mPlayerInfo.stat.playerHealth.maxHP = (mDefaultStat.playerHealth.maxHP + (32 * mPlayerInfo.level) - 32);
		mPlayerInfo.stat.playerHealth.healthRegen = (mDefaultStat.playerHealth.healthRegen + (0.12 * mPlayerInfo.level) - 0.12);
		mPlayerInfo.stat.playerHealth.defance = (mDefaultStat.playerHealth.defance + (2 * mPlayerInfo.level) - 2);
		mPlayerInfo.stat.playerOffence.damage = (mDefaultStat.playerOffence.damage + (3 * mPlayerInfo.level) - 3);
	}

	void PlayerManager::PickUpItems(eItemList item)
	{
		++mPlayerItems[(UINT)item];
	}
}