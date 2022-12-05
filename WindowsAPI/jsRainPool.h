#pragma once
#include "Common.h"

#define RAIN 21

namespace js
{
	class Scene;
	class jsRain;
	class jsRainPool
	{
	public:
		static void Initialize(Scene* _target);

	private:
		static jsRain* rain[RAIN];
	};


}