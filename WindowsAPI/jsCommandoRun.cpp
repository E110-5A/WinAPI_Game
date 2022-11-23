#include "jsCommandoRun.h"
#include "jsAnimator.h"
#include "jsResources.h"

js::CommandoRun::CommandoRun()
{
	SetPos(Vector2(640.0f, 600.0f));
	Initialize();
}

js::CommandoRun::CommandoRun(Pos pos)
{
	SetPos(pos);
	Initialize();
}

js::CommandoRun::~CommandoRun()
{
}

void js::CommandoRun::Initialize()
{
	if (nullptr == mImage)
	{
		mImage = Resources::Load<Image>
			(L"Player", L"..\\Resources\\Image\\Player\\player.bmp");
	}

	mAnim = new Animator;
	AddComponent(mAnim);
	mAnim->CreateAnimation(L"WalkR", mImage, Pos(0.f, 72.f), Size(18.0f, 33.f)
		, Vector2(-10.f, 0.f), 8, 0.1f);
	mAnim->Play(L"WalkR");
}

void js::CommandoRun::Render(HDC hdc)
{
	GameObject::Render(hdc);
}

