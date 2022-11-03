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
		HDC GetHdc() { return mWindowData.hdc; }

		void Initialize(WindowData _data);
		void Tick();

		HPEN GetPen(ePenColor color) { return mPens[(UINT)color]; }
		HBRUSH GetBrush(eBrushColor color) { return mBrushs[(UINT)color]; }

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



