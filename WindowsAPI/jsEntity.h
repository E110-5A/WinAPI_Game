#pragma once
#include "Common.h"

namespace js
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring name) { mName = name; }
		std::wstring GetName() { return mName; }
		UINT32 GetID() { return mID; }


	private:
		std::wstring	mName;
		UINT			mID;
	};

}
