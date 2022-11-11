#include "jsTilePalette.h"
#include "jsImage.h"
#include "jsResources.h"

namespace js
{
	TilePalette::TilePalette()
	{
		mAtlas = Resources::Load<Image>(L"TileAtlas", L"..\\Resources\\Image\\Tile\\AtlasTile.bmp");
	}

	TilePalette::~TilePalette()
	{
	}

	void TilePalette::Tick()
	{
	}
	void TilePalette::Render(HDC hdc)
	{
	}
}