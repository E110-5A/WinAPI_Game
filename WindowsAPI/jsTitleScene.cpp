#include "jsTitleScene.h"
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsBGObj.h"
#include "jsCamera.h"

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