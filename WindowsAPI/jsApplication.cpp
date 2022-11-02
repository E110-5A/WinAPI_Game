#include "jsApplication.h"
#include "jsSceneManager.h"
#include "jsTime.h"
#include "jsInput.h"
#include "jsResources.h"
#include "jsCollisionManager.h"
#include "jsCamera.h"

namespace js
{
	Application::Application()
	{
		mWindowData.clear();
	}

	Application::~Application()
	{
		Resources::Release();
		SceneManager::Release();
		ReleaseDC(mWindowData.hWnd, mWindowData.hdc);
		ReleaseDC(mWindowData.hWnd, mWindowData.backBuffer);
	}

	void Application::InitializeWindow(WindowData _data)
	{
		mWindowData = _data;
		mWindowData.hdc = GetDC(_data.hWnd);

		RECT rect = { 0,0,mWindowData.width, mWindowData.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(mWindowData.hWnd, nullptr, 0, 0
			, rect.right - rect.left, rect.bottom - rect.top, 0);

		ShowWindow(mWindowData.hWnd, true);


		mWindowData.backTexture 
			= CreateCompatibleBitmap(mWindowData.hdc, mWindowData.width, mWindowData.height);

		mWindowData.backBuffer
			= CreateCompatibleDC(mWindowData.hdc);
		HBITMAP defaultBitMap
			= (HBITMAP)SelectObject(mWindowData.backBuffer, mWindowData.backTexture);

		DeleteObject(defaultBitMap);

		mPens[(UINT)ePenColor::Red] = CreatePen(PS_SOLID, 1, RGB(255,0,0));
		mPens[(UINT)ePenColor::Green] = CreatePen(PS_SOLID, 1, RGB(0,255,0));
		mPens[(UINT)ePenColor::Blue] = CreatePen(PS_SOLID, 1, RGB(0,0,255));
		
		mBrushs[(UINT)eBrushColor::Transparent] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		mBrushs[(UINT)eBrushColor::Black] = (HBRUSH)GetStockObject(BLACK_BRUSH);
		mBrushs[(UINT)eBrushColor::Gray] = (HBRUSH)GetStockObject(GRAY_BRUSH);
		mBrushs[(UINT)eBrushColor::White] = (HBRUSH)GetStockObject(WHITE_BRUSH);
	}

	void Application::Initialize(WindowData _data)
	{
		InitializeWindow(_data);

		Time::Initialize();
		jsInput::Initialize();
		SceneManager::Initialize();
		Camera::Initialize();
	}

	void Application::Tick()
	{
		Time::Tick();
		jsInput::Tick();

		Camera::Tick();
		SceneManager::Tick();
		CollisionManager::Tick();
		

		Brush brush(mWindowData.backBuffer, mBrushs[(UINT)eBrushColor::Gray]);
		Rectangle(mWindowData.backBuffer, -1, -1, mWindowData.width + 1, mWindowData.height + 1);
		// 랜더링 전에 화면 초기화 진행
		SceneManager::Render(mWindowData.backBuffer);
		jsInput::Render(mWindowData.backBuffer);
		Time::Render(mWindowData.backBuffer);


		BitBlt(mWindowData.hdc, 0, 0, mWindowData.width, mWindowData.height,
			mWindowData.backBuffer, 0, 0, SRCCOPY);
	}
}

