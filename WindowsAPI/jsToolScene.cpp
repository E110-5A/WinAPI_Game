#include "jsToolScene.h"
#include "jsApplication.h"

namespace js
{
	
	ToolScene::ToolScene()
	{
		mTilePalette = new TilePalette();
	}
	ToolScene::~ToolScene()
	{
		delete mTilePalette;
	}
	void ToolScene::Initialize()
	{
	}


	void ToolScene::Tick()
	{
	}
	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t szFloat[40] = {};
		swprintf_s(szFloat, 40, L"Tool Scene");
		int strLen = wcsnlen_s(szFloat, 40);
		TextOut(hdc, 10, 30, szFloat, strLen);



		WindowData mainWindow = Application::GetInstance().GetWindowData();

		HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 125, 0));
		HPEN prevPen = (HPEN)SelectObject(hdc, greenPen);



		int maxRow = mainWindow.height / TILE_SIZE + 1;
		for (int idx = 0; idx < maxRow; idx++)
		{
			MoveToEx(hdc, 0, TILE_SIZE * idx, nullptr);
			LineTo(hdc, mainWindow.width, TILE_SIZE * idx);
		}
		int maxCol = mainWindow.width / TILE_SIZE + 1;
		for (int idx = 0; idx < maxCol; idx++)
		{
			MoveToEx(hdc, TILE_SIZE * idx, 0, nullptr);
			LineTo(hdc, TILE_SIZE * idx, mainWindow.height);
		}

		(HPEN)SelectObject(hdc, prevPen);
		DeleteObject(greenPen);
	}


	void ToolScene::Enter()
	{
		Application::GetInstance().SetMenuBar(true);
	}
	void ToolScene::Exit()
	{
		Application::GetInstance().SetMenuBar(false);
	}
}
