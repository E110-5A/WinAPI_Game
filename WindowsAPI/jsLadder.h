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

		// �÷��̾� ��ġ ����
		void PullPlayer(GameObject* target);

		// Climb�� �ƴ� ���¿��� UPŰ�� ���� ���
		void BodyCollision(Collider* other);
		void FootEscapeLadder(Collider* other);
		bool IsPlayerCollision() { return mIsBodyCollision; }
	private:
		bool mIsBodyCollision;
	};
}

/*
	��ٸ��μ� �浹ü�� ���� (������ ����)
	object Pos ����
	collider Pos Size ���� 


	�÷��̾� ���� �������ֱ�
	�÷��̾�� �浹�ϰ�, �÷��̾ Up, Down ȭ��ǥ�� ������ �۵���
	OnCollisionOverlap + Key_Press

	�÷��̾��� x ��ġ�� �� x ��ġ�� �̵���Ŵ
	pPos = player->GetPos();
	pPos.x = GetPos().x;
	player->SetPos(pPos);


*/