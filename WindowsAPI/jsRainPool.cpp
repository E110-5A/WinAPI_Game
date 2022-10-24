#include "jsRainPool.h"
#include "jsRain.h"
#include "jsScene.h"

namespace js
{
	jsRain* jsRainPool::rain[RAIN] = {};

	void jsRainPool::Init(jsScene* _target)
	{
		for (size_t i = 0; i < RAIN; i++)
		{
			rain[i] = new jsRain;
			rain[i]->SetPos(Pos(rand() % 1921, 200));
			rain[i]->SetScale(Pos(rand() % 100, rand() % 100));
			rain[i]->SetSpeed(rand() % 800);
			_target->AddGameObject(rain[i]);
		}
	}
}