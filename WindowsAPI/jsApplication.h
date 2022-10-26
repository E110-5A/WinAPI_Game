#pragma once
#include "Common.h"

namespace js
{
	class Application
	{
	public:
		static Application& GetInstance()
		{
			static Application m_Instance;
			return m_Instance;
		}

		WindowData GetWindowData() { return mWindowData; }

		void Initialize(WindowData _data);
		void Tick();

	private:
		Application();
		~Application();

		void InitializeWindow(WindowData _data);

	private:		
		WindowData	mWindowData;
		HPEN		mPens[(UINT)ePenColor::End];
		HBRUSH		mBrushs[(UINT)eBrushColor::End];
	};
}



