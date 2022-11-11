#pragma once
#include "jsScene.h"
#include "jsTilePalette.h"

namespace js
{

	class ToolScene :
		public Scene
	{
	public:
		ToolScene();
		~ToolScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter() override;		// 해당 씬으로 변경될 때 호출
		virtual void Exit() override;

		Image* GetAtlasImage() { return mTilePalette->GetImage(); }


	private:
		TilePalette* mTilePalette;
	};
}