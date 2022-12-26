#include "jsStage1.h"

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
#include "jsBGObj.h"
#include "jsMonster.h"
#include "jsPlatform.h"

namespace js
{
	Stage1::Stage1()
	{
	}
	Stage1::~Stage1()
	{
	}
	void Stage1::Initialize()
	{
		
		InitBG();

		/*
		tempGround* g = new tempGround();
		g->SetImage(L"PlayG", L"Play_Ground.bmp");
		g->Initialize();
		AddGameObject(g, eColliderLayer::Tile);*/


	}

	void Stage1::InitBG()
	{
		SceneManager::LoadMap<MapToolScene>(L"..\\Resources\\Tile\\STG1\\stage1", eSceneType::MapTool);

		// 배경 오브젝트 추가
		BGObj* bg = new BGObj();
		bg->SetImage(L"PlayBG", L"Play_BG.bmp");
		bg->Initialize();
		AddGameObject(bg, eColliderLayer::BackGroundImage);
	}

	void Stage1::Tick()
	{
		Scene::Tick();
		
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
	void Stage1::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[40] = {};
		swprintf_s(szFloat, 40, L"Play Scene");
		int strLen = wcsnlen_s(szFloat, 40);
		TextOut(hdc, 5, 10, szFloat, strLen);
	}
	void Stage1::Enter()
	{
		GameManager::SetPlayable(true);

		EnterObject();

		Camera::SetTarget(GameManager::GetPlayer());

		EnterUI();
		EnterLayer();
		UIManager::Push(eUIType::PlayerInfo);
		UIManager::Push(eUIType::HpBar);
		UIManager::Push(eUIType::ExpBar);

	}
	void Stage1::Exit()
	{
	}

	void Stage1::EnterObject()
	{
		GameManager::AddObject();
	}

	void Stage1::EnterUI()
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

	void Stage1::EnterLayer()
	{
		CollisionManager::SetLayer(eColliderLayer::Platform, eColliderLayer::Head, true);
		CollisionManager::SetLayer(eColliderLayer::Platform, eColliderLayer::Foot, true);
		CollisionManager::SetLayer(eColliderLayer::Platform, eColliderLayer::Player, true);
		CollisionManager::SetLayer(eColliderLayer::Platform, eColliderLayer::Monster, true);

		CollisionManager::SetLayer(eColliderLayer::Ladder, eColliderLayer::Head, true);
		CollisionManager::SetLayer(eColliderLayer::Ladder, eColliderLayer::Foot, true);
		CollisionManager::SetLayer(eColliderLayer::Ladder, eColliderLayer::Player, true);

		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Propellant, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Item, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::DamageObject, true);

		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Propellant, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Projectile, true);
	}
}