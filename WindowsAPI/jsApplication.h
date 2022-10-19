#pragma once
#include "Common.h"

namespace js
{
	class jsApplication
	{
	public:
		static jsApplication& GetInstance()
		{
			return m_Instance;
		}

		jsApplication();
		~jsApplication();

		void Initialize(WindowData _data);
		void Tick();

	private:
		static jsApplication	m_Instance;
		WindowData				m_WindowData;
	};
}



