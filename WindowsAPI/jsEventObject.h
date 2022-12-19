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

		EventObject();
		EventObject(Pos pos);
		virtual ~EventObject();

		// Ÿ��, �浹ü, ������
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
* �÷��̾�� �浹�Ͽ� �����ϴ� ������Ʈ
* ������
* ����
* �ڷ�����
* ����
* 
* ������� ����
*/
