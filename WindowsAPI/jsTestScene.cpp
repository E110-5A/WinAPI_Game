#include "jsTestScene.h"
#include "jsApplication.h"

// manager
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCollisionManager.h"
#include "jsCamera.h"
#include "jsGameManager.h"

// tool
#include "jsMapToolScene.h"

// ui
#include "jsUIManager.h"
#include "jsHUD.h"
#include "jsButton.h"
#include "jsBarUI.h"
#include "jsIcon.h"
// obj
#include "jsPlayer.h"
#include "jsObject.h"
#include "jsPlayerProjectile.h"
#include "jsImp.h"
#include "jsSmallChest.h"
#include "jsLargeChest.h"
#include "jsGoldenChest.h"
#include "jsItemObject.h"
#include "jsDamageObject.h"

// env
#include "jsBGObj.h"
#include "jsPlatform.h"
#include "jsLadder.h"
#include "jsPropellant.h"

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
		UIManager::Push(eUIType::PlayerInfo);
		HUD* hud = UIManager::GetUIInstant<HUD>(eUIType::PlayerInfo);
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

		Platform* secondGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(128.0f, 512.0f));
		secondGround->SetColliderSize(Size(GRID_SIZE * 5, GRID_SIZE));
		secondGround->SetColliderOffset(Vector2(GRID_SIZE * 5 / 2, GRID_SIZE / 2));

		Platform* thirdGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(702.0f, 448.0f));
		thirdGround->SetColliderSize(Size(GRID_SIZE * 5, GRID_SIZE * 2));
		thirdGround->SetColliderOffset(Vector2(GRID_SIZE * 5 / 2, GRID_SIZE * 2 / 2));

		Ladder* ladder = object::Instantiate<Ladder>(eColliderLayer::Ladder, Pos(256.0f, 512.0f));
		ladder->SetColliderSize(Size(GRID_SIZE, GRID_SIZE * 2));
		ladder->SetColliderOffset(Vector2(GRID_SIZE / 2, GRID_SIZE * 2 / 2));

		Propellant* propellant = object::Instantiate<Propellant>(eColliderLayer::EventObject, Pos(610, 550));
	}

	void TestScene::ObjectTest()
	{
		GameManager::AddObject();
		Player* player = GameManager::GetPlayer();
		player->SetPos(Pos(440.f, 576.f));

		//// 플레이어 설정
		//Player* player = object::Instantiate<Player>(eColliderLayer::Player, Pos(440.f, 576.0f));
		//// 투사체 풀링
		//for (int idx = 0; idx < PLAYER_PROJECTILE_POOL; ++idx)
		//{
		//	mPlayerAttack[idx] = object::Instantiate<PlayerProjectile>(eColliderLayer::Player_Projectile);
		//	mPlayerAttack[idx]->SetPlayerInfo(player);
		//}

		// 기타 오브젝트 설정
		EventObject* smallBox = object::Instantiate<SmallChest>(eColliderLayer::EventObject, Pos(70.0f, 610.0f));
		EventObject* largeBox = object::Instantiate<LargeChest>(eColliderLayer::EventObject, Pos(140.0f, 610.0f));
		EventObject* goldenBox = object::Instantiate<GoldenChest>(eColliderLayer::EventObject, Pos(220.0f, 610.0f));
		
		// 몬스터 설정
		//Monster* imp = object::Instantiate<Imp>(  eColliderLayer::Monster, Pos(700.f, 550.0f));
		/*Monster* imp2 = object::Instantiate<Imp>(eColliderLayer::Monster, Pos(750.f, 550.0f));
		Monster* imp3 = object::Instantiate<Imp>(eColliderLayer::Monster, Pos(800.f, 550.0f));*/

		// 플레이어 상호작용 테스트
		DamageObject* damageTest = object::Instantiate<DamageObject>(eColliderLayer::DamageObject, Pos(GRID_SIZE*5,GRID_SIZE*9));
	}

	void TestScene::SetLayer()
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
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::DamageObject, true);

		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::EventObject, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Projectile, true);
	}

	void TestScene::SetUI()
	{
		// ui 추가
		UIManager::Push(eUIType::PlayerInfo);

		BarUI* hpBar = UIManager::GetUIInstant<BarUI>(eUIType::HpBar);
		hpBar->SetType(eBarType::HP);
		hpBar->SetHealth(GameManager::GetPlayerInfo()->stat->playerHealth);


		BarUI* expBar = UIManager::GetUIInstant<BarUI>(eUIType::ExpBar);
		expBar->SetType(eBarType::EXP);
		expBar->SetExp(GameManager::GetPlayerInfo());

		Player* player = GameManager::GetPlayer();
		float zCooldown = player->GetDubleTabInfo().coolDown;
		float zTime = player->GetDubleTabInfo().coolDownTime;
		float xCooldown = player->GetFMJInfo().coolDown;
		float xTime = player->GetFMJInfo().coolDownTime;

		float cCooldown = player->GetTacticalDiveInfo().coolDown;
		float cTime = player->GetTacticalDiveInfo().coolDownTime;
		float vCooldown = player->GetSupressiveFireInfo().coolDown;
		float vTime = player->GetSupressiveFireInfo().coolDownTime;

		Icon* z = UIManager::GetUIInstant<Icon>(eUIType::Z);
		z->SetMaxValue(zCooldown);
		z->SetCurValue(zTime);
		Icon* x = UIManager::GetUIInstant<Icon>(eUIType::X);
		x->SetMaxValue(xCooldown);
		x->SetCurValue(xTime);
		Icon* c = UIManager::GetUIInstant<Icon>(eUIType::C);
		c->SetMaxValue(cCooldown);
		c->SetCurValue(cTime);
		Icon* v = UIManager::GetUIInstant<Icon>(eUIType::V);
		v->SetMaxValue(vCooldown);
		v->SetCurValue(vTime);
	}

	// 충돌 및 UI 설정
	void TestScene::Enter()
	{
		SetLayer();
		SetUI();		
	}

	// UI 끄고 나가셈
	void TestScene::Exit()
	{
		UIManager::Pop(eUIType::PlayerInfo);
		UIManager::Pop(eUIType::HpBar);
		UIManager::Pop(eUIType::ExpBar);
	}
}