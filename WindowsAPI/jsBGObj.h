#pragma once
#include "jsGameObject.h"
namespace js
{
	class Image;
	class BGObj : public GameObject
	{
	public:
		BGObj();
		BGObj(Pos pos);
		~BGObj();

		// 이미지 출력
		virtual void Render(HDC hdc) override;
		// 이미지 연결
		void SetImage(const std::wstring& key, const std::wstring& fileName);

		void SetCamFollow(bool camFollow = true) { mCamFollow = camFollow; }

	private:
		Image* mImage;
		std::wstring mImageName;

		bool mCamFollow;
	};
}