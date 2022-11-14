#pragma once
#include "jsScene.h"

namespace js
{
	class Monster;
	class TestScene : public Scene
	{
	public:
		TestScene();
		~TestScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();

	private:
		Monster* mons[2];
	};
}
