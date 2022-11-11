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
		WindowData GetAtlasWindowData() { return mAtlasWindowData; }
		HDC GetHdc() { return mWindowData.hdc; }


		void Initialize(WindowData data);
		void InitializeAtlasWindow(WindowData data);

		void Tick();

		void SetMenuBar(bool power);

		HPEN GetPen(ePenColor color) { return mPens[(UINT)color]; }
		HBRUSH GetBrush(eBrushColor color) { return mBrushs[(UINT)color]; }

	private:
		Application();
		~Application();

		void InitializeWindow(WindowData data);

	private:		
		WindowData	mWindowData;
		WindowData	mAtlasWindowData;
		HPEN		mPens[(UINT)ePenColor::End];
		HBRUSH		mBrushs[(UINT)eBrushColor::End];

		HMENU		mMenu;
	};
}



