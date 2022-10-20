#pragma once

#include "jsEntity.h"

namespace js
{
	class jsGameObject;
	class jsScene :
		public jsEntity
	{
	public:
		jsScene();
		virtual ~jsScene();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC _dc);

		void AddGameObject(jsGameObject* _obj);

	private:
		std::vector<jsGameObject*> m_GameObj;
	};


}