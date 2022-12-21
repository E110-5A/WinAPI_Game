#pragma once
#include "Common.h"

namespace js
{
	class GameManager
	{
	public:

		void Initialize();		// ...? 게임매니저와 플레이어 매니저를 합치는게 나을수도 있을듯
		void Tick();			// 주기적으로 업데이트 할 정보가 있음 ㅇㅇ;
		// Render() UI요소는 씬에서 해결하니까 굳이 필요 없을듯


		void PlayerLevelUp();	// playerManager::LevelUp() 호출

		
		float GetDifficultyTime() { return mDifficultyTime; }
		float GetPlayerGold() { return mPlayerInfo.gold; }

		// 게임 승리조건 달성시 Teleport 객체가 호출 -> 씬 초기화 과정을 거친 뒤, 스테이지를 넘기고 ObjectPool 세팅
		void StageClear();

	private:
		// 씬에서 사용할 풀 객체
		
		
		// 게임 정보
		PlayerInfo	mPlayerInfo;
		float		mDifficultyTime;	// 2~5분마다 몬스터가 강해짐

	};
}