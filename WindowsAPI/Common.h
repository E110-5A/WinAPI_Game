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

// ������ ���̺귯��
#pragma comment(lib, "Msimg32.lib")

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

// �����ӿ�ũ
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


// �÷��̾� ����
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
	Health		playerHealth;
	Offence		playerOffence;
	Utility		playerUtility;
};
struct PlayerInfo
{
	PlayerStat	stat;
	int			level;
	float		maxExp;
	float		curExp;
	int			gold;
};
struct ItemInfo
{
	eItemType	type;			// ����
	float		count;			// ����
	float		value;			// ȿ�� ����
	float		duration;		// ��ȿ �ð�
};

// 
struct ProjectileInfo
{
	eProjectileType		type;		// ����ü ���� (��ų + ������)
	eStagger			stagger;	// ����
	float				damage;		// ���ط�
	float				power;		// ����
	float				range;		// ��Ÿ�
};

