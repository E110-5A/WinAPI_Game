#pragma once
#include "jsCollisionBlock.h"

namespace js
{
	class Player;
	class Ladder : public CollisionBlock
	{
	public:
		Ladder();
		Ladder(Pos pos);
		virtual ~Ladder();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

	protected:
		// 플레이어 위치 변경
		virtual void Process(GameObject* target) override;
	};
}

/*
	사다리로서 충돌체를 가짐 (씬에서 설정)
	object Pos 세팅
	collider Pos Size 세팅 


	플레이어 상태 변경해주기
	플레이어와 충돌하고, 플레이어가 Up, Down 화살표를 눌러야 작동함
	OnCollisionOverlap + Key_Press

	플레이어의 x 위치를 내 x 위치로 이동시킴
	pPos = player->GetPos();
	pPos.x = GetPos().x;
	player->SetPos(pPos);


*/