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
		
		// 기능 함수
		static void PlayerLevelUp();
		
		// 스텟 함수
		static PlayerStat& GetPlayerStat() { return mPlayerStat; }

		// 아이템 함수
		static void PickUpItems(eItemList item);
		static int GetItem(eItemList type) { return mPlayerItems[(UINT)type]; }
		static int* GetItemList() { return mPlayerItems; }

	private:
		static PlayerStat	mDefaultStat;		// 기초 스텟
		static PlayerStat	mPlayerStat;		// 플레이어 순정 스텟 (레벨 증가량 포함)
		static int			mPlayerLevel;		// 플레이어 레벨
		static int			mPlayerItems[(UINT)eItemList::End];
	};
}