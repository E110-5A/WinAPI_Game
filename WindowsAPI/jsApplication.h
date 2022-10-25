#pragma once
#include "Common.h"

namespace js
{
	class jsApplication
	{
	public:
		static jsApplication& GetInstance()
		{
			static jsApplication m_Instance;
			return m_Instance;
		}

		WindowData GetWindowData() { return m_WindowData; }

		void Initialize(WindowData _data);
		void Tick();

	private:
		jsApplication();
		~jsApplication();

		void InitializeWindow(WindowData _data);
	private:
		
		WindowData				m_WindowData;
	};
}



