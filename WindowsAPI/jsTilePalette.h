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

		// void CreateTile();
		// void CreateTiles();

		// void Save();
		// void Load();

		Image* GetImage() { return mAtlas; }

	private:
		Image* mAtlas;
	};
}