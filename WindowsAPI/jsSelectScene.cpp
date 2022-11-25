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
		BGObj* selectBG = object::Instantiate<BGObj>(eColliderLayer::BackGround);
		selectBG->SetImage(L"SelectBG", L"SelectBG.bmp");

		BGObj* selectInfo = object::Instantiate<BGObj>(eColliderLayer::BackGround,Vector2(60.0f, 100.0f));
		selectInfo->SetImage(L"select_Info", L"select_Info.bmp");

		BGObj* selectList = object::Instantiate<BGObj>(eColliderLayer::BackGround, Vector2(1000.0f, 80.0f));
		selectList->SetImage(L"select_list", L"select_list.bmp");
				
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

		// UI 로딩
		UIManager::Push(eUIType::PlayBtn);
	}
	void SelectScene::Exit()
	{
		// UI 없애기
		UIManager::Pop(eUIType::PlayBtn);
	}
}