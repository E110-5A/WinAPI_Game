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

		virtual void Enter() override;		// 해당 씬으로 변경될 때 호출
		virtual void Exit() override;

	private:
	};
}