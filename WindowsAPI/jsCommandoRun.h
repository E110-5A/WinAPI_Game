#pragma once
#include "jsGameObject.h"

namespace js
{
	class Image;
	class Animator;
	class CommandoRun : public GameObject
	{
	public:
		CommandoRun();
		CommandoRun(Pos pos);
		~CommandoRun();

		virtual void Initialize() override;
		virtual void Render(HDC hdc) override;

	private:
		Animator*	mAnim;
		Image*		mImage;
	};
}