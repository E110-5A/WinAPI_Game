#pragma once
#include "Common.h"
#include "jsUIBase.h"


namespace js
{
	/*
	*	�÷��̾��� ���ۿ� ������ ���� ����
	*	-��ü ȭ�� UI
	*	-�⺻ UI
	*	-HUD �̹����� ������ �ִ� UI 
	*	-��ư
	*	�������� �ٸ� UI���� �ڽı����� �����ؼ� ���� �����̴� �ϳ��� ū UI�� ����
	*/
	class UIManager
	{
	public:
		static void Initialize();
		static void OnLoad(eUIType type);
		static void Tick();
		static void Render(HDC hdc);
		static void OnComplete(UIBase* addUI);
		static void OnFail();
		static void Release();

		static void Push(eUIType type);
		static void Pop(eUIType type);

		template <typename T>
		static T* GetUIInstant(eUIType type)
		{
			return dynamic_cast<T*>(mUIs[type]);
		}

	private:
		static std::unordered_map<eUIType, UIBase*> mUIs;
		static std::queue<eUIType>					mRequestUIQueue;
		static std::stack<UIBase*>					mUIBases;
		static UIBase*								mCurrentData;
	};
}