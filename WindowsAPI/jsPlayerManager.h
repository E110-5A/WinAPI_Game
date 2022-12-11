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

		// ���ӸŴ����� �÷��̾ ������ ���ǿ� �޼��ϸ� �ݵ�� ȣ���� ��
		static void PlayerLevelUp();

		static PlayerStat& GetPlayerStat() { return mPlayerStat; }

	private:
		static PlayerStat	mDefaultStat;		// ���� ����
		static PlayerStat	mPlayerStat;		// �÷��̾� ���� ���� (���� ������ ����)
		static int			mPlayerLevel;		// �÷��̾� ����
		// ������ �迭 ����Ʈ�� �ʿ���
	};
}