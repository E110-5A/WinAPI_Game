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

		//	Title Scene

		Button* selectBtn = new Button(eUIType::SelectBtn);
		mUIs.insert(std::make_pair(eUIType::SelectBtn, selectBtn));
		selectBtn->ImageLoad(L"SelectBtn", L"..\\Resources\\Image\\Button\\Title_Play.bmp");
		selectBtn->SetPos(Vector2(470.0f, 300.0f));
		selectBtn->SetFunc(eBtnType::GoToSelectScene);

		Button* optionBtn = new Button(eUIType::OptionBtn);
		mUIs.insert(std::make_pair(eUIType::OptionBtn, optionBtn));
		optionBtn->ImageLoad(L"OptionBtn", L"..\\Resources\\Image\\Button\\Title_Options.bmp");
		optionBtn->SetPos(Vector2(470.0f, 370.0f));
		optionBtn->SetFunc(eBtnType::GoToOption);

		Button* quitBtn = new Button(eUIType::QuitBtn);
		mUIs.insert(std::make_pair(eUIType::QuitBtn, quitBtn));
		quitBtn->ImageLoad(L"QuitBtn", L"..\\Resources\\Image\\Button\\Title_Quit.bmp");
		quitBtn->SetPos(Vector2(470.0f, 440.0f));
		quitBtn->SetFunc(eBtnType::GoToTitleScene);






		// Select Scene

		Button* playBtn = new Button(eUIType::PlayBtn);
		mUIs.insert(std::make_pair(eUIType::PlayBtn, playBtn));
		playBtn->ImageLoad(L"PlayBtn", L"..\\Resources\\Image\\Button\\Select_Play.bmp");
		playBtn->SetPos(Vector2(560.0f, 620.0f));
		playBtn->SetFunc(eBtnType::GoToPlayScene);



		//// UI 테스트
		//Button* btn = new Button(eUIType::TEST);
		//mUIs.insert(std::make_pair(eUIType::TEST, btn));
		//btn->SetPos(Vector2(0.0f, 0.0f));
		//btn->ImageLoad(L"HPBAR", L"..\\Resources\\Image\\UI\\HPBAR.bmp");

		//HUD* hud = new HUD(eUIType::PLAYER_INFO);
		//mUIs.insert(std::make_pair(eUIType::PLAYER_INFO, hud));
		//hud->SetPos(Vector2(0.0f, 0.0f));
		//hud->ImageLoad(L"PlayerInfo", L"..\\Resources\\Image\\UI\\PlayerHud.bmp");

		//Panel* panel = new Panel(eUIType::ITEM_SELECT);
		//mUIs.insert(std::make_pair(eUIType::ITEM_SELECT, panel));
		//panel->SetPos(Vector2(500.0f, 500.0f));
		//panel->ImageLoad(L"BackPack", L"..\\Resources\\Image\\BackPack.bmp");
		//panel->AddChild(btn);
		//panel->AddChild(hud);

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
		std::stack<UIBase*> tempStack = mUIBases;

		// ui 스택 뒤집기
		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();
			tempStack.push(uiBase);
			uiBases.pop();
		}

		// ui 메시지 순차적으로 재생
		while (!tempStack.empty())
		{
			UIBase* uiBase = tempStack.top();

			if (nullptr != uiBase)
				uiBase->Render(hdc);

			tempStack.pop();
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

	void UIManager::Release()
	{
		for (auto ui : mUIs)
		{
			delete ui.second;
			ui.second = nullptr;
		}
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
			uiBase->InActive();

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