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
		UIManager::Push(eUIType::PLAYER_INFO);
		HUD* hud = UIManager::GetUIInstant<HUD>(eUIType::PLAYER_INFO);
		hud->SetTarget(pPlayer);
		UIManager::Push(eUIType::ITEM_SELECT);*/
	}

	void TestScene::Tick()
	{
		// ������Ʈ tick �� ȣ���Ѵ�.
		Scene::Tick();

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
		SceneManager::LoadMap<MapToolScene>(L"..\\Resources\\Tile\\pls", eSceneType::MapTool);
	}

	void TestScene::BGTest()
	{
		Ground* leftGround = object::Instantiate<Ground>(eColliderLayer::Ground, Pos(0.0f, 384.0f));
		leftGround->SetColliderSize(Size(GRID_SIZE, GRID_SIZE * 5));
		leftGround->SetColliderOffset(Pos(GRID_SIZE / 2, GRID_SIZE * 5 / 2));

		Ground* mainGround = object::Instantiate<Ground>(eColliderLayer::Ground, Pos(64.0f, 640.0f));
		mainGround->SetColliderSize(Size(GRID_SIZE * 16, GRID_SIZE));
		mainGround->SetColliderOffset(Pos(GRID_SIZE * 8, GRID_SIZE / 2));
	}

	void TestScene::ObjectTest()
	{
		// �÷��̾� ����
		Player* pPlayer = object::Instantiate<Player>(eColliderLayer::Player, Pos(440.f, 600.0f));

		for (int idx = 0; idx < WEAPON_POOL; ++idx)
		{
			mPlayerAttack[idx] = object::Instantiate<PlayerProjectile>(eColliderLayer::Player_Projectile);
			mPlayerAttack[idx]->SetOwner(pPlayer);
		}

		// ��Ÿ ������Ʈ ����
		EventObject* smallBox = object::Instantiate<SmallChest>(eColliderLayer::Chest, Pos(70.0f, 480.0f));
		EventObject* largeBox = object::Instantiate<LargeChest>(eColliderLayer::Chest, Pos(140.0f, 480.0f));
		EventObject* goldenBox = object::Instantiate<GoldenChest>(eColliderLayer::Chest, Pos(220.0f, 480.0f));
		
		// ���� ����
		Monster* imp = object::Instantiate<Imp>(eColliderLayer::Monster, Pos(700.f, 600.0f));
		Monster* imp2 = object::Instantiate<Imp>(eColliderLayer::Monster, Pos(750.f, 600.0f));
		Monster* imp3 = object::Instantiate<Imp>(eColliderLayer::Monster, Pos(800.f, 600.0f));
	}

	// �浹 �� UI ����
	void TestScene::Enter()
	{
		CollisionManager::SetLayer(eColliderLayer::Ground, eColliderLayer::Player, true);
		CollisionManager::SetLayer(eColliderLayer::Ground, eColliderLayer::Monster, true);

		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Chest, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Monster_Projectile, true);
		
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Projectile, true);
	}

	// UI ���� ������
	void TestScene::Exit()
	{
	}
}