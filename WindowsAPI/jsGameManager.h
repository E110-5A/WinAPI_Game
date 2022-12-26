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

		// 현재 씬에 오브젝트 추가
		static void AddObject();
		
		static void InitStat(PlayerInfo* info);
		static void Tick();

		// 기능 함수
		static void PlayerLevelUp();
		static void Damaged() {}
		static void Playing();

		// 몬스터 리스폰 기능 (able = true, rand type, rand Pos

		// 상자 세팅
		static Chest* GetChest(int idx) { return mChest[idx]; }

		static void SetPlayable(bool Playable) { mPlayable = Playable; }

		// Info
		static Player* GetPlayer() { return mPlayer; }
		static PlayerInfo* GetPlayerInfo() { return mPlayerInfo; }
		static int* GetDifficulty() { return mDifficulty; }

		// 아이템 함수
		static void PickUpItems(eItemList item);
		static int* GetItemList() { return mPlayerItems; }

		static void StageClear();


		static void Release()
		{
			delete mPlayerInfo;
		}
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

		// 60초마다 difficulty가 1 증가함 최대 9까지 있음
	};
}