#include "jsTestScene.h"
#include "jsPlayer.h"
#include "jsMonster.h"
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsBGObj.h"
#include "jsCollisionManager.h"
#include "jsObject.h"
#include "jsApplication.h"
#include "jsToolScene.h"

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
		GameObject* pPlayer = object::Instantiate<Player>(eColliderLayer::Player, Pos(440.f, 380.f));

		//mons[0] = object::Instantiate<Monster>(eColliderLayer::Monster);

		js::Scene* scene = js::SceneManager::GetScene(eSceneType::Tool);
		js::ToolScene* toolScene = dynamic_cast<js::ToolScene*>(scene);
		toolScene->LoadTilePalette(L"..\\Resources\\Tile\\ttss");

	}

	void TestScene::Tick()
	{
		// 오브젝트 tick 을 호출한다.
		Scene::Tick();

		//js::object::Destroy(mons[0], 3.0f);
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
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Projectile, true);
	}

	void TestScene::Exit()
	{
	}
}