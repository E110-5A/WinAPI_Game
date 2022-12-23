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
		static void InitStat(PlayerStat& stat);
		static void Tick();

		// ��� �Լ�
		static void AddObjects();
		static void PlayerLevelUp();
		static void Damaged() {}



		// ��ü ��������
		static Player* GetPlayer() { return mPlayer; }

		// �÷��̾� ���� ��������
		static PlayerInfo& GetPlayerInfo() { return mPlayerInfo; }
		static PlayerStat& GetPlayerStat() { return mPlayerInfo.stat; }

		// ������ �Լ�
		static void PickUpItems(eItemList item);
		static int* GetItemList() { return mPlayerItems; }


		static void StageClear();

	private:
		// ������ ����� ��ü
		static Player*				mPlayer;
		static PlayerProjectile*	mPlayerAttack[PLAYER_PROJECTILE_POOL];
		// ���� Ǯ, ���� Ǯ �߰��� ����



		// �÷��̾� ����
		static PlayerInfo	mPlayerInfo;
		static PlayerStat	mDefaultStat;		// ���� ����
		static int			mPlayerItems[(UINT)eItemList::End];
		
		// ���� ����
		static float		mDifficultyTime;	// 2~5�и��� ���Ͱ� ������

	};
}