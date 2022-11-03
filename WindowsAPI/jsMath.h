#pragma once

namespace js
{
	struct Vector2
	{
		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Right;
		static Vector2 Left;
		static Vector2 Up;
		static Vector2 Down;
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

		Vector2 operator /(const float value)
		{
			Vector2 vec;
			vec.x = x / value;
			vec.y = y / value;
			return vec;
		}
		Vector2 operator *(const float value)
		{
			Vector2 vec;
			vec.x = x * value;
			vec.y = y * value;
			return vec;
		}
		Vector2 operator *(const Vector2& other)
		{
			Vector2 vec;
			vec.x = x * other.x;
			vec.y = y * other.y;
			return vec;
		}
		Vector2 operator +(const Vector2& other)
		{
			Vector2 vec;
			vec.x = x + other.x;
			vec.y = y + other.y;
			return vec;
		}
		Vector2 operator -(const Vector2& other)
		{
			Vector2 vec;
			vec.x = x - other.x;
			vec.y = y - other.y;
			return vec;
		}
	};
	typedef Vector2 Pos, Size, Scale;
}