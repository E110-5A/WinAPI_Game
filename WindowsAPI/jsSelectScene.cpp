#include "jsSelectScene.h"

//매니저
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCamera.h"
#include "jsUIManager.h"

// 오브젝트
#include "jsObject.h"
#include "jsBGObj.h"
#include "jsCommandoRun.h"


namespace js
{
	SelectScene::SelectScene()
	{
	}
	SelectScene::~SelectScene()
	{
	}
	void SelectScene::Initialize()
	{
		// 배경 오브젝트
		

		// 버튼 UI
		UIManager::Push(eUIType::PlayBtn);
	}
	void SelectScene::Tick()
	{
		Scene::Tick();
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Select);
		}
	}
	void SelectScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[40] = {};
		swprintf_s(szFloat, 40, L"Title Scene");
		int strLen = wcsnlen_s(szFloat, 40);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}
	void SelectScene::Enter()
	{
		Camera::SetCameraEffect(eCameraEffect::FadeIn);
	}
	void SelectScene::Exit()
	{
	}
}