#pragma once
#include "jsTile.h"

namespace js
{
	class Image;
	class TilePalette
	{
	public:
		TilePalette();
		~TilePalette();

		void Tick();
		void Render(HDC hdc);

		void CreateTile(UINT index, Pos pos);
		// void CreateTiles();

		void Save();
		void Load();
		void Load(const std::wstring& path);

		Image* GetImage() { return mAtlas; }

	private:
		Image*								mAtlas;
		std::unordered_map<UINT64, Tile*>	mTiles;
		WindowData							mWindowInfo;
	};
}