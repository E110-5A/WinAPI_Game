#pragma once
#include "jsGameObject.h"

namespace js
{
	class Image;
	class Collider;
	class Player;
	class EventObject : public GameObject
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

		EventObject();
		EventObject(Pos pos);
		virtual ~EventObject();

		// 타입, 충돌체, 스케일
		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
				
		virtual void SetComponent() override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;
		
		void SetImage(const std::wstring& key, const std::wstring& path);
		void SetImage(const std::wstring& key);

	protected:
		Image*		mImage;
		Collider*	mEventCollider;

	private:
	};
}

/*
* 플레이어와 충돌하여 반응하는 오브젝트
* 아이템
* 상자
* 텔레포터
* 성소
* 
* 점프대는 제외
*/
