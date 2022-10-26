#include "jsImage.h"
#include "jsApplication.h"

namespace js
{
	Image::Image()
		: m_Bitmap(NULL)
		, m_hdc(NULL)
		, m_Width(0)
		, m_Height(0)
	{
	}

	Image::~Image()
	{
		HWND hWnd = Application::GetInstance().GetWindowData().hWnd;
		ReleaseDC(hWnd, m_hdc);
	}

	HRESULT Image::Load(const std::wstring& _strPath)
	{
		m_Bitmap = 
			(HBITMAP)LoadImageW(nullptr, _strPath.c_str(), 
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		// �̹����� ���������� �ε� ����� Ȯ��
		if (nullptr == m_Bitmap)
		{
			return E_FAIL;
		}

		// ��Ʈ�� ���� Ȯ���ϱ�
		BITMAP bitInfo = {};
		GetObject(m_Bitmap, sizeof(BITMAP), &bitInfo);


		// �ε��� ��Ʈ�� ������ �� DC �����
		m_Width = bitInfo.bmWidth;
		m_Height = bitInfo.bmHeight;

		HDC mainDC = Application::GetInstance().GetWindowData().hdc;
		m_hdc = CreateCompatibleDC(mainDC);

		HBITMAP prevBit = (HBITMAP)SelectObject(m_hdc, m_Bitmap);
		DeleteObject(prevBit);

		return S_OK;
	}
}