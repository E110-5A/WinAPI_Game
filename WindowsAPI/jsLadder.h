#pragma once
#include "jsEventObject.h"

namespace js
{
	class Ladder : public EventObject
	{
	public:
		Ladder();
		Ladder(Pos pos);
		virtual ~Ladder();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		// ������ �浹ũ�� ����
		void SetColliderSize(Size size) { mEventCollider->SetSize(size); }
		// ������ �浹��ġ ����
		void SetColliderOffset(Pos pos) { mEventCollider->SetOffset(pos); }

		// �÷��̾� ���� �ٲٱ�
		void SetPlayerState(Player* player);


		// �÷��̾� ��ġ ����
		void SetPlayerPos(Player* player);


		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;
	private:

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