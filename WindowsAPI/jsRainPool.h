#pragma once
#include "Common.h"

#define RAIN 10

namespace js
{
	class jsScene;
	class jsRain;
	class jsRainPool
	{
	public:
		static void Init(jsScene* _target);

	private:
		static jsRain* rain[RAIN];
	};


}