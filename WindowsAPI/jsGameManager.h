#pragma once
#include "Common.h"

namespace js
{
	class Player;
	class PlayerProjectile;
	class Monster;
	class Chest;
	class BossMonster;
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

		static void SetPlayable(bool Playable) { mPlayable = Playable; }

		// Get
		static Player* GetPlayer() { return mPlayer; }
		static PlayerInfo* GetPlayerInfo() { return mPlayerInfo; }
		static int* GetDifficulty() { return mDifficulty; }

		// 아이템 함수
		static void PickUpItems(eItemList item);
		static int* GetItemList() { return mPlayerItems; }

		static void StageClear();

	private:
		// 씬에서 사용할 객체

		static Player*				mPlayer;
		static PlayerProjectile*	mPlayerAttack[PLAYER_PROJECTILE_POOL];

		static Monster*				mMonster[MONSTER_POOL];
		static Chest*				mChest[CHEST_POOL];
		static BossMonster*			mBossMonster;



		// 플레이어 정보
		static PlayerInfo*	mPlayerInfo;
		static PlayerStat*	mDefaultStat;		// 기초 스텟
		static int			mPlayerItems[(UINT)eItemList::End];
		
		// 게임 정보
		static bool			mPlayable;
		static int*			mDifficulty;
		static float*		mDifficultyTime;	// 2~5분마다 몬스터가 강해짐
	};
}