#include "jsPlayScene.h"
#include "jsPlayer.h"
#include "jsSceneManager.h"
#include "jsInput.h"
#include "jsCollisionManager.h"
#include "jsCamera.h"
#include "jsObject.h"

#include "jsBGObj.h"
#include "jsMonster.h"
#include "jsGround.h"
namespace js
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		BGObj* bg = new BGObj();
		bg->SetImage(L"PlayBG", L"Play_BG.bmp");
		bg->Initialize();
		AddGameObject(bg, eColliderLayer::BackGround);

		Ground* g = new Ground();
		g->SetImage(L"PlayG", L"Play_Ground.bmp");
		g->Initialize();
		AddGameObject(g, eColliderLayer::Tile);

		GameObject* pPlayer = object::Instantiate<Player>(eColliderLayer::Player, Pos(440.f, 380.f));		
		Camera::SetTarget(pPlayer);

		//mObj[0] = object::Instantiate<Monster>(eColliderLayer::Monster, Pos(740.f, 360.f));


		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Monster, true);
		CollisionManager::SetLayer(eColliderLayer::Player_Projectile, eColliderLayer::Monster, true);

	}
	void PlayScene::Tick()
	{
		Scene::Tick();
		if (KEY_DOWN(eKeyCode::K))
		{
			object::Destroy(mObj[1],1.f);
		}
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Title);
		}
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[40] = {};
		swprintf_s(szFloat, 40, L"Play Scene");
		int strLen = wcsnlen_s(szFloat, 40);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}
	void PlayScene::Enter()
	{
		Camera::SetCameraEffect(eCameraEffect::FadeIn);
	}
	void PlayScene::Exit()
	{
	}
}