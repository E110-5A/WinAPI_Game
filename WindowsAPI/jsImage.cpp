#include "jsImage.h"
#include "jsApplication.h"
#include "jsResources.h"

namespace js
{
	Image* Image::Create(const std::wstring& key, UINT width, UINT height)
	{
		// ���� �̸��� �̹����� �ִ��� Ȯ��
		Image* image = Resources::Find<Image>(key);
		if (nullptr != image)
		{
			MessageBox(nullptr, L"�ߺ� Ű �̹��� ����", L"�̹��� ���� ����!", MB_OK);
			return nullptr;
		}
		
		// �̹��� ����
		image = new Image();
		HDC hdc = Application::GetInstance().GetHdc();
		image->mBitmap = CreateCompatibleBitmap(hdc, width, height);
		image->mHdc = CreateCompatibleDC(hdc);

		if (NULL == image->mBitmap 
			|| NULL == image->mHdc)
			return nullptr;

		// ��Ʈ�ʰ� DC�� ����
		HBITMAP defaultBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(defaultBitmap);

		// ��Ʈ�� ����Ȯ��
		BITMAP bitmap = {};
		GetObject(image->mBitmap, sizeof(BITMAP), &bitmap);

		image->mWidth = bitmap.bmWidth;
		image->mHeight = bitmap.bmHeight;
		image->SetKey(key);
		Resources::Insert<Image>(key, image);

		return image;
	}
	Image::Image()
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{
	}

	Image::~Image()
	{
		HWND hWnd = Application::GetInstance().GetWindowData().hWnd;
		ReleaseDC(hWnd, mHdc);
	}

	HRESULT Image::Load(const std::wstring& path)
	{
		mBitmap = 
			(HBITMAP)LoadImageW(nullptr, path.c_str(), 
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		// �̹����� ���������� �ε� ����� Ȯ��
		if (nullptr == mBitmap)
		{
			return E_FAIL;
		}

		// ��Ʈ�� ���� Ȯ���ϱ�
		BITMAP bitInfo = {};
		GetObject(mBitmap, sizeof(BITMAP), &bitInfo);


		// �ε��� ��Ʈ�� ������ �� DC �����
		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDC = Application::GetInstance().GetWindowData().hdc;
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP prevBit = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(prevBit);

		return S_OK;
	}
	Pixel Image::GetPixel(int x, int y)
	{
		y = mHeight - (y + 1);

		Pixel* pixel = (Pixel*)mBitmap;
		pixel += (mWidth * y + x);

		
		return *pixel;
	}
	void Image::SetPixel(int x, int y, Pixel pixel)
	{
		// ���ϴ��� 0,0 // Ȱ���Ϸ��� y�� �ݴ�� �����ؾ���
		y = mHeight - (y + 1);

		Pixel* bitmapPixel = (Pixel*)mBitmap;
		bitmapPixel += (mWidth * y + x);
		*bitmapPixel = pixel;
	}
}