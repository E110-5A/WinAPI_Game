#include "jsPlayerProjectile.h"
#include "jsCollider.h"
#include "jsPlayer.h"
#include "jsObject.h"
#include "jsTime.h"

js::PlayerProjectile::PlayerProjectile()
{
	Init();
}

js::PlayerProjectile::PlayerProjectile(Pos pos)
{
	Init();
}

js::PlayerProjectile::~PlayerProjectile()
{
}

void js::PlayerProjectile::Init()
{
	mOwner = nullptr;

	mInfo.dir = Vector2::Right;
	mInfo.range = 700;
	mInfo.type = ePlayerAttackType::DubleTab;
	mInfo.unable = false;
	// �浹ü ����
	mCollider = new Collider();
	AddComponent(mCollider);
	mCollider->SetPos(Vector2::Zero);
	mCollider->SetSize(Vector2::One);
}

void js::PlayerProjectile::Tick()
{
	// Ȱ��ȭ �ƴϸ� ����
	if (mInfo.unable == false)
		return;

	// �浹Ȯ��
	GameObject::Tick();

	// ����ü �̵�
	Pos destPos = GetPos();
	destPos.x += mInfo.dir.x * 9300.0f * Time::GetDeltaTime();
	SetPos(destPos);

	// ���� ���� Ȯ��
	Vector2 curPos = mCollider->GetPos();
	float curDistance = fabs(mStartPos.x - curPos.x);

	if (mInfo.dir == Vector2::Right)
	{
		if (mStartPos.x + mInfo.range <= curPos.x)
			InActive();
	}
	else
	{
		if (mStartPos.x - mInfo.range >= curPos.x)
			InActive();
	}		
}

void js::PlayerProjectile::Render(HDC hdc)
{
	if (mInfo.unable == false)
		return;
	GameObject::Render(hdc);
}

void js::PlayerProjectile::OnCollisionEnter(Collider* other)
{
	// ���� ��ü�� �ִ� Hit ȣ��
	
	// ���� ��ü Rigidbody���� SetVelocity������ ���� + �˹�Ÿ� �־���




	// ���� FMJ Ÿ���� �ƴ϶�� �����ϱ�
	if (!(mInfo.type == ePlayerAttackType::FMJ))
	{
		mInfo.unable = false;
	}
}
void js::PlayerProjectile::OnCollisionStay(Collider* other)
{
}
void js::PlayerProjectile::OnCollisionExit(Collider* other)
{
}

void js::PlayerProjectile::SetOwner(Player* owner)
{
	// ���� ����
	mOwner = owner;
	owner->SetWeapon(this);
	SetInfo();
}

void js::PlayerProjectile::SetInfo()
{
	// info ����
	mInfo.range = mOwner->GetInfo().range;

	// �浹ü ũ�� ����
	Collider* playerCollider = mOwner->GetComponent<Collider>();
	Size ownerSize = playerCollider->GetSize();
	mCollider->SetSize(ownerSize);
}


void js::PlayerProjectile::Active(ePlayerAttackType type, int damage)
{
	// Ȱ��ȭ
	mInfo.unable = true;
	// ���� ����
	mInfo.dir = mOwner->GetDir();
	// Ÿ�� ����
	mInfo.type = type;


	// ��ġ ����
	Pos pos = mOwner->GetPos();
	SetPos(pos);
	mStartPos = pos;				// �������� ���
}

