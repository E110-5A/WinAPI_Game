#pragma once
#include "Common.h"

namespace js
{
	class Player;
	class PlayerProjectile;
	class GameManager
	{
	public:
		static void Initialize();

		static void InitObject();
		static void AddObject();
		static void InitStat(PlayerInfo* info);
		static void Tick();

		// 기능 함수
		static void PlayerLevelUp();
		static void Damaged() {}
		static void Playing();


		// Get
		static Player* GetPlayer() { return mPlayer; }
		static PlayerInfo* GetPlayerInfo() { return mPlayerInfo; }
		static float* GetDifficultyTime() { return mDifficultyTime; }
		// 아이템 함수
		static void PickUpItems(eItemList item);
		static int* GetItemList() { return mPlayerItems; }


		static void StageClear();

	private:
		// 씬에서 사용할 객체
		static Player*				mPlayer;
		static PlayerProjectile*	mPlayerAttack[PLAYER_PROJECTILE_POOL];
		// 몬스터 풀, 상자 풀 추가될 예정



		// 플레이어 정보
		static PlayerInfo*	mPlayerInfo;
		static PlayerStat*	mDefaultStat;		// 기초 스텟
		static int			mPlayerItems[(UINT)eItemList::End];
		
		// 게임 정보
		static float*		mDifficultyTime;	// 2~5분마다 몬스터가 강해짐

	};
}