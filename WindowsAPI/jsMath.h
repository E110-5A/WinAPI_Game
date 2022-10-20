#pragma once

namespace js
{
	struct Vector2
	{
		float x;
		float y;

		Vector2(float _x, float _y)
		{
			x = _x;
			y = _y;
		}
		Vector2(const Vector2& _other) = default;
		Vector2() = default;
		~Vector2() = default;
	};
	typedef Vector2 Pos, Size, Scale;
}