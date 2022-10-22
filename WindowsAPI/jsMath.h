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

		Vector2 operator /(const float _value)
		{
			Vector2 vec;
			vec.x = x / _value;
			vec.y = y / _value;
			return vec;
		}
		Vector2 operator +(const Vector2& _other)
		{
			Vector2 vec;
			vec.x = x + _other.x;
			vec.y = y + _other.y;
			return vec;
		}
		Vector2 operator -(const Vector2& _other)
		{
			Vector2 vec;
			vec.x = x - _other.x;
			vec.y = y - _other.y;
			return vec;
		}
	};
	typedef Vector2 Pos, Size, Scale;
}