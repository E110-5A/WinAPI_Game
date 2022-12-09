#include "jsTestScene.h"
#include "jsApplication.h"

// manager
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCollisionManager.h"

// tool
#include "jsMapToolScene.h"

// ui
#include "jsUIManager.h"
#include "jsHUD.h"
#include "jsButton.h"

// obj
#include "jsPlayer.h"
#include "jsBGObj.h"
#include "jsObject.h"
#include "jsGround.h"
#include "jsPlayerProjectile.h"
#include "jsImp.h"
#include "jsSmallChest.h"
#include "jsLargeChest.h"
#include "jsGoldenChest.h"

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
		//SceneManager::LoadMap<MapToolScene>(L"..\\Resources\\Tile\\debugTest", eSceneType::MapTool);
		/*Scene* scene = SceneManager::GetScene(eSceneType::MapTool);
		MapToolScene* toolScene = dynamic_cast<MapToolScene*>(scene);
		toolScene->LoadTilePalette(L"..\\Resources\\Tile\\isthatbug");*/


		// 배경 오브젝트
		GameObject* testGround = object::Instantiate<Ground>(eColliderLayer::Ground, Pos(600.0f, 570.0f));
		Collider* gCollider = testGround->GetComponent<Collider>();
		gCollider->SetSize(Vector2(6600.0f, 50.0f));

		// 오브젝트 추가
		Player* pPlayer = object::Instantiate<Player>(eColliderLayer::Player, Pos(440.f, 480.f));
		
		for (int idx = 0; idx < WEAPON_POOL; ++idx)
		{
			mPlayerAttack[idx] = object::Instantiate<PlayerProjectile>(eColliderLayer::Player_Projectile);
			mPlayerAttack[idx]->SetOwner(pPlayer);
		}

		Monster* imp = object::Instantiate<Imp>(eColliderLayer::Monster, Pos(700.f, 480.f));
		Monster* imp2 = object::Instantiate<Imp>(eColliderLayer::Monster, Pos(750.f, 480.f));
		Monster* imp3 = object::Instantiate<Imp>(eColliderLayer::Monster, Pos(800.f, 480.f));

		EventObject* smallBox = object::Instantiate<SmallChest>(eColliderLayer::Chest, Pos(70.0f, 480.0f));
		EventObject* largeBox = object::Instantiate<LargeChest>(eColliderLayer::Chest, Pos(140.0f, 480.0f));
		EventObject* goldenBox = object::Instantiate<GoldenChest>(eColliderLayer::Chest, Pos(220.0f, 480.0f));

		


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
		TextOut(hdc, 5, 10, szFloat, strLen);
	}

	void TestScene::Enter()
	{
		CollisionManager::SetLayer(eColliderLayer::Ground, eColliderLayer::Player, true);
		CollisionManager::SetLayer(eColliderLayer::Ground, eColliderLayer::Monster, true);

		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Chest, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Monster_Projectile, true);
		
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Projectile, true);
	}

	void TestScene::Exit()
	{
	}
}