#pragma once
#include "Common.h"

namespace js
{
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

		// 게임매니저는 플레이어가 레벨업 조건에 달성하면 반드시 호출할 것
		static void PlayerLevelUp();

		static PlayerStat& GetPlayerStat() { return mPlayerStat; }

	private:
		static PlayerStat	mDefaultStat;		// 기초 스텟
		static PlayerStat	mPlayerStat;		// 플레이어 순정 스텟 (레벨 증가량 포함)
		static int			mPlayerLevel;		// 플레이어 레벨
		// 아이템 배열 리스트가 필요함
	};
}