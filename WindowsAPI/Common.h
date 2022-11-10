#pragma once

#include "framework.h"

#include <filesystem>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>

#include "def.h"
#include "jsMath.h"

#pragma comment(lib, "Msimg32.lib")

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