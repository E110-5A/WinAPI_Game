#pragma once
#include "jsEntity.h"

namespace js
{
	class Image;
	class GameObject;
	class UIBase : public Entity
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				// 함수는 r-value(코드영역)이기 때문에 move를 통해서 옮겨줘야함
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		UIBase(eUIType type);
		virtual ~UIBase();

		void Initialize();			//	UI가 로드될 때 호출되는 초기화 함수
		void Active();				//	UI가 활성화 되면 호출되는 함수
		void InActive();			//	UI가 비활성화 되면 호출되는 함수
		void Tick();				//	UI가 업데이트 될 때마다 호출되는 함수
		void Render(HDC hdc);
		void UIClear();				//	UI가 사라질 때 호출되는 함수

		void ImageLoad(const std::wstring& key, const std::wstring& path);
		void ImageLoad(const std::wstring& key);
		void AddChild(UIBase* uiBase);



		eUIType GetType() { return mType; }
		bool GetisFullScreen() { return mIsFullScreen; }
		void SetIsFullScreen(bool enable) { mIsFullScreen = enable; }
		void SetParent(UIBase* parent) { mParent = parent; }

		void SetPos(Pos pos) { mPos = pos; }
		Pos GetPos() { return mPos; }
		void SetSize(Size size) { mSize = size; }
		Size GetSize() { return mSize; }



	protected:
		virtual void OnInit() {};
		virtual void OnActive() {};
		virtual void OnInActive() {};
		virtual void OnTick() {};
		virtual void OnRender(HDC hdc) {};
		virtual void OnClear() {};
				
		UIBase* mParent;
		Image*	mImage;
		Pos		mPos;
		Size	mSize;
		Pos		mScreenPos;
		
	private:
		std::vector<UIBase*> mChilds;
		eUIType mType;
		bool	mIsFullScreen;
		bool	mIsEnable;

		
	};
}