#include "jsTilePalette.h"
#include <commdlg.h>
#include "jsApplication.h"

// manager
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCamera.h"

#include "jsMapToolScene.h"

// resource
#include "jsResources.h"
#include "jsImage.h"

// object
#include "jsObject.h"

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

	// Ÿ�� �ȷ�Ʈ ���
	void TilePalette::Tick()
	{
		// Ÿ�� ����
		if (KEY_PRESSE(eKeyCode::LBTN))
		{
			if (GetFocus())
			{
				//eSceneType type = Application::GetInstance();

				// ���콺 ��ġ ������
				Pos mousePos = Input::GetMousePos();

				// ���콺�� ȭ�� ������ ������ ret
				if (mousePos.x < 0 || mousePos.y < 0)
					return;
				if (mousePos.x > mWindowInfo.width
					|| mousePos.y > mWindowInfo.height)
					return;

				mousePos = Camera::CalculateMousePos(mousePos);
				// ���콺 ��ġ�� Ÿ�� ���̸�ŭ ���� ��
				int layerX = mousePos.x / (TILE_SIZE * TILE_SCALE);
				int layerY = mousePos.y / (TILE_SIZE * TILE_SCALE);

				// ���� ������
				Scene* scene = SceneManager::GetPlayScene();
				MapToolScene* toolScene = dynamic_cast<MapToolScene*>(scene);

				// ���� �������� Ÿ���� ���̾� ��ġ�� ����
				UINT index = toolScene->GetTileIndex();
				CreateTile(index, Vector2(layerX, layerY));
			}
		}
		// Ÿ�� ����
		if (KEY_PRESSE(eKeyCode::RBTN))
		{
			if (GetFocus())
			{
				// ���콺 ��ġ ��������
				js::Pos mousePos = js::Input::GetMousePos();

				// ������ ������ ������
				if (mousePos.x < 0 || mousePos.y < 0)
					return;
				if (mousePos.x > mWindowInfo.width
					|| mousePos.y > mWindowInfo.height)
					return;

				// �� ���� ��������
				Scene* scene = SceneManager::GetPlayScene();
				MapToolScene* toolScene = dynamic_cast<MapToolScene*>(scene);

				// ��ġ�� Ÿ�� ������Ʈ ��������
				std::vector<GameObject*> tiles = toolScene->GetGameObjects(eColliderLayer::Tile);
				std::vector<GameObject*>::iterator tileIter = tiles.begin();
				
				// ��� Ÿ���� ��ȸ
				for (; tileIter != tiles.end(); ++tileIter)
				{
					Vector2 objPos = (*tileIter)->GetPos();
					// ���콺�� ��ȿ�� ��ġ�� �ִ°�� �ش� Ÿ�� ����
					if (objPos.x < mousePos.x && objPos.x + (TILE_SIZE * TILE_SCALE) > mousePos.x
						&& objPos.y < mousePos.y && objPos.y + (TILE_SIZE * TILE_SCALE) > mousePos.y)
					{
						object::Destroy((*tileIter));
					}
				}
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
		// ��� ��ο� �������� �����������

		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0"; //"All Files\0*.*\0\0"
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