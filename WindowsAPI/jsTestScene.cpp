#include "jsTestScene.h"
#include "jsApplication.h"

// manager
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCollisionManager.h"

#include "jsToolScene.h"

// ui
#include "jsUIManager.h"
#include "jsHUD.h"
#include "jsButton.h"

// obj
#include "jsPlayer.h"
#include "jsMonster.h"
#include "jsBGObj.h"
#include "jsObject.h"
#include "jsGround.h"

// component
#include "jsCollider.h"

namespace js
{
	TestScene::TestScene()
	{
	}

	TestScene::~TestScene()
	{
	}
	
	void TestScene::Initialize()
	{
		// 윈도우 크기
		// 1280
		// 720
		
		// 맵 로딩		
		SceneManager::LoadMap<ToolScene>(L"..\\Resources\\Tile\\testMap",eSceneType::Tool);


		// 오브젝트 추가
		GameObject* pPlayer = object::Instantiate<Player>(eColliderLayer::Player, Pos(440.f, 380.f));

		GameObject* testGround = object::Instantiate<Ground>(eColliderLayer::Ground, Pos(600.0f, 600.0f));
		Collider* gCollider = testGround->GetComponent<Collider>();
		gCollider->SetSize(Vector2(6600.0f, 50.0f));
		//mons[0] = object::Instantiate<Monster>(eColliderLayer::Monster);


		// ui 추가
		/*UIManager::Push(eUIType::TEST);
		UIManager::Push(eUIType::PLAYER_INFO);
		HUD* hud = UIManager::GetUIInstant<HUD>(eUIType::PLAYER_INFO);
		hud->SetTarget(pPlayer);
		UIManager::Push(eUIType::ITEM_SELECT);*/
	}

	void TestScene::Tick()
	{
		// 오브젝트 tick 을 호출한다.
		Scene::Tick();

		// ESC 누를경우
		/*
		*  - 시간 진행 멈추기
		*  - 메뉴 UI 불러오기
		*
		*/

		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Title);
		}
	}

	void TestScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		//
		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Test Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}

	void TestScene::Enter()
	{
		CollisionManager::SetLayer(eColliderLayer::Ground, eColliderLayer::Player, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Projectile, true);
	}

	void TestScene::Exit()
	{
	}
}