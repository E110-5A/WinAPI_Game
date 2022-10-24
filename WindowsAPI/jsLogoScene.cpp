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
		AddGameObject(new jsPlayer);
		jsRainPool::Init(this);
	}
	void jsLogoScene::Tick()
	{
		jsScene::Tick();
	}
	void jsLogoScene::Render(HDC _dc)
	{
		jsScene::Render(_dc);
	}
}