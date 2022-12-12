#include "jsPlayerManager.h"

namespace js
{
	PlayerStat	PlayerManager::mDefaultStat = {};
	PlayerStat	PlayerManager::mPlayerStat = {};
	int			PlayerManager::mPlayerLevel = 0;
	int			PlayerManager::mPlayerItems[(UINT)eItemList::End] = {};

	void PlayerManager::Initialize()
	{
		InitStat(mDefaultStat);
		InitStat(mPlayerStat);
		PlayerLevelUp();
	}

	void PlayerManager::InitStat(PlayerStat& stat)
	{
		stat.playerHealth.maxHP = 110;
		stat.playerHealth.curHP = 110;
		stat.playerHealth.healthRegen = 0.6;
		stat.playerHealth.defance = 0;
		stat.playerHealth.moveSpeed = 1.3;
		stat.playerOffence.damage = 12;
		stat.playerOffence.attackSpeed = 1;
		stat.playerOffence.range = 700;
	}

	void PlayerManager::PlayerLevelUp()
	{
		++mPlayerLevel;
		mPlayerStat.playerHealth.maxHP = (mDefaultStat.playerHealth.maxHP + (32 * mPlayerLevel));
		mPlayerStat.playerHealth.healthRegen = (mDefaultStat.playerHealth.healthRegen + (0.12 * mPlayerLevel));
		mPlayerStat.playerHealth.defance = (mDefaultStat.playerHealth.defance + (2 * mPlayerLevel));
		mPlayerStat.playerOffence.damage = (mDefaultStat.playerOffence.damage + (3 * mPlayerLevel));
	}
	void PlayerManager::PickUpItems(eItemList item)
	{
		++mPlayerItems[(UINT)item];
	}
}