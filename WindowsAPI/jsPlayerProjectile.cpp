#include "jsPlayerProjectile.h"

// �Ŵ���
#include "jsTime.h"
#include "jsPlayerManager.h"

// ������Ʈ
#include "jsCollider.h"

// ������Ʈ
#include "jsPlayer.h"
#include "jsObject.h"
#include "jsMonster.h"

js::PlayerProjectile::PlayerProjectile()
{
	Initialize();
}
js::PlayerProjectile::PlayerProjectile(Pos pos)
{
	Initialize();
}
js::PlayerProjectile::~PlayerProjectile()
{
}

void js::PlayerProjectile::Initialize()
{
	// �⺻ ����
	SetType(eColliderLayer::Player_Projectile);
	mOwner = nullptr;

	// ���� ����
	mInfo.range = 700;
	mInfo.type = eProjectileType::DoubleTab;
	mInfo.unable = false;
	
	InitComponent();
}
void js::PlayerProjectile::InitComponent()
{
	// �浹ü ����
	mCollider = new Collider();
	AddComponent(mCollider);
	mCollider->SetPos(Vector2::Zero);
	mCollider->SetSize(Vector2::One);
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
	//mInfo.range = mOwner->GetInfo().range;

	// �浹ü ũ�� ����
	Collider* playerCollider = mOwner->GetComponent<Collider>();
	Size ownerSize = playerCollider->GetSize();
	mCollider->SetSize(ownerSize);
}


void js::PlayerProjectile::Tick()
{
	// ��Ȱ��ȭ ������ ��� ����
	if (mInfo.unable == false)
		return;

	// �浹Ȯ��
	GameObject::Tick();
	// ����ü �̵�
	Process();
	// ���� ���� Ȯ��
	Shutdown();
}
void js::PlayerProjectile::Process()
{
	Vector2 dir = GetDir();
	Pos destPos = GetPos();
	destPos.x += dir.x * 9300.0f * Time::GetDeltaTime();
	SetPos(destPos);
}
void js::PlayerProjectile::Shutdown()
{
	Vector2 dir = GetDir();

	Vector2 curPos = mCollider->GetPos();
	float curDistance = fabs(mStartPos.x - curPos.x);
		
	if (dir == Vector2::Right)
	{
		if (mStartPos.x + (mInfo.range * dir.x) <= curPos.x)
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
	// ���� ��ü�� �ִ� Damaged ȣ��
	GameObject* attacker = other->GetOwner();
	if (eColliderLayer::Monster == attacker->GetType())
	{
		Monster* target = dynamic_cast<Monster*>(attacker);
		target->Hit(this);
	}
	
	// ���� FMJ Ÿ���� �ƴ϶�� ��Ȱ��ȭ �ϱ�
	if (!(mInfo.type == eProjectileType::FMJ))
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


void js::PlayerProjectile::Active(eProjectileType type, int damage)
{
	mInfo.unable = true;			// Ȱ��ȭ
	SetDir(mOwner->GetDir());		// ���� ����
	mInfo.type = type;				// Ÿ�� ����
	Pos pos = mOwner->GetPos();		// ��ġ ����
	SetPos(pos);

	mStartPos = pos;				// �������� ���
}