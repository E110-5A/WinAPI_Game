#pragma once
#include "jsResource.h"

namespace js
{
	class jsImage :
		public jsResource
	{
	public:
		jsImage();
		~jsImage();

		virtual HRESULT Load(const std::wstring& _strPath) override;

		HDC GetDC() { return m_hdc; }
		UINT GetWidth() { return m_Width; }
		UINT GetHeight() { return m_Height; }

	private:
		HBITMAP m_Bitmap;
		HDC		m_hdc;
		UINT	m_Width;
		UINT	m_Height;
	};
}