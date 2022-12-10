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

#include "def.h"
#include "jsMath.h"

// 렌더링 라이브러리
#pragma comment(lib, "Msimg32.lib")

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")


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

struct PlayerStat
{
	float	maxHp;			// 110				+ 32
	float	curHp;
	int		maxExe;			// 최대 경험치
	int		curExe;			// 현재 경험치
	float	regenHp;		// 0.6				+ 0.12
	float	def;			// 0				+ 2
	float	moveSpeed;		// 1.3
	float	att;			// 12				+ 3
	float	attSpeed;		// 정확한 수치 ㅁ?ㄹ
	float	range;			// 700
	int		critical;		// 치명타율
};

struct ItemInfo
{
	eItemType	type;			// 유형
	float		count;			// 개수
	float		value;			// 효과 위력
	float		duration;		// 유효 시간
};