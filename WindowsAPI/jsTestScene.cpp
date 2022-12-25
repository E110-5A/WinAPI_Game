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
#include "jsDifficultyHUD.h"

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
		// ������ ũ��
		// 1280
		// 720
		
		// �� �ε�
		TileLoadTest();

		// ��� ������Ʈ
		BGTest();

		// ������Ʈ �߰�
		ObjectTest();

		// ui �߰�
		/*UIManager::Push(eUIType::TEST);
		UIManager::Push(eUIType::PlayerInfo);
		HUD* hud = UIManager::GetUIInstant<HUD>(eUIType::PlayerInfo);
		hud->SetTarget(pPlayer);
		UIManager::Push(eUIType::ITEM_SELECT);*/
	}

	void TestScene::Tick()
	{
		// ������Ʈ tick �� ȣ���Ѵ�.
		Scene::Tick();

		GameManager::Playing();
		// ESC �������
		/*
		*  - �ð� ���� ���߱�
		*  - �޴� UI �ҷ�����
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
		SceneManager::LoadMap<MapToolScene>(L"..\\Resources\\Tile\\STG1\\stage1", eSceneType::MapTool);
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
		// ��Ÿ ������Ʈ ����
		EventObject* smallBox = object::Instantiate<SmallChest>(eColliderLayer::EventObject, Pos(70.0f, 610.0f));
		EventObject* largeBox = object::Instantiate<LargeChest>(eColliderLayer::EventObject, Pos(140.0f, 610.0f));
		EventObject* goldenBox = object::Instantiate<GoldenChest>(eColliderLayer::EventObject, Pos(220.0f, 610.0f));
		
		// ���� ����
		//Monster* imp = object::Instantiate<Imp>(  eColliderLayer::Monster, Pos(700.f, 550.0f));
		/*Monster* imp2 = object::Instantiate<Imp>(eColliderLayer::Monster, Pos(750.f, 550.0f));
		Monster* imp3 = object::Instantiate<Imp>(eColliderLayer::Monster, Pos(800.f, 550.0f));*/

		// �÷��̾� ��ȣ�ۿ� �׽�Ʈ
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
		// ui �߰�
		UIManager::Push(eUIType::PlayerInfo);

		BarUI* hpBar = UIManager::GetUIInstant<BarUI>(eUIType::HpBar);
		hpBar->SetType(eBarType::HP);
		hpBar->SetHealth(GameManager::GetPlayerInfo()->stat->playerHealth);


		BarUI* expBar = UIManager::GetUIInstant<BarUI>(eUIType::ExpBar);
		expBar->SetType(eBarType::EXP);
		expBar->SetExp(GameManager::GetPlayerInfo());


		Player* player = GameManager::GetPlayer();
		Icon* z = UIManager::GetUIInstant<Icon>(eUIType::Z);
		z->SetSkillInfo(player->GetDubleTabInfo());
		Icon* x = UIManager::GetUIInstant<Icon>(eUIType::X);
		x->SetSkillInfo(player->GetFMJInfo());
		Icon* c = UIManager::GetUIInstant<Icon>(eUIType::C);
		c->SetSkillInfo(player->GetTacticalDiveInfo());
		Icon* v = UIManager::GetUIInstant<Icon>(eUIType::V);
		v->SetSkillInfo(player->GetSupressiveFireInfo());

		UIManager::Push(eUIType::Difficulty);

		DifficultyHUD* difficultyHud = UIManager::GetUIInstant<DifficultyHUD>(eUIType::DifficultyBar);
		difficultyHud->SetDifficulty(GameManager::GetDifficulty());
	}

	// �浹 �� UI ����
	void TestScene::Enter()
	{
		GameManager::AddObject();
		Player* player = GameManager::GetPlayer();
		player->SetPos(Pos(440.f, 576.f));

		SetLayer();
		SetUI();

	}

	// UI ���� ������
	void TestScene::Exit()
	{
		
	}
}