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
		
		// ���� �Լ�
		static PlayerStat& GetPlayerStat() { return mPlayerStat; }

		// ������ �Լ�
		static void PickUpItems(eItemList item);
		static int GetItem(eItemList type) { return mPlayerItems[(UINT)type]; }
		static int* GetItemList() { return mPlayerItems; }

	private:
		static PlayerStat	mDefaultStat;		// ���� ����
		static PlayerStat	mPlayerStat;		// �÷��̾� ���� ���� (���� ������ ����)
		static int			mPlayerLevel;		// �÷��̾� ����
		static int			mPlayerItems[(UINT)eItemList::End];
	};
}