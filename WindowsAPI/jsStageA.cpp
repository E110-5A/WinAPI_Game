#include "jsStageA.h"

// manager
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCollisionManager.h"
#include "jsUIManager.h"
#include "jsCamera.h"

#include "jsGameManager.h"

// scene
#include "jsMapToolScene.h"
#include "jsCollider.h"
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
	StageA::StageA()
	{
	}
	StageA::~StageA()
	{
	}
	void StageA::Initialize()
	{		
		InitBG();
	}

	void StageA::InitBG()
	{
		// 배경 오브젝트 추가
		BGObj* bg = new BGObj();
		bg->SetImage(L"PlayBG", L"Play_BG.bmp");
		bg->Initialize();
		AddGameObject(bg, eColliderLayer::BackGroundImage);

		// 맵 불러오기
		BGObj* STG1Map = new BGObj();
		STG1Map->SetImage(L"STG1Map", L"STG1.bmp");
		STG1Map->Initialize();
		STG1Map->SetCamFollow();
		AddGameObject(STG1Map, eColliderLayer::BackgroundMap);

		// 플레이어 시작위치
		Platform* startGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(384.0f, 896.0f));
		startGround->SetColliderSize(Size(GRID_SIZE * 16, GRID_SIZE * 6));
		startGround->SetColliderOffset(Vector2(GRID_SIZE * 8, GRID_SIZE * 3));
		GameManager::SetSpawnPlatform(startGround);

		Platform* leftGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(0.0f, 384.0f));
		leftGround->SetColliderSize(Size(GRID_SIZE * 6, GRID_SIZE * 14));
		leftGround->SetColliderOffset(Vector2(GRID_SIZE * 3, GRID_SIZE * 7));

		Platform* rightGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(2432.0f, 0.0f));
		rightGround->SetColliderSize(Size(GRID_SIZE * 4, GRID_SIZE * 20));
		rightGround->SetColliderOffset(Vector2(GRID_SIZE * 2, GRID_SIZE * 10));

		Platform* fstGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(1408.0f, 704.0f));
		fstGround->SetColliderSize(Size(GRID_SIZE * 16, GRID_SIZE * 9));
		fstGround->SetColliderOffset(Vector2(GRID_SIZE * 8, GRID_SIZE * (9 / 2)));

		Platform* secGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(1280.0f, 640.0f));
		secGround->SetColliderSize(Size(GRID_SIZE * 18, GRID_SIZE));
		secGround->SetColliderOffset(Vector2(GRID_SIZE * 9, GRID_SIZE / 2));


		Ladder* ladder = object::Instantiate<Ladder>(eColliderLayer::Ladder, Pos(1344.0f, 640.0f));
		ladder->SetColliderSize(Size(GRID_SIZE, GRID_SIZE * 4));
		ladder->SetColliderOffset(Vector2(GRID_SIZE / 2, GRID_SIZE * 2));

		Propellant* propellant = object::Instantiate<Propellant>(eColliderLayer::Propellant, Pos(1216, 896));
		propellant->SetPos(Pos(1216, 896 - 80));
	}

	void StageA::Tick()
	{
		Scene::Tick();
		GameManager::Playing();

		if (KEY_DOWN(eKeyCode::ESC))
		{
			SceneManager::ChangeScene(eSceneType::Title);
		}
	}
	void StageA::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[40] = {};
		swprintf_s(szFloat, 40, L"Stage A");
		int strLen = wcsnlen_s(szFloat, 40);
		TextOut(hdc, 5, 10, szFloat, strLen);
	}
	void StageA::Enter()
	{

		EnterObject();
		GameManager::SetPlayable(true);
		Camera::SetTarget(GameManager::GetPlayer());


		EnterUI();
		EnterLayer();
	}
	void StageA::Exit()
	{
		UIManager::Pop(eUIType::PlayerInfo);
		UIManager::Pop(eUIType::Difficulty);
	}

	void StageA::EnterObject()
	{
		GameManager::AddObject();		
		Player* player = GameManager::GetPlayer();
		player->SetPos(Pos(420.0f, 620.0f));

		// 씬에서 상자 연결
		for (int idx = 0; idx < CHEST_POOL; ++idx)
		{
			mChest[idx] = GameManager::GetChest(idx);
		}
		mChest[0]->SetPos(Pos(384.0f, 866.0f));
		mChest[1]->SetPos(Pos(1280.0f, 610.0f));
		mChest[2]->SetPos(Pos(1536.0f, 610.0f));
		mChest[3]->SetPos(Pos(2368.0f, 610.0f));
		// 텔레포터 연결
		mTeleporter = GameManager::GetTeleporter();
		mTeleporter->SetPos(Pos(2112.f, 640.f - 64.0f));

		GameManager::SetPlayable(true);
	}

	void StageA::EnterUI()
	{
		UIManager::Push(eUIType::PlayerInfo);
		UIManager::Push(eUIType::HpBar);
		UIManager::Push(eUIType::ExpBar);

		BarUI* hpBar = UIManager::GetUIInstant<BarUI>(eUIType::HpBar);
		hpBar->SetType(eBarType::HP);
		hpBar->SetHealth(GameManager::GetPlayerInfo()->stat->playerHealth);
		BarUI* expBar = UIManager::GetUIInstant<BarUI>(eUIType::ExpBar);
		expBar->SetType(eBarType::EXP);
		expBar->SetExp(GameManager::GetPlayerInfo());

		// 스킬 UI
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

	void StageA::EnterLayer()
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
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Teleporter, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::DamageObject, true);

		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Propellant, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Projectile, true);
	}
}