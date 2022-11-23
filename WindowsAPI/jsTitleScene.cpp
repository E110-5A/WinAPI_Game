#include "jsTitleScene.h"
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsBGObj.h"
#include "jsCamera.h"
#include "jsApplication.h"

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
		BGObj* bg = new BGObj();
		bg->SetImage(L"TitleBG", L"Title_BG.bmp");
		bg->Initialize();
		AddGameObject(bg, eColliderLayer::BackGround);
		// 회전하는 배경 추가
		// 이동하는 배경 추가

		// SinglePlay 버튼 추가
		// Option 버튼 추가
		// Quit 버튼 추가
	}
	void TitleScene::Tick()
	{
		Scene::Tick();
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Play);
		}
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[40] = {};
		swprintf_s(szFloat, 40, L"Title Scene");
		int strLen = wcsnlen_s(szFloat, 40);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}
	void TitleScene::Enter()
	{
		Camera::SetCameraEffect(eCameraEffect::FadeIn);
	}
	void TitleScene::Exit()
	{
	}
}