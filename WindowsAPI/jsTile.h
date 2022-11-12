#pragma once
#include "jsGameObject.h"

namespace js
{
	class Image;
	class Tile : public GameObject
	{
	public:
		Tile(Pos pos);
		~Tile();

		void Initialize(Image* atlas, int index);
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetIndex(UINT index);
		UINT GetIndex() { return mIndex; }
	private:
		Image* mAtlas;
		UINT mIndex;
		UINT mX;
		UINT mY;
	};
}
