#include "framework.h"
#include "WindowsAPI.h"

#include "jsMapToolScene.h"

#include "jsApplication.h"
#include "jsSceneManager.h"
#include "jsInput.h"
#include "jsCamera.h"

#include "jsScene.h"

#include "jsImage.h"



namespace js
{
	
    MapToolScene::MapToolScene()
        : mTileIndex(0)
	{
		mTilePalette = new TilePalette();
	}
    MapToolScene::~MapToolScene()
	{
		delete mTilePalette;
	}
	void MapToolScene::Initialize()
	{
	}


	void MapToolScene::Tick()
	{
        Camera::CameraMove();

        if (mTilePalette)
            mTilePalette->Tick();
	}
	void MapToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t szFloat[40] = {};
		swprintf_s(szFloat, 40, L"Tool Scene");
		int strLen = wcsnlen_s(szFloat, 40);
		TextOut(hdc, 5, 10, szFloat, strLen);



		WindowData mainWindow = Application::GetInstance().GetWindowData();

		HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 125, 0));
		HPEN prevPen = (HPEN)SelectObject(hdc, greenPen);

		int maxRow = mainWindow.height / TILE_SIZE * TILE_SCALE + 1;
        

        for (int idx = 0; idx < maxRow; idx++)
        {
            MoveToEx(hdc,
                Camera::CalculateObjectPos(Vector2(0, TILE_SIZE * idx * TILE_SCALE)).x, 
                Camera::CalculateObjectPos(Vector2(0, TILE_SIZE * idx * TILE_SCALE)).y, nullptr);
            LineTo(hdc,
                Camera::CalculateObjectPos(Vector2(mainWindow.width, TILE_SIZE * idx * TILE_SCALE)).x, 
                Camera::CalculateObjectPos(Vector2(mainWindow.width, TILE_SIZE * idx * TILE_SCALE)).y);
        }
        int maxCol = mainWindow.width / TILE_SIZE * TILE_SCALE + 1;
        for (int idx = 0; idx < maxCol; idx++)
        {
            MoveToEx(hdc,
                Camera::CalculateObjectPos(Vector2(TILE_SIZE * idx * TILE_SCALE, 0)).x, 
                Camera::CalculateObjectPos(Vector2(TILE_SIZE * idx * TILE_SCALE, 0)).y, nullptr);
            LineTo(hdc,
                Camera::CalculateObjectPos(Vector2(TILE_SIZE * idx * TILE_SCALE, mainWindow.height)).x, 
                Camera::CalculateObjectPos(Vector2(TILE_SIZE * idx * TILE_SCALE, mainWindow.height)).y);
        }

		(HPEN)SelectObject(hdc, prevPen);
		DeleteObject(greenPen);
	}


	void MapToolScene::Enter()
	{
		Application::GetInstance().SetMenuBar(true);
	}
	void MapToolScene::Exit()
	{
		Application::GetInstance().SetMenuBar(false);
	}
    void MapToolScene::SaveTilePalette()
    {
        mTilePalette->Save();
    }
    void MapToolScene::LoadTilePalette()
    {
        mTilePalette->Load();
    }
    void MapToolScene::LoadTilePalette(const std::wstring& path)
    {
        mTilePalette->Load(path);
    }


    void MapToolScene::SaveObjectPalette()
    {
    }
    void MapToolScene::LoadObjectPalette()
    {
    }
    void MapToolScene::LoadObjectPalette(const std::wstring& path)
    {
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
        js::MapToolScene* toolScene = dynamic_cast<js::MapToolScene*>(Scene);
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
        case IDM_ABOUT:
        {
            int a = 0;
        }
        break;
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
            js::MapToolScene* toolScene = dynamic_cast<js::MapToolScene*>(Scene);

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
        js::MapToolScene* toolScene = dynamic_cast<js::MapToolScene*>(Scene);
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
