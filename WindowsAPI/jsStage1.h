#pragma once
#include "jsScene.h"

namespace js
{
	class Stage1 : public Scene
	{
	public:
		Stage1();
		~Stage1();

		void Initialize() override;

		void InitBG();

		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter() override;		// �ش� ������ ����� �� ȣ��
		virtual void Exit() override;

		void EnterLayer();
		void EnterObject();
		void EnterUI();
	private:
	};
}
