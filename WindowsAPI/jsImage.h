#pragma once
#include "jsResource.h"

namespace js
{
	class Image :
		public Resource
	{
	public:
		Image();
		~Image();

		virtual HRESULT Load(const std::wstring& _strPath) override;

		HDC GetDC() { return mHdc; }
		UINT GetWidth() { return m_Width; }
		UINT GetHeight() { return m_Height; }

	private:
		HBITMAP m_Bitmap;
		HDC		mHdc;
		UINT	m_Width;
		UINT	m_Height;
	};
}