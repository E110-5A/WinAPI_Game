#include "jsTitleScene.h"
#include "jsApplication.h"

// 매니저
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
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		// 배경 오브젝트
		//BGObj* title = new BGObj();
		//AddGameObject(title, eColliderLayer::BackGroundImage);
		BGObj* title = object::Instantiate<BGObj>(eColliderLayer::BackGroundImage);
		title->SetImage(L"TitleBG", L"Title_BG.bmp");

		// 회전하는 행성 배경 추가
		BGObj* ground = object::Instantiate<BGObj>(eColliderLayer::BackGroundImage, Vector2(380.0f, 560.0f));
		ground->SetImage(L"TitleGround", L"ground.bmp");
		// 이동하는 플레이어 배경 추가
		CommandoRun* pObj = object::Instantiate<CommandoRun>(eColliderLayer::BGObj, Vector2(640.0f, 618.0f));


	}
	void TitleScene::Tick()
	{
		Scene::Tick();
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Select);
		}
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[40] = {};
		swprintf_s(szFloat, 40, L"Title Scene");
		int strLen = wcsnlen_s(szFloat, 40);
		TextOut(hdc, 5, 10, szFloat, strLen);
	}
	void TitleScene::Enter()
	{
		Camera::SetCameraEffect(eCameraEffect::FadeIn);
		// UI 로딩
		UIManager::Push(eUIType::SelectBtn);
		UIManager::Push(eUIType::OptionBtn);
		UIManager::Push(eUIType::QuitBtn);
	}
	void TitleScene::Exit()
	{
		// UI 지워주기?
		UIManager::Pop(eUIType::SelectBtn);
		UIManager::Pop(eUIType::OptionBtn);
		UIManager::Pop(eUIType::QuitBtn);
	}
}