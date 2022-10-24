#pragma once

#include "framework.h"

#include <string>
#include <vector>
#include <list>
#include <map>

#include "def.h"
#include "jsMath.h"

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
	Pen(HDC _hdc, HPEN _pen)
		: m_hdc(_hdc)
		, m_prevPen(NULL)
		, m_targetPen(_pen)
	{
		m_prevPen = (HPEN)SelectObject(m_hdc, _pen);
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
	Brush(HDC _hdc, HBRUSH _brush)
		: m_hdc(_hdc)
		, m_prevBrush(NULL)
		, m_targetBrush(_brush)
	{
		m_prevBrush = (HBRUSH)SelectObject(m_hdc, _brush);
	}
	
	~Brush()
	{
		SelectObject(m_hdc, m_prevBrush);
		DeleteObject(m_targetBrush);
	}
};