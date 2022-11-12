#include "jsTilePalette.h"
#include "jsImage.h"
#include "jsResources.h"
#include "jsInput.h"
#include "jsToolScene.h"
#include "jsSceneManager.h"
#include "jsObject.h"

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
		if (KEY_PRESSE(eKeyCode::LBTN))
		{
			if (GetFocus())
			{
				js::Pos mousePos = js::Input::GetMousePos();

				int layerX = mousePos.x / (TILE_SIZE * TILE_SCALE);
				int layerY = mousePos.y / (TILE_SIZE * TILE_SCALE);

				js::Scene* scene = js::SceneManager::GetPlayScene();
				js::ToolScene* toolScene = dynamic_cast<ToolScene*>(scene);
				UINT index = toolScene->GetTileIndex();
				CreateTile(index, Vector2(layerX, layerY));
			}
		}
	}
	void TilePalette::Render(HDC hdc)
	{
	}
	void TilePalette::CreateTile(UINT index, Pos indexPos)
	{
		TileID key;
		key.left = indexPos.x;
		key.right = indexPos.y;

		std::unordered_map<UINT64, Tile*>::iterator iter = mTiles.find(key.ID);

		if (iter != mTiles.end())
		{
			iter->second->SetIndex(index);
		}

		Pos objectPos = indexPos * TILE_SIZE * TILE_SCALE;

		Tile* tile = object::Instantiate<Tile>(eColliderLayer::Tile, objectPos);
		tile->Initialize(mAtlas, index);
		mTiles.insert(std::make_pair(key.ID, tile));
	}
}