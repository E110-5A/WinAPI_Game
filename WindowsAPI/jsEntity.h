#pragma once
#include "Common.h"

namespace js
{
	class jsEntity
	{
	public:
		jsEntity();
		virtual ~jsEntity();

		void SetName(const std::wstring _strname) { m_strName = _strname; }
		std::wstring GetName() { return m_strName; }

	private:
		std::wstring	m_strName;
		UINT			m_iID;
	};

}
