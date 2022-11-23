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


		void Initialize(WindowData data);
		void InitializeAtlasWindow(WindowData data);
		// 충돌체 선택용 윈도우 생성하기
		void InitializeCollisionWindow(WindowData data);

		void Tick();

		void SetMenuBar(bool power);

		WindowData GetWindowData() { return mWindowData; }
		WindowData GetAtlasWindowData() { return mAtlasWindowData; }
		WindowData GetCollisionWindowData() { return mCollisionWindowData; }

		HDC GetHdc() { return mWindowData.hdc; }

		HPEN GetPen(ePenColor color) { return mPens[(UINT)color]; }
		HBRUSH GetBrush(eBrushColor color) { return mBrushs[(UINT)color]; }
		eSceneType GetPlaySceneType();
	private:
		Application();
		~Application();

		void InitializeWindow(WindowData data);

	private:		
		WindowData	mWindowData;
		WindowData	mAtlasWindowData;
		WindowData	mCollisionWindowData;

		HPEN		mPens[(UINT)ePenColor::End];
		HBRUSH		mBrushs[(UINT)eBrushColor::End];

		HMENU		mMenu;
	};
}



