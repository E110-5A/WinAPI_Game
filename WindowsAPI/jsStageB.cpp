#include "jsStageB.h"

// manager
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCollisionManager.h"
#include "jsUIManager.h"
#include "jsCamera.h"

#include "jsGameManager.h"

// scene
#include "jsMapToolScene.h"

// ui
#include "jsHUD.h"
#include "jsButton.h"
#include "jsBarUI.h"
#include "jsIcon.h"
#include "jsDifficultyHUD.h"

// object
#include "jsObject.h"
#include "jsPlayer.h"
#include "jsMonster.h"
#include "jsChest.h"

#include "jsBGObj.h"
#include "jsPlatform.h"
#include "jsLadder.h"
#include "jsPropellant.h"
#include "jsTeleporter.h"

namespace js
{
	StageB::StageB()
	{
	}
	StageB::~StageB()
	{
	}
	void StageB::Initialize()
	{

		InitBG();

	}

	void StageB::InitBG()
	{
		// 배경 오브젝트 추가
		BGObj* bg = new BGObj();
		bg->SetImage(L"PlayBG2", L"Play_BG2.bmp");
		bg->Initialize();
		AddGameObject(bg, eColliderLayer::BackGroundImage);

		// 맵 불러오기
		BGObj* STG2Map = new BGObj();
		STG2Map->SetImage(L"STG2Map", L"STG2.bmp");
		STG2Map->Initialize();
		STG2Map->SetCamFollow();
		AddGameObject(STG2Map, eColliderLayer::BackgroundMap);

		 

		// 플레이어 시작위치
		Platform* startGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(384.0f, 896.0f));
		startGround->SetColliderSize(Size(GRID_SIZE * 25, GRID_SIZE * 6));
		startGround->SetColliderOffset(Vector2(GRID_SIZE * 25 / 2, GRID_SIZE * 3));
		GameManager::SetSpawnPlatform(startGround);

		Platform* leftGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(0.0f, 384.0f));
		leftGround->SetColliderSize(Size(GRID_SIZE * 6, GRID_SIZE * 14));
		leftGround->SetColliderOffset(Vector2(GRID_SIZE * 3, GRID_SIZE * 7));

		Platform* Ground2 = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(640, 640));
		Ground2->SetColliderSize(Size(GRID_SIZE * 4, GRID_SIZE * 2));
		Ground2->SetColliderOffset(Vector2(GRID_SIZE * 2, GRID_SIZE));

		Platform* Ground3 = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(1984, 640));
		Ground3->SetColliderSize(Size(GRID_SIZE * 7, GRID_SIZE * 4));
		Ground3->SetColliderOffset(Vector2(GRID_SIZE * 7 / 2, GRID_SIZE * 2));

		Platform* Ground4 = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(1536, 512));
		Ground4->SetColliderSize(Size(GRID_SIZE * 15, GRID_SIZE * 2));
		Ground4->SetColliderOffset(Vector2(GRID_SIZE * 15 / 2, GRID_SIZE));

		Platform* rightGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(2432.0f, 0.0f));
		rightGround->SetColliderSize(Size(GRID_SIZE * 4, GRID_SIZE * 20));
		rightGround->SetColliderOffset(Vector2(GRID_SIZE * 2, GRID_SIZE * 10));

		Platform* Platform1 = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(448, 384));
		Platform1->SetColliderSize(Size(GRID_SIZE * 2, GRID_SIZE * 1));
		Platform1->SetColliderOffset(Vector2(GRID_SIZE, GRID_SIZE / 2));

		Platform* Platform2 = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(704, 384));
		Platform2->SetColliderSize(Size(GRID_SIZE * 7, GRID_SIZE * 1));
		Platform2->SetColliderOffset(Vector2(GRID_SIZE * 7 / 2, GRID_SIZE / 2));

		Platform* Platform3 = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(1024, 128));
		Platform3->SetColliderSize(Size(GRID_SIZE * 4, GRID_SIZE));
		Platform3->SetColliderOffset(Vector2(GRID_SIZE * 2, GRID_SIZE / 2));

		Ladder* ladder1 = object::Instantiate<Ladder>(eColliderLayer::Ladder, Pos(768, 384));
		ladder1->SetColliderSize(Size(GRID_SIZE, GRID_SIZE * 4));
		ladder1->SetColliderOffset(Vector2(GRID_SIZE / 2, GRID_SIZE * 2));

		Ladder* ladder2 = object::Instantiate<Ladder>(eColliderLayer::Ladder, Pos(1088, 128));
		ladder2->SetColliderSize(Size(GRID_SIZE, GRID_SIZE * 4));
		ladder2->SetColliderOffset(Vector2(GRID_SIZE / 2, GRID_SIZE * 2));

		Ladder* ladder3 = object::Instantiate<Ladder>(eColliderLayer::Ladder, Pos(704, 640));
		ladder3->SetColliderSize(Size(GRID_SIZE, GRID_SIZE * 4));
		ladder3->SetColliderOffset(Vector2(GRID_SIZE / 2, GRID_SIZE * 2));

		Propellant* propellant = object::Instantiate<Propellant>(eColliderLayer::Propellant, Pos(1344, 896));
		propellant->SetPos(Pos(1344, 896 - 80));
	}

	void StageB::Tick()
	{
		Scene::Tick();
		GameManager::Playing();

		if (KEY_DOWN(eKeyCode::ESC))
		{
			SceneManager::ChangeScene(eSceneType::Title);
		}

		// ESC 누를경우
		/*
		*  - 시간 진행 멈추기
		*  - 메뉴 UI 불러오기
		*/
	}
	void StageB::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[40] = {};
		swprintf_s(szFloat, 40, L"Play Scene");
		int strLen = wcsnlen_s(szFloat, 40);
		TextOut(hdc, 5, 10, szFloat, strLen);
	}
	void StageB::Enter()
	{
		EnterObject();
		GameManager::SetPlayable(true);
		Camera::SetTarget(GameManager::GetPlayer());

		EnterUI();
		EnterLayer();
		UIManager::Push(eUIType::PlayerInfo);
		UIManager::Push(eUIType::HpBar);
		UIManager::Push(eUIType::ExpBar);

	}
	void StageB::Exit()
	{
		UIManager::Pop(eUIType::PlayerInfo);
		UIManager::Pop(eUIType::Difficulty);
	}

	void StageB::EnterObject()
	{
		GameManager::AddObject();
		Player* player = GameManager::GetPlayer();
		player->SetPos(Pos(640.0f, 620.0f));
		Camera::SetTarget(GameManager::GetPlayer());

		// 씬에서 상자 연결
		for (int idx = 0; idx < CHEST_POOL; ++idx)
		{
			mChest[idx] = GameManager::GetChest(idx);
		}
		mChest[0]->SetPos(Pos(384, 896 - 30));
		mChest[1]->SetPos(Pos(512, 384 - 30));
		mChest[2]->SetPos(Pos(1216, 128 - 30));
		mChest[3]->SetPos(Pos(2368, 512 - 30));

		// 텔레포터 연결
		mTeleporter = GameManager::GetTeleporter();
		mTeleporter->SetPos(Pos(1984, 512 - 64.0f));

		EnterUI();
		EnterLayer();
	}

	void StageB::EnterUI()
	{
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

	void StageB::EnterLayer()
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
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Projectile, true);
	}
}