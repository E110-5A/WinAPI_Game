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

		// ��� �Լ�
		static void PlayerLevelUp();
		static void Damaged() {}
		static void Playing();

		static void SetPlayable(bool Playable) { mPlayable = Playable; }

		// Get
		static Player* GetPlayer() { return mPlayer; }
		static PlayerInfo* GetPlayerInfo() { return mPlayerInfo; }
		static int* GetDifficulty() { return mDifficulty; }

		// ������ �Լ�
		static void PickUpItems(eItemList item);
		static int* GetItemList() { return mPlayerItems; }

		static void StageClear();

	private:
		// ������ ����� ��ü

		static Player*				mPlayer;
		static PlayerProjectile*	mPlayerAttack[PLAYER_PROJECTILE_POOL];

		static Monster*				mMonster[MONSTER_POOL];
		static Chest*				mChest[CHEST_POOL];
		static BossMonster*			mBossMonster;



		// �÷��̾� ����
		static PlayerInfo*	mPlayerInfo;
		static PlayerStat*	mDefaultStat;		// ���� ����
		static int			mPlayerItems[(UINT)eItemList::End];
		
		// ���� ����
		static bool			mPlayable;
		static int*			mDifficulty;
		static float*		mDifficultyTime;	// 2~5�и��� ���Ͱ� ������
	};
}