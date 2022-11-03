#pragma once
#include "jsResource.h"

namespace js
{
	class Image :
		public Resource
	{
	public:
		static Image* Create(const std::wstring& key, UINT width, UINT height);

		Image();
		~Image();

		virtual HRESULT Load(const std::wstring& strPath) override;

		HDC GetDC() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		HBITMAP mBitmap;
		HDC		mHdc;
		UINT	mWidth;
		UINT	mHeight;
	};
}