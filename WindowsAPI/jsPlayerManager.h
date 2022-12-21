#pragma once
#include "Common.h"

namespace js
{
	class Player;
	class SceneManager;
	class PlayerManager
	{
	public:
		static PlayerManager& GetInstance()
		{
			static PlayerManager m_Instance;
			return m_Instance;
		}

		static void Initialize();
		static void InitStat(PlayerStat& stat);
		
		// ��� �Լ�
		static void PlayerLevelUp();
		static void Damaged() {}
		
		static void SetPlayer(Player* player) { mPlayer = player; }
		static Player* GetPlayer() { return mPlayer; }

		// ���� �Լ�
		static PlayerInfo& GetPlayerInfo() { return mPlayerInfo; }
		static PlayerStat& GetPlayerStat() { return mPlayerInfo.stat; }

		// ������ �Լ�
		static void PickUpItems(eItemList item);
		static int GetItem(eItemList type) { return mPlayerItems[(UINT)type]; }
		static int* GetItemList() { return mPlayerItems; }


	private:
		static Player*		mPlayer;
		static PlayerInfo	mPlayerInfo;

		static PlayerStat	mDefaultStat;		// ���� ����
		static int			mPlayerItems[(UINT)eItemList::End];
	};
}