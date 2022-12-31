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
		// ������Ʈ ����
		static void InitObject();
		
		static void InitStat(PlayerInfo* info);
		static void Tick();

		// ������Ʈ �߰� (������ ȣ��)
		static void AddObject();


		// ������ �������� ��� ȣ��
		static void Playing();
		static void SetPlayable(bool Playable) { mPlayable = Playable; }	// ��ó�� ������ �� ������ �ѹ��� ȣ���������


		static void AddExp(float exp) { mPlayerInfo->curExp += exp; }
		static void PlayerLevelUp();

		static void Damaged() {} // �Ⱦ�


		// ���� ������ ��� (able = true, rand type, rand Pos)
		static void SetSpawnPlatform(Platform* prevPlatform) { mSpawnPlatform = prevPlatform; }
		static void RespawnMonster();
		static Platform* GetSpawnPlatform() { return mSpawnPlatform; }


		// ���� ����
		static Chest* GetChest(int idx) { return mChest[idx]; }


		// Get Info
		static Player* GetPlayer() { return mPlayer; }
		static PlayerInfo* GetPlayerInfo() { return mPlayerInfo; }
		static int* GetDifficulty() { return mDifficulty; }

		// ������ �Լ�
		static void PickUpItems(eItemList item);
		static int* GetItemList() { return mPlayerItems; }


		static void StageClear(); // �Ⱦ��� ���


		static void Release()
		{
			delete mPlayerInfo;
		}
	private:
		// ������ ����� ��ü

		static Player*				mPlayer;
		static PlayerProjectile*	mPlayerAttack[PLAYER_PROJECTILE_POOL];

		static Monster*				mMonster[MONSTER_POOL];
		static Chest*				mChest[CHEST_POOL];
		static BossMonster*			mBossMonster;

		static Platform*			mSpawnPlatform;

		// �÷��̾� ����
		static PlayerInfo*	mPlayerInfo;
		static PlayerStat*	mDefaultStat;		// ���� ����
		static int			mPlayerItems[(UINT)eItemList::End];
		
		// ���� ����
		static bool			mPlayable;
		static int*			mDifficulty;
		static float*		mDifficultyTime;	// 2~5�и��� ���Ͱ� ������
		static float		mSpawnTime;

		// 60�ʸ��� difficulty�� 1 ������ �ִ� 9���� ����
	};
}