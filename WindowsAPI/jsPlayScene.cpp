#include "jsPlayScene.h"
#include "jsPlayer.h"
#include "jsSceneManager.h"
#include "jsInput.h"
#include "jsCollisionManager.h"
#include "jsCamera.h"
#include "jsObject.h"

#include "jsBGObj.h"
#include "jsMonster.h"
#include "jsPlatform.h"
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
		// 배경 오브젝트 추가
		BGObj* bg = new BGObj();
		bg->SetImage(L"PlayBG", L"Play_BG.bmp");
		bg->Initialize();
		AddGameObject(bg, eColliderLayer::BackGroundImage);

		/*
		tempGround* g = new tempGround();
		g->SetImage(L"PlayG", L"Play_Ground.bmp");
		g->Initialize();
		AddGameObject(g, eColliderLayer::Tile);*/

		// 오브젝트 추가
		GameObject* pPlayer = object::Instantiate<Player>(eColliderLayer::Player, Pos(440.f, 380.f));		
		//mObj[0] = object::Instantiate<Monster>(eColliderLayer::Monster, Pos(740.f, 360.f));

		// 게임매니저에서 오브젝트 풀 요청?

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

		// ESC 누를경우
		/*
		*  - 시간 진행 멈추기
		*  - 메뉴 UI 불러오기
		* 
		*/
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[40] = {};
		swprintf_s(szFloat, 40, L"Play Scene");
		int strLen = wcsnlen_s(szFloat, 40);
		TextOut(hdc, 5, 10, szFloat, strLen);
	}
	void PlayScene::Enter()
	{
		Camera::SetCameraEffect(eCameraEffect::FadeIn);
		Scene* scene = SceneManager::GetPlayScene();
		std::vector<GameObject*> pPlayer = scene->GetGameObjects(eColliderLayer::Player);
		// 일단 플레이어 오브젝트 풀을 가져옴 여기서 플레이어를 짚어서 넘겨야함


		Camera::SetTarget(pPlayer.at(0));

	}
	void PlayScene::Exit()
	{
	}
}