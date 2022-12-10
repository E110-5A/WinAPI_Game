#include "jsPlayerProjectile.h"

// 매니저
#include "jsTime.h"
#include "jsPlayerManager.h"

// 컴포넌트
#include "jsCollider.h"

// 오브젝트
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
	// 기본 설정
	SetType(eColliderLayer::Player_Projectile);
	mOwner = nullptr;

	// 스텟 설정
	mInfo.range = 700;
	mInfo.type = eProjectileType::DoubleTab;
	mInfo.unable = false;
	
	InitComponent();
}
void js::PlayerProjectile::InitComponent()
{
	// 충돌체 설정
	mCollider = new Collider();
	AddComponent(mCollider);
	mCollider->SetPos(Vector2::Zero);
	mCollider->SetSize(Vector2::One);
}
void js::PlayerProjectile::SetOwner(Player* owner)
{
	// 오너 설정
	mOwner = owner;
	owner->SetWeapon(this);
	SetInfo();
}
void js::PlayerProjectile::SetInfo()
{
	// info 설정
	//mInfo.range = mOwner->GetInfo().range;

	// 충돌체 크기 설정
	Collider* playerCollider = mOwner->GetComponent<Collider>();
	Size ownerSize = playerCollider->GetSize();
	mCollider->SetSize(ownerSize);
}


void js::PlayerProjectile::Tick()
{
	// 비활성화 상태인 경우 종료
	if (mInfo.unable == false)
		return;

	// 충돌확인
	GameObject::Tick();
	// 투사체 이동
	Process();
	// 종료 조건 확인
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
	// 몬스터 객체에 있는 Damaged 호출
	GameObject* attacker = other->GetOwner();
	if (eColliderLayer::Monster == attacker->GetType())
	{
		Monster* target = dynamic_cast<Monster*>(attacker);
		target->Hit(this);
	}
	
	// 내가 FMJ 타입이 아니라면 비활성화 하기
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
	mInfo.unable = true;			// 활성화
	SetDir(mOwner->GetDir());		// 방향 갱신
	mInfo.type = type;				// 타입 갱신
	Pos pos = mOwner->GetPos();		// 위치 갱신
	SetPos(pos);

	mStartPos = pos;				// 시작지점 기록
}