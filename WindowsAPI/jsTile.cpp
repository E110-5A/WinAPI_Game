#include "jsTile.h"
#include "jsCamera.h"
#include "jsImage.h"

namespace js
{
	Tile::Tile(Pos pos)
		: GameObject(pos)
		, mAtlas(nullptr)
		, mY(-1)
		, mX(-1)
	{
	}
	Tile::~Tile()
	{
	}
	void Tile::Initialize(Image* atlas, int index)
	{
		mIndex = index;
		if (nullptr == atlas
			|| 0 > index)
			return;

		mAtlas = atlas;
		int maxColum = mAtlas->GetWidth() / TILE_SIZE;
		int maxRow = mAtlas->GetHeight() / TILE_SIZE;

		mY = index / maxColum;
		mX = index % maxColum;
	}


	void Tile::Tick()
	{
	}
	void Tile::Render(HDC hdc)
	{
		if (nullptr == mAtlas)
			return;
		Pos nowPos = GetPos();
		Pos renderPos = Camera::CalculateObjectPos(nowPos);

		int tileImageX = mX * TILE_SIZE;
		int tileImageY = mY * TILE_SIZE;

		TransparentBlt(hdc, renderPos.x, renderPos.y, 
			TILE_SIZE * TILE_SCALE, TILE_SIZE * TILE_SCALE,
			mAtlas->GetDC(), tileImageX, tileImageY,
			TILE_SIZE, TILE_SIZE,
			RGB(255, 0, 255));

	}
	void Tile::SetIndex(UINT index)
	{
		mIndex = index;

		int maxCol = mAtlas->GetWidth() / TILE_SIZE * TILE_SCALE;
		int maxRow = mAtlas->GetHeight() / TILE_SIZE * TILE_SCALE;
	
		mY = index / maxCol;
		mX = index % maxCol;
	}
}