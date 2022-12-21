#include "jsGameManager.h"

// manager
#include "jsTime.h"
#include "jsPlayerManager.h"

namespace js
{
	void GameManager::Initialize()
	{
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
	void GameManager::PlayerLevelUp()
	{
		PlayerManager::PlayerLevelUp();
	}
	void GameManager::StageClear()
	{
	}
}