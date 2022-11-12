#include "framework.h"
#include "WindowsAPI.h"

#include "jsToolScene.h"
#include "jsApplication.h"
#include "jsSceneManager.h"
#include "jsInput.h"
#include "jsScene.h"
#include "jsImage.h"

namespace js
{
	
	ToolScene::ToolScene()
        : mTileIndex(0)
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
        if (mTilePalette)
            mTilePalette->Tick();
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
			MoveToEx(hdc, 0, TILE_SIZE * idx * TILE_SCALE, nullptr);
			LineTo(hdc, mainWindow.width, TILE_SIZE * idx * TILE_SCALE);
		}
		int maxCol = mainWindow.width / TILE_SIZE + 1;
		for (int idx = 0; idx < maxCol; idx++)
		{
			MoveToEx(hdc, TILE_SIZE * idx * TILE_SCALE, 0, nullptr);
			LineTo(hdc, TILE_SIZE * idx * TILE_SCALE, mainWindow.height);
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



LRESULT CALLBACK AtlasWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        WindowData windowData = js::Application::GetInstance().GetWindowData();
        WindowData atlasWindowData = js::Application::GetInstance().GetAtlasWindowData();


        js::Scene* Scene = js::SceneManager::GetPlayScene();
        js::ToolScene* toolScene = dynamic_cast<js::ToolScene*>(Scene);
        js::Image* atlas = toolScene->GetAtlasImage();


        RECT rect = { 0,0,atlas->GetWidth() * TILE_SCALE, atlas->GetHeight() * TILE_SCALE };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
        SetWindowPos(hWnd, nullptr,
            windowData.width
            , 0
            , rect.right - rect.left
            , rect.bottom - rect.top
            , 0);
        ShowWindow(hWnd, true);
        UpdateWindow(hWnd);
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_LBUTTONDOWN:
    {
        if (GetFocus())
        {
            js::Pos mousePos = js::Input::GetMousePos(hWnd);
            int y = mousePos.y / (TILE_SIZE * TILE_SCALE);
            int x = mousePos.x / (TILE_SIZE * TILE_SCALE);

            int index = (y * TILE_LINE_X) + (x % TILE_LINE_X);

            js::Scene* Scene = js::SceneManager::GetPlayScene();
            js::ToolScene* toolScene = dynamic_cast<js::ToolScene*>(Scene);

            toolScene->SetTileIndex(index);
        }


    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        WindowData atlasWindowData = js::Application::GetInstance().GetAtlasWindowData();
        js::Scene* Scene = js::SceneManager::GetPlayScene();
        js::ToolScene* toolScene = dynamic_cast<js::ToolScene*>(Scene);
        js::Image* atlas = toolScene->GetAtlasImage();

        js::Pos pos(js::Vector2::Zero);

        TransparentBlt(hdc, pos.x, pos.y, atlas->GetWidth() * TILE_SCALE, atlas->GetHeight() * TILE_SCALE,
            atlas->GetDC(), 0, 0, atlas->GetWidth(), atlas->GetHeight(),
            RGB(255, 0, 255));


        // stockObject를 사용하기 때문에 소멸시킬 대상이 없음
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
