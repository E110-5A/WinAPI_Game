#include "jsUIManager.h"
#include "jsHUD.h"
#include "jsButton.h"
#include "jsPanel.h"

namespace js
{
	std::unordered_map<eUIType, UIBase*> UIManager::mUIs;
	std::queue<eUIType> UIManager::mRequestUIQueue;
	std::stack<UIBase*> UIManager::mUIBases;
	UIBase* UIManager::mCurrentData = nullptr;
	void UIManager::Initialize()
	{
		// 여기서 UI 메모리를 할당하면 된다

		//UIBase* newUI = new HUD(eUIType::HP);
		//mUIs.insert(std::make_pair(eUIType::HP, newUI));
		//newUI->SetScreenPos(Vector2(100.0f, 100.0f));
		//newUI->ImageLoad(L"HPBAR", L"..\\Resources\\Image\\HPBAR.bmp");


		UIBase* btn = new Button(eUIType::MP);
		mUIs.insert(std::make_pair(eUIType::MP, btn));
		btn->SetScreenPos(Vector2(100.0f, 300.0f));
		btn->ImageLoad(L"HPBAR", L"..\\Resources\\Image\\HPBAR.bmp");

	}
	void UIManager::OnLoad(eUIType type)
	{
		std::unordered_map<eUIType, UIBase*>::iterator iter = mUIs.find(type);
		if (iter == mUIs.end())
		{
			OnFail();
			return;
		}
		OnComplete(iter->second);
	}
	void UIManager::Tick()
	{
		// UI tick 호출
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();
			if (nullptr != uiBase)
			{
				uiBase->Tick();
			}
			uiBases.pop();
		}

		// UI 로드 진행
		if (mRequestUIQueue.size() > 0)
		{
			eUIType requestUI = mRequestUIQueue.front();
			mRequestUIQueue.pop();
			OnLoad(requestUI);
		}
	}


	void UIManager::Render(HDC hdc)
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();

			if (nullptr != uiBase)
				uiBase->Render(hdc);

			uiBases.pop();
		}
	}


	void UIManager::OnComplete(UIBase* addUI)
	{
		if (nullptr == addUI)
			return;
		addUI->Initialize();
		addUI->Active();
		addUI->Tick();

		if (addUI->GetisFullScreen())
		{
			std::stack<UIBase*> uiBases = mUIBases;
			while (!uiBases.empty())
			{
				UIBase* uiBase = uiBases.top();
				uiBases.pop();
				
				if (uiBase->GetisFullScreen())
					uiBase->InActive();
			}
		}
		mUIBases.push(addUI);
	}
	void UIManager::OnFail()
	{
		mCurrentData = nullptr;
	}

	void UIManager::Push(eUIType type)
	{
		mRequestUIQueue.push(type);
	}
	void UIManager::Pop(eUIType type)
	{
		if (0 >= mUIBases.size())
			return;

		std::stack<UIBase*> tempStack;

		UIBase* uiBase = nullptr;

		while (mUIBases.size() > 0)
		{
			uiBase = mUIBases.top();
			mUIBases.pop();

			if (uiBase->GetType() == type)
			{
				if (uiBase->GetisFullScreen())
				{
					std::stack<UIBase*> uiBases = mUIBases;
					while (!uiBases.empty())
					{
						UIBase* uiBase = uiBases.top();
						uiBases.pop();

						if (uiBase->GetisFullScreen())
						{
							break;
						}
					}
				}
				uiBase->UIClear();
			}
			else
			{
				tempStack.push(uiBase); 
			}
		}
		while (tempStack.size())
		{
			uiBase = tempStack.top();
			tempStack.pop();

			mUIBases.push(uiBase);
		}
	}
}