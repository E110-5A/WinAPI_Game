#pragma once
#include "jsScene.h"

namespace js
{
	class TitleScene :
		public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter() override;		// �ش� ������ ����� �� ȣ��
		virtual void Exit() override;

	private:
	};
}