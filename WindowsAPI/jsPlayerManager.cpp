#include "jsPlayerManager.h"

namespace js
{
	PlayerStat	PlayerManager::mDefaultStat = {};
	PlayerStat	PlayerManager::mPlayerStat = {};
	int			PlayerManager::mPlayerLevel = 0;

	void PlayerManager::Initialize()
	{
		InitStat(mDefaultStat);
		InitStat(mPlayerStat);
		PlayerLevelUp();
	}

	void PlayerManager::InitStat(PlayerStat& stat)
	{
		stat.maxHp = 110;
		stat.curHp = 110;
		stat.regenHp = 0.6;
		stat.def = 0;
		stat.moveSpeed = 1.3;
		stat.att = 12;
		stat.attSpeed = 1;
		stat.range = 700;
	}

	void PlayerManager::PlayerLevelUp()
	{
		++mPlayerLevel;
		mPlayerStat.maxHp = (mDefaultStat.maxHp + 32 * mPlayerLevel);
		mPlayerStat.regenHp = (mDefaultStat.regenHp + 0.12 * mPlayerLevel);
		mPlayerStat.def = (mDefaultStat.def + 2 * mPlayerLevel);
		mPlayerStat.att = (mDefaultStat.att + 3 * mPlayerLevel);
	}
}