#pragma once

#include "framework.h"

#include <string>
#include <vector>
#include <list>
#include <map>

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
	HDC m_hdc;
	HPEN m_prevPen;
	HPEN m_targetPen;

public:
	Pen(HDC hdc, HPEN pen)
		: m_hdc(hdc)
		, m_prevPen(NULL)
		, m_targetPen(pen)
	{
		m_prevPen = (HPEN)SelectObject(m_hdc, pen);
	}
	~Pen()
	{
		SelectObject(m_hdc, m_prevPen);
		DeleteObject(m_targetPen);
	}
};

struct Brush
{
private:
	HDC m_hdc;
	HBRUSH m_prevBrush;
	HBRUSH m_targetBrush;

public:
	Brush(HDC hdc, HBRUSH brush)
		: m_hdc(hdc)
		, m_prevBrush(NULL)
		, m_targetBrush(brush)
	{
		m_prevBrush = (HBRUSH)SelectObject(m_hdc, brush);
	}
	
	~Brush()
	{
		SelectObject(m_hdc, m_prevBrush);
		DeleteObject(m_targetBrush);
	}
};