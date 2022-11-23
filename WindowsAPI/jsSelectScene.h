#pragma once
#include "jsScene.h"

namespace js
{
	class SelectScene : public Scene
	{
	public:
		SelectScene();
		~SelectScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter() override;		// �ش� ������ ����� �� ȣ��
		virtual void Exit() override;
	};
}