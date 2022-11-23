#include <Windows.h>
#include "framework.h"
#include "WindowsAPI.h"

#include "jsApplication.h"
#include "jsSceneManager.h"
#include "jsTime.h"
#include "jsInput.h"
#include "jsResources.h"
#include "jsCollisionManager.h"
#include "jsCamera.h"
#include "jsUIManager.h"
#include "jsSoundManager.h"
namespace js
{
	void Application::Initialize(WindowData data)
	{
		InitializeWindow(data);

		Time::Initialize();
		Input::Initialize();
		UIManager::Initialize();
		SceneManager::Initialize();
		Camera::Initialize();
		SoundManager::Initialize();
	}

	void Application::InitializeAtlasWindow(WindowData data)
	{
		mAtlasWindowData = data;
		mAtlasWindowData.hdc = GetDC(data.hWnd);
	}

	void Application::InitializeCollisionWindow(WindowData data)
	{
	}

	void Application::Tick()
	{
		Time::Tick();
		Input::Tick();

		SceneManager::Tick();
		CollisionManager::Tick();
		UIManager::Tick();
		Camera::Tick();


		Brush brush(mWindowData.backBuffer, mBrushs[(UINT)eBrushColor::Gray]);
		Rectangle(mWindowData.backBuffer, -1, -1, mWindowData.width + 1, mWindowData.height + 1);
		// 랜더링 전에 화면 초기화 진행
		SceneManager::Render(mWindowData.backBuffer);
		UIManager::Render(mWindowData.backBuffer);
		Camera::Render(mWindowData.backBuffer);
		
		Input::Render(mWindowData.backBuffer);
		Time::Render(mWindowData.backBuffer);


		BitBlt(mWindowData.hdc, 0, 0, mWindowData.width, mWindowData.height,
			mWindowData.backBuffer, 0, 0, SRCCOPY);


		SceneManager::DestroyGameObject();

	}
	void Application::SetMenuBar(bool power)
	{
		SetMenu(mWindowData.hWnd, mMenu);

		RECT rect = { 0,0,mWindowData.width, mWindowData.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, power);

		SetWindowPos(mWindowData.hWnd, nullptr, 0, 0
			, rect.right - rect.left, rect.bottom - rect.top
			, SWP_NOMOVE | SWP_NOZORDER);

		ShowWindow(mWindowData.hWnd, true);
	}



	eSceneType Application::GetPlaySceneType()
	{
		return SceneManager::GetPlaySceneType();
	}

	Application::Application()
	{
		mWindowData.clear();
	}

	Application::~Application()
	{
		SceneManager::Release();
		Resources::Release();
		UIManager::Release();

		ReleaseDC(mWindowData.hWnd, mWindowData.hdc);
		ReleaseDC(mWindowData.hWnd, mWindowData.backBuffer);
	}

	void Application::InitializeWindow(WindowData data)
	{
		mWindowData = data;
		mWindowData.hdc = GetDC(data.hWnd);


		RECT rect = { 0,0,mWindowData.width, mWindowData.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mWindowData.hWnd, nullptr, 0, 0
			, rect.right - rect.left, rect.bottom - rect.top
			, SWP_NOMOVE | SWP_NOZORDER);
		ShowWindow(mWindowData.hWnd, true);


		mWindowData.backTexture
			= CreateCompatibleBitmap(mWindowData.hdc, mWindowData.width, mWindowData.height);
		mWindowData.backBuffer
			= CreateCompatibleDC(mWindowData.hdc);
		HBITMAP defaultBitMap
			= (HBITMAP)SelectObject(mWindowData.backBuffer, mWindowData.backTexture);
		DeleteObject(defaultBitMap);


		mPens[(UINT)ePenColor::Red] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		mPens[(UINT)ePenColor::Green] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		mPens[(UINT)ePenColor::Blue] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

		mBrushs[(UINT)eBrushColor::Transparent] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		mBrushs[(UINT)eBrushColor::Black] = (HBRUSH)GetStockObject(BLACK_BRUSH);
		mBrushs[(UINT)eBrushColor::Gray] = (HBRUSH)GetStockObject(GRAY_BRUSH);
		mBrushs[(UINT)eBrushColor::White] = (HBRUSH)GetStockObject(WHITE_BRUSH);

		mMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_WINDOWSAPI));
	}
}

