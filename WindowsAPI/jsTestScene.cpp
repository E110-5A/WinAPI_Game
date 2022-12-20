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
#include "jsObject.h"
#include "jsPlayerProjectile.h"
#include "jsImp.h"
#include "jsSmallChest.h"
#include "jsLargeChest.h"
#include "jsGoldenChest.h"
#include "jsItemObject.h"

// env
#include "jsBGObj.h"
#include "jsPlatform.h"
#include "jsLadder.h"


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
		TileLoadTest();

		// 배경 오브젝트
		BGTest();

		// 오브젝트 추가
		ObjectTest();



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

	void TestScene::TileLoadTest()
	{
		SceneManager::LoadMap<MapToolScene>(L"..\\Resources\\Tile\\pls", eSceneType::MapTool);
	}

	void TestScene::BGTest()
	{
		Platform* leftGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(0.0f, 384.0f));
		leftGround->SetColliderSize(Size(GRID_SIZE, GRID_SIZE * 5));
		leftGround->SetColliderOffset(Vector2(GRID_SIZE / 2, GRID_SIZE * 5 / 2));

		Platform* mainGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(64.0f, 640.0f));
		mainGround->SetColliderSize(Size(GRID_SIZE * 16, GRID_SIZE));
		mainGround->SetColliderOffset(Vector2(GRID_SIZE * 8, GRID_SIZE / 2));

		Platform* secondGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(64.0f, 512.0f));
		secondGround->SetColliderSize(Size(GRID_SIZE * 16, GRID_SIZE));
		secondGround->SetColliderOffset(Vector2(GRID_SIZE * 8, GRID_SIZE / 2));

		/*Platform* rock = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(256.0f, 576.0f));
		rock->SetColliderSize(Size(GRID_SIZE, GRID_SIZE));
		rock->SetColliderOffset(Pos(GRID_SIZE / 2, GRID_SIZE / 2));*/

		Ladder* ladder = object::Instantiate<Ladder>(eColliderLayer::Ladder, Pos(256.0f, 512.0f));
		ladder->SetColliderSize(Size(GRID_SIZE, GRID_SIZE * 2));
		ladder->SetColliderOffset(Vector2(GRID_SIZE / 2, GRID_SIZE * 2 / 2));
	}

	void TestScene::ObjectTest()
	{
		// 플레이어 설정
		Player* pPlayer = object::Instantiate<Player>(eColliderLayer::Player, Pos(440.f, 576.0f));

		// 투사체 풀링
		for (int idx = 0; idx < PLAYER_PROJECTILE_POOL; ++idx)
		{
			mPlayerAttack[idx] = object::Instantiate<PlayerProjectile>(eColliderLayer::Player_Projectile);
			mPlayerAttack[idx]->SetPlayerInfo(pPlayer);
		}

		// 기타 오브젝트 설정
		EventObject* smallBox = object::Instantiate<SmallChest>(eColliderLayer::EventObject, Pos(70.0f, 610.0f));
		EventObject* largeBox = object::Instantiate<LargeChest>(eColliderLayer::EventObject, Pos(140.0f, 610.0f));
		EventObject* goldenBox = object::Instantiate<GoldenChest>(eColliderLayer::EventObject, Pos(220.0f, 610.0f));
		
		// 몬스터 설정
		//Monster* imp = object::Instantiate<Imp>(  eColliderLayer::Monster, Pos(700.f, 550.0f));
		/*Monster* imp2 = object::Instantiate<Imp>(eColliderLayer::Monster, Pos(750.f, 550.0f));
		Monster* imp3 = object::Instantiate<Imp>(eColliderLayer::Monster, Pos(800.f, 550.0f));*/
	}

	// 충돌 및 UI 설정
	void TestScene::Enter()
	{
		CollisionManager::SetLayer(eColliderLayer::Platform, eColliderLayer::Head, true);
		CollisionManager::SetLayer(eColliderLayer::Platform, eColliderLayer::Foot, true);
		CollisionManager::SetLayer(eColliderLayer::Platform, eColliderLayer::Player, true);
		CollisionManager::SetLayer(eColliderLayer::Platform, eColliderLayer::Monster, true);

		CollisionManager::SetLayer(eColliderLayer::Ladder, eColliderLayer::Head, true);
		CollisionManager::SetLayer(eColliderLayer::Ladder, eColliderLayer::Foot, true);
		CollisionManager::SetLayer(eColliderLayer::Ladder, eColliderLayer::Player, true);

		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::EventObject, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Item, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::DamagingObj, true);
		
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::EventObject, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Projectile, true);
	}

	// UI 끄고 나가셈
	void TestScene::Exit()
	{
	}
}