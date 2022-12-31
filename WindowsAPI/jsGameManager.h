#pragma once
#include "Common.h"

namespace js
{
	class Player;
	class PlayerProjectile;
	class Monster;
	class Chest;
	class Platform;
	class BossMonster;
	class GameManager
	{
	public:
		
		static void Initialize();
		// 오브젝트 생성
		static void InitObject();
		
		static void InitStat(PlayerInfo* info);
		static void Tick();

		// 오브젝트 추가 (씬에서 호출)
		static void AddObject();


		// 게임이 진행중인 경우 호출
		static void Playing();
		static void SetPlayable(bool Playable) { mPlayable = Playable; }	// 맨처음 시작할 때 씬에서 한번은 호출해줘야함


		static void AddExp(float exp) { mPlayerInfo->curExp += exp; }
		static void PlayerLevelUp();

		static void Damaged() {} // 안씀


		// 몬스터 리스폰 기능 (able = true, rand type, rand Pos)
		static void SetSpawnPlatform(Platform* prevPlatform) { mSpawnPlatform = prevPlatform; }
		static void RespawnMonster();
		static Platform* GetSpawnPlatform() { return mSpawnPlatform; }


		// 상자 세팅
		static Chest* GetChest(int idx) { return mChest[idx]; }


		// Get Info
		static Player* GetPlayer() { return mPlayer; }
		static PlayerInfo* GetPlayerInfo() { return mPlayerInfo; }
		static int* GetDifficulty() { return mDifficulty; }

		// 아이템 함수
		static void PickUpItems(eItemList item);
		static int* GetItemList() { return mPlayerItems; }


		static void StageClear(); // 안쓰는 기능


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

		static Platform*			mSpawnPlatform;

		// 플레이어 정보
		static PlayerInfo*	mPlayerInfo;
		static PlayerStat*	mDefaultStat;		// 기초 스텟
		static int			mPlayerItems[(UINT)eItemList::End];
		
		// 게임 정보
		static bool			mPlayable;
		static int*			mDifficulty;
		static float*		mDifficultyTime;	// 2~5분마다 몬스터가 강해짐
		static float		mSpawnTime;

		// 60초마다 difficulty가 1 증가함 최대 9까지 있음
	};
}