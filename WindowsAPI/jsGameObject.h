#pragma once
#include "jsEntity.h"

namespace js
{

	class jsGameObject :
		public jsEntity
	{
	public:
		jsGameObject();
		virtual ~jsGameObject();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC _dc);

		void SetPos(Pos _Pos) { m_Pos = _Pos; }
		Pos GetPos() { return m_Pos; }
		void SetScale(Size _Scale) { m_Scale = _Scale; }
		Size GetScale() { return m_Scale; }

	private:
		Pos		m_Pos;
		Size	m_Scale;
	};
}

