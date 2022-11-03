#include "jsImage.h"
#include "jsApplication.h"
#include "jsResources.h"

namespace js
{
	Image* Image::Create(const std::wstring& key, UINT width, UINT height)
	{
		// 같은 이름의 이미지가 있는지 확인
		Image* image = Resources::Find<Image>(key);
		if (nullptr != image)
		{
			MessageBox(nullptr, L"중복 키 이미지 생성", L"이미지 생성 실패!", MB_OK);
			return nullptr;
		}
		
		// 이미지 생성
		image = new Image();
		HDC hdc = Application::GetInstance().GetHdc();
		image->mBitmap = CreateCompatibleBitmap(hdc, width, height);
		image->mHdc = CreateCompatibleDC(hdc);

		if (NULL == image->mBitmap ||
			NULL == image->mHdc)
			return nullptr;

		// 비트맵과 DC를 연결
		HBITMAP defaultBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(defaultBitmap);

		// 비트맵 정보확인
		BITMAP bitmap = {};
		GetObject(image->mHdc, sizeof(BITMAP), &bitmap);

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

		// 이미지가 성공적으로 로드 됬는지 확인
		if (nullptr == mBitmap)
		{
			return E_FAIL;
		}

		// 비트맵 정보 확인하기
		BITMAP bitInfo = {};
		GetObject(mBitmap, sizeof(BITMAP), &bitInfo);


		// 로드한 비트맵 정보로 새 DC 만들기
		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDC = Application::GetInstance().GetWindowData().hdc;
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP prevBit = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(prevBit);

		return S_OK;
	}
}