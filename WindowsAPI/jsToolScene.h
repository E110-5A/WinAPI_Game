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

		void SaveTilePalette();
		void LoadTilePalette();
		void LoadTilePalette(const std::wstring& path);

		// 추후 스테이지 충돌체정보 저장기능 완성할것
		void SaveCollision();
		void LoadCollision();

		Image* GetAtlasImage() { return mTilePalette->GetImage(); }
		void SetTileIndex(UINT index) { mTileIndex = index; }
		UINT GetTileIndex() { return mTileIndex; }

	private:
		TilePalette* mTilePalette;
		UINT mTileIndex;
	};
}