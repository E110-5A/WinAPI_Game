#pragma once

#include "framework.h"

#include <filesystem>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <stack>
#include <queue>
#include <assert.h>
#include <time.h>

#include "def.h"
#include "jsMath.h"

// 렌더링 라이브러리
#pragma comment(lib, "Msimg32.lib")

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

// 프레임워크
struct Pixel
{
	BYTE R;
	BYTE G;
	BYTE B;
	BYTE A;
	Pixel(BYTE r, BYTE g, BYTE b, BYTE a)
		: R(r), G(g), B(b), A(a)
	{}
};
struct WindowData
{
	HWND	hWnd;
	HDC		hdc;
	HBITMAP	backTexture;
	HDC		backBuffer;
	UINT	height;
	UINT	width;

	void clear()
	{
		hWnd = nullptr;
		hdc = nullptr;
		height = 0;
		width = 0;
	}
};
struct Pen
{
private:
	HDC mHdc;
	HPEN mPrevPen;
	HPEN mTargetPen;

public:
	Pen(HDC hdc)
		: mHdc(hdc)
		, mPrevPen(NULL)
		, mTargetPen(NULL)
	{

	}
	Pen(HDC hdc, HPEN pen)
		: mHdc(hdc)
		, mPrevPen(NULL)
		, mTargetPen(pen)
	{
		mPrevPen = (HPEN)SelectObject(mHdc, pen);
	}
	~Pen()
	{
		SelectObject(mHdc, mPrevPen);
		DeleteObject(mTargetPen);
	}
	void SetPen(HPEN pen)
	{
		mPrevPen = (HPEN)SelectObject(mHdc, pen);
	}
};
struct Brush
{
private:
	HDC mHdc;
	HBRUSH mPrevBrush;
	HBRUSH mTargetBrush;

public:
	Brush(HDC hdc, HBRUSH brush)
		: mHdc(hdc)
		, mPrevBrush(NULL)
		, mTargetBrush(brush)
	{
		mPrevBrush = (HBRUSH)SelectObject(mHdc, brush);
	}
	
	~Brush()
	{
		SelectObject(mHdc, mPrevBrush);
		DeleteObject(mTargetBrush);
	}
};


// 플레이어 정보
struct Health
{
	float maxHP;
	float curHP;
	float healthRegen;
	float defance;
};
struct Offence
{
	float damage;
	float attackSpeed;
	float criticalChance;
	float range;
};
struct Utility
{
	int		maxJumpCount;
	int		curJumpCount;
	float	jumpPower;
	float	moveSpeed;
};
struct PlayerStat
{
	PlayerStat()
		: playerHealth(nullptr)
		, playerOffence(nullptr)
		, playerUtility(nullptr)
	{
		playerHealth = new Health();
		playerOffence = new Offence();
		playerUtility = new Utility();
	}
	~PlayerStat()
	{
		delete playerHealth;
		delete playerOffence;
		delete playerUtility;
	}

	Health*		playerHealth;
	Offence*	playerOffence;
	Utility*	playerUtility;
};
struct PlayerInfo
{
	PlayerInfo()
		: stat(nullptr)
		, level(0)
		, maxExp(0)
		, curExp(0)
		, gold(0)
	{
		stat = new PlayerStat();
	}
	~PlayerInfo()
	{
		delete stat;
	}

	PlayerStat*	stat;
	int			level;
	float		maxExp;
	float		curExp;
	int			gold;
};
struct ItemInfo
{
	eItemType	type;			// 유형
	float		count;			// 개수
	float		value;			// 효과 위력
	float		duration;		// 유효 시간
};

// 
struct ProjectileInfo
{
	eProjectileType		type;		// 투사체 종류 (스킬 + 아이템)
	eStagger			stagger;	// 관통
	float				damage;		// 피해량
	float				power;		// 위력
	float				range;		// 사거리
};

struct SkillInfo
{
	SkillInfo()
		: damage(0) ,stagger(eStagger::Light), power(0), castDelay(0), castDelayTime(0), coolDown(0), coolDownTime(0), maxCount(0), curCount(0)
		, active(true), run(false), finish(true)
	{
	}
	~SkillInfo() = default;

	float		damage;				// 피해량 비율
	eStagger	stagger;			// 관통 단계
	float		power;				// 위력 (피해와 연관없음)

	float		castDelay;			// 스킬 지연시간
	float		castDelayTime;
	float		coolDown;			// 스킬 재사용 대기시간
	float		coolDownTime;

	int			maxCount;			// 반복 횟수
	int			curCount;

	bool		active;				// 사용불가 상태		: 쿨다운 대기
	bool		run;				// 진행중 상태		: 스킬 내부로직 조건용
	bool		finish;				// 끝난 상태			: 상태 종료 조건
};