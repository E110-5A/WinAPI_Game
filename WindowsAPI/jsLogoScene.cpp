#include "jsLogoScene.h"
#include "jsPlayer.h"
#include "jsRainPool.h"

namespace js
{
	jsLogoScene::jsLogoScene()
	{
	}
	jsLogoScene::~jsLogoScene()
	{
	}
	void jsLogoScene::Initialize()
	{
		AddGameObject(new Player);
		//jsRainPool::Init(this);
	}
	void jsLogoScene::Tick()
	{
		Scene::Tick();
	}
	void jsLogoScene::Render(HDC _dc)
	{
		Scene::Render(_dc);
	}
}