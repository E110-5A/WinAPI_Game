#pragma once
#include "jsEntity.h"

namespace js
{
	class Image;
	class UIBase : public Entity
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				// �Լ��� r-value(�ڵ念��)�̱� ������ move�� ���ؼ� �Ű������
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

		void Initialize();			//	UI�� �ε�� �� ȣ��Ǵ� �ʱ�ȭ �Լ�
		void Active();				//	UI�� Ȱ��ȭ �Ǹ� ȣ��Ǵ� �Լ�
		void InActive();			//	UI�� ��Ȱ��ȭ �Ǹ� ȣ��Ǵ� �Լ�
		void Tick();				//	UI�� ������Ʈ �� ������ ȣ��Ǵ� �Լ�
		void Render(HDC hdc);
		void UIClear();				//	UI�� ����� �� ȣ��Ǵ� �Լ�

		void ImageLoad(const std::wstring& key, const std::wstring& path);

		virtual void OnInit() {};
		virtual void OnActive() {};
		virtual void OnInActive() {};
		virtual void OnTick() {};
		virtual void OnRender(HDC hdc) {};
		virtual void OnClear() {};

		eUIType GetType() { return mType; }
		bool GetisFullScreen() { return mIsFullScreen; }
		void SetIsFullScreen(bool enable) { mIsFullScreen = enable; }
		void SetParent(UIBase* parent) { mParent = parent; }

		void SetScreenPos(Pos pos) { mScreenPos = pos; }
		Pos GetScreenPos() { return mScreenPos; }
		void SetPos(Pos pos) { mPos = pos; }
		Pos GetPos() { return mPos; }
		void SetSize(Size size) { mSize = size; }
		Size GetSize() { return mSize; }

	protected:
		UIBase* mParent;
		Image* mImage;
		Pos mScreenPos;
		Pos mPos;
		Size mSize;

	private:
		std::vector<UIBase*> mChilds;
		eUIType mType;
		bool	mIsFullScreen;
		bool	mIsEnable;

		
	};
}