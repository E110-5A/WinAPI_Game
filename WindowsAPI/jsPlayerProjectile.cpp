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
	mInfo.isActive = false;
	// 충돌체 설정
	mCollider = new Collider();
	AddComponent(mCollider);
	mCollider->SetPos(Vector2::Zero);
	mCollider->SetSize(Vector2::One);
}

void js::PlayerProjectile::Tick()
{
	// 활성화 아니면 종료
	if (mInfo.isActive == false)
		return;

	// 충돌확인
	GameObject::Tick();

	// 투사체 이동
	Pos destPos = GetPos();
	destPos.x += mInfo.dir.x * 13000.0f * Time::GetDeltaTime();
	SetPos(destPos);

	// 종료 조건 확인
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
	if (mInfo.isActive == false)
		return;
	GameObject::Render(hdc);
}

void js::PlayerProjectile::OnCollisionEnter(Collider* other)
{
	// 몬스터 객체에 있는 Hit 호출
	
	// 몬스터 객체 Rigidbody에서 SetVelocity값으로 방향 + 넉백거리 넣어줌




	// 내가 FMJ 타입이 아니라면 삭제하기
	if (!(mInfo.type == ePlayerAttackType::FMJ))
	{
		object::Destroy(this);
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
	// 오너 설정
	mOwner = owner;
	owner->SetWeapon(this);

	// info 설정
	mInfo.range = owner->GetInfo().range;

	// 충돌체 크기 설정
	Collider* playerCollider = mOwner->GetComponent<Collider>();
	Size ownerSize = playerCollider->GetSize();
	mCollider->SetSize(ownerSize);
}


void js::PlayerProjectile::Active(ePlayerAttackType type)
{
	// 활성화
	mInfo.isActive = true;
	// 방향 갱신
	mInfo.dir = mOwner->GetDir();
	// 타입 갱신
	mInfo.type = type;


	// 위치 갱신
	Pos pos = mOwner->GetPos();
	SetPos(pos);
	mStartPos = pos;			// 시작지점 기록
}

