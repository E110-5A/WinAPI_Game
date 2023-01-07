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
	class Teleporter;
	class Sound;
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

		static Sound* GetTitleSound() { return mTitleMusic; }
		static Sound* GetSTG1Sound() { return mSTG1Music; }
		static Sound* GetSTG2Sound() { return mSTG2Music; }
		static Sound* GetBossSound() { return mBossMusic; }

		// ������ �������� ��� ȣ��
		static void Playing();
		static void SetPlayable(bool Playable) { mPlayable = Playable; }	// ��ó�� ������ �� ������ �ѹ��� ȣ���������


		static void AddExp(float exp) { mPlayerInfo->curExp += exp; }
		static void PlayerLevelUp();

		static void Damaged() {} // �Ⱦ�


		// ���
		static void SpawnMonster();
		static void KillBoss();


		static void SetSpawnPlatform(Platform* prevPlatform) { mSpawnPlatform = prevPlatform; }
		static Platform* GetSpawnPlatform() { return mSpawnPlatform; }

		// Get Info
		static Player* GetPlayer() { return mPlayer; }
		static PlayerInfo* GetPlayerInfo() { return mPlayerInfo; }
		static int* GetDifficulty() { return mDifficulty; }
		// Get Objects
		static BossMonster* GetBoss() { return mBossMonster; }
		static Chest* GetChest(int idx) { return mChest[idx]; }
		static Teleporter* GetTeleporter() { return mTeleporter; }

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
		static Sound* mTitleMusic;
		static Sound* mSTG1Music;
		static Sound* mSTG2Music;
		static Sound* mBossMusic;

		static Sound* mLevelUpSound;
		static Sound* mTeleporterSound;


		static Player*				mPlayer;
		static PlayerProjectile*	mPlayerAttack[PLAYER_PROJECTILE_POOL];

		static Monster*				mMonster[MONSTER_POOL];
		static Chest*				mChest[CHEST_POOL];
		static BossMonster*			mBossMonster;
		static Teleporter*			mTeleporter;
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