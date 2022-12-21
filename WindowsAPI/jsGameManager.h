#pragma once
#include "Common.h"

namespace js
{
	class GameManager
	{
	public:

		void Initialize();		// ...? ���ӸŴ����� �÷��̾� �Ŵ����� ��ġ�°� �������� ������
		void Tick();			// �ֱ������� ������Ʈ �� ������ ���� ����;
		// Render() UI��Ҵ� ������ �ذ��ϴϱ� ���� �ʿ� ������


		void PlayerLevelUp();	// playerManager::LevelUp() ȣ��

		
		float GetDifficultyTime() { return mDifficultyTime; }
		float GetPlayerGold() { return mPlayerInfo.gold; }

		// ���� �¸����� �޼��� Teleport ��ü�� ȣ�� -> �� �ʱ�ȭ ������ ��ģ ��, ���������� �ѱ�� ObjectPool ����
		void StageClear();

	private:
		// ������ ����� Ǯ ��ü
		
		
		// ���� ����
		PlayerInfo	mPlayerInfo;
		float		mDifficultyTime;	// 2~5�и��� ���Ͱ� ������

	};
}