#include "jsTilePalette.h"
#include "jsImage.h"
#include "jsResources.h"
#include "jsInput.h"
#include "jsToolScene.h"
#include "jsSceneManager.h"
#include "jsObject.h"
#include "jsApplication.h"
#include <commdlg.h>

namespace js
{
	TilePalette::TilePalette()
	{
		mAtlas = Resources::Load<Image>(L"TileAtlas", L"..\\Resources\\Image\\Tile\\RoRTile.bmp");
		mWindowInfo = Application::GetInstance().GetWindowData();
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
				if (mousePos.x < 0 || mousePos.y < 0)
					return;
				if (mousePos.x > mWindowInfo.width
					|| mousePos.y > mWindowInfo.height)
					return;

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

		Pos objectPos = indexPos * (TILE_SIZE * TILE_SCALE);

		Tile* tile = object::Instantiate<Tile>(eColliderLayer::Tile, objectPos);
		tile->Initialize(mAtlas, index);
		mTiles.insert(std::make_pair(key.ID, tile));
	}
	void TilePalette::Save()
	{
		// 어디 경로에 저장할지 지정해줘야함

		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"wb");
		if (nullptr == pFile)
			return;

		std::unordered_map<UINT64, Tile*>::iterator iter = mTiles.begin();
		for (; iter != mTiles.end(); ++iter)
		{
			int tileIndex = (*iter).second->GetIndex();
			fwrite(&tileIndex, sizeof(int), 1, pFile);

			TileID id;
			id.ID = (*iter).first;
			fwrite(&id.ID, sizeof(UINT64), 1, pFile);

		}
		fclose(pFile);
	}

	void TilePalette::Load()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"rb");
		if (nullptr == pFile)
			return;

		while (true)
		{
			int tileIndex = 0;
			TileID id;

			if (fread(&tileIndex, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&id.ID, sizeof(UINT64), 1, pFile) == NULL)
				break;

			CreateTile(tileIndex, Vector2(id.left, id.right));
		}
		fclose(pFile);
	}
	void TilePalette::Load(const std::wstring& path)
	{
		
		FILE* pFile = nullptr;
		_wfopen_s(&pFile, path.c_str(), L"rb");
		if (nullptr == pFile)
			return;

		while (true)
		{
			int tileIndex = 0;
			TileID id;

			if (fread(&tileIndex, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&id.ID, sizeof(UINT64), 1, pFile) == NULL)
				break;

			CreateTile(tileIndex, Vector2(id.left, id.right));
		}
		fclose(pFile);
	}
}