#pragma once
#include "jsEventObject.h"

namespace js
{
	class GoldItemBox : public EventObject
	{
	public:
		GoldItemBox();
		GoldItemBox(Pos pos);
		virtual ~GoldItemBox();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

	private:
		Event		mOnTrigger;
	};
}

