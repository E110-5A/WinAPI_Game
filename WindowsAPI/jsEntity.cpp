#include "jsEntity.h"

namespace js
{
	Entity::Entity()
		: mName(L"")
		, mID((UINT32)this)
	{}
	Entity::~Entity()
	{}
}