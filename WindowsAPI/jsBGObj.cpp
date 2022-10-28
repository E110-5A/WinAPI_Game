#include "jsBGObj.h"
#include "jsResources.h"
#include "jsImage.h"

namespace js
{
	BGObj::BGObj()
		: mImage(nullptr)
	{
		SetPos(Vector2::Zero);
		SetScale(Vector2::One);
	}
	BGObj::~BGObj()
	{
	}
	void BGObj::Initialize()
	{
		
	}
	void BGObj::Tick()
	{
	}
	void BGObj::Render(HDC hdc)
	{
		Pos pos = GetPos();
		Size scale = GetScale();

		Vector2 finalPos = pos;
		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;


		TransparentBlt(hdc,
			finalPos.x, finalPos.y,
			rect.x, rect.y,
			mImage->GetDC(), 0, 0,
			mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(hdc);
	}
	void BGObj::SetImage(const std::wstring& key, const std::wstring& fileName)
	{
		std::wstring path = L"..\\Resources\\Image\\etc\\";
		path += fileName;

		mImage = Resources::Load<Image>(key, path);
	}
}