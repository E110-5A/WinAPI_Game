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
#include "jsTeleporter.h"

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
		InitBG();
		// ������Ʈ �߰�
		InitObject();
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
		// SceneManager::LoadMap<MapToolScene>(L"..\\Resources\\Tile\\STGA\\stage1", eSceneType::MapTool);
	}

	void TestScene::InitBG()
	{
		Platform* leftGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(0.0f, 384.0f));
		leftGround->SetColliderSize(Size(GRID_SIZE, GRID_SIZE * 5));
		leftGround->SetColliderOffset(Vector2(GRID_SIZE / 2, GRID_SIZE * 5 / 2));

		/*Platform* mainGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(64.0f, 640.0f));
		mainGround->SetColliderSize(Size(GRID_SIZE * 16, GRID_SIZE));
		mainGround->SetColliderOffset(Vector2(GRID_SIZE * 8, GRID_SIZE / 2));*/

		Platform* secondGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(64.0f, 512.0f));
		secondGround->SetColliderSize(Size(GRID_SIZE * 5, GRID_SIZE));
		secondGround->SetColliderOffset(Vector2(GRID_SIZE * 5 / 2, GRID_SIZE / 2));

		//Platform* thirdGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(702.0f, 448.0f));
		//thirdGround->SetColliderSize(Size(GRID_SIZE * 5, GRID_SIZE * 2));
		//thirdGround->SetColliderOffset(Vector2(GRID_SIZE * 5 / 2, GRID_SIZE * 2 / 2));

		Ladder* ladder = object::Instantiate<Ladder>(eColliderLayer::Ladder, Pos(256.0f, 512.0f));
		ladder->SetColliderSize(Size(GRID_SIZE, GRID_SIZE * 2));
		ladder->SetColliderOffset(Vector2(GRID_SIZE / 2, GRID_SIZE * 2 / 2));

		Propellant* propellant = object::Instantiate<Propellant>(eColliderLayer::Propellant, Pos(610, 550));
	}

	void TestScene::InitObject()
	{
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

		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Propellant, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Chest, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Item, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::DamageObject, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Teleporter, true);

		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Propellant, true);
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
		Platform* mainGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(64.0f, 640.0f));
		mainGround->SetColliderSize(Size(GRID_SIZE * 16, GRID_SIZE));
		mainGround->SetColliderOffset(Vector2(GRID_SIZE * 8, GRID_SIZE / 2));

		GameManager::SetSpawnPlatform(mainGround);

		GameManager::AddObject();
		Player* player = GameManager::GetPlayer();
		player->SetPos(Pos(440.f, 576.f));

		// ������ ���� ����
		for (int idx = 0; idx < CHEST_POOL; ++idx)
		{
			mChest[idx] = GameManager::GetChest(idx);
		}
		mChest[0]->SetPos(Pos(384.0f, 896.0f));
		mChest[1]->SetPos(Pos(1280.0f, 640.0f));
		mChest[2]->SetPos(Pos(1536.0f, 640.0f));
		mChest[3]->SetPos(Pos(2368.0f, 640.0f));
		// �ڷ����� ����
		mTeleporter = GameManager::GetTeleporter();
		mTeleporter->SetPos(Pos(2112.f, 640.f));

		SetLayer();
		SetUI();
		GameManager::SetPlayable(true);
	}

	// UI ���� ������
	void TestScene::Exit()
	{
		
	}
}