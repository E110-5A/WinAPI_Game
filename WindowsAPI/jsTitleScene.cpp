#include "jsTitleScene.h"
#include "jsApplication.h"

// �Ŵ���
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCamera.h"
#include "jsUIManager.h"

// ������Ʈ
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
		// ��� ������Ʈ
		//BGObj* title = new BGObj();
		//AddGameObject(title, eColliderLayer::BackGround);
		BGObj* title = object::Instantiate<BGObj>(eColliderLayer::BackGround);
		title->SetImage(L"TitleBG", L"Title_BG.bmp");

		// ȸ���ϴ� �༺ ��� �߰�
		BGObj* ground = object::Instantiate<BGObj>(eColliderLayer::BackGround, Vector2(380.0f, 560.0f));
		ground->SetImage(L"TitleGround", L"ground.bmp");
		// �̵��ϴ� �÷��̾� ��� �߰�
		CommandoRun* pObj = object::Instantiate<CommandoRun>(eColliderLayer::BGObj, Vector2(640.0f, 618.0f));


		// ui ������Ʈ
		 
		UIManager::Push(eUIType::SelectBtn);
		UIManager::Push(eUIType::QuitBtn);
		UIManager::Push(eUIType::OptionBtn);
		/*UIManager::Push(eUIType::TEST);
		UIManager::Push(eUIType::PLAYER_INFO);
		HUD* hud = UIManager::GetUIInstant<HUD>(eUIType::PLAYER_INFO);
		hud->SetTarget(pPlayer);
		UIManager::Push(eUIType::ITEM_SELECT);*/
		
		// SinglePlay ��ư �߰�
		
		// Option ��ư �߰�
		// Quit ��ư �߰�
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
		TextOut(hdc, 10, 30, szFloat, strLen);
	}
	void TitleScene::Enter()
	{
		Camera::SetCameraEffect(eCameraEffect::FadeIn);
	}
	void TitleScene::Exit()
	{
		// UI �����ֱ�?
	}
}