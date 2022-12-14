#pragma once
#include <math.h>

#define PI 3.141592

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

		void Clear()
		{
			x = 0.0f;
			y = 0.0f;
		}

		Vector2 operator -()
		{			
			return Vector2(-x, -y);
		}
		Vector2 operator /(const float value)
		{
			Vector2 vec;
			vec.x = x / value;
			vec.y = y / value;
			return vec;
		}
		Vector2 operator *(const Vector2& other)
		{
			Vector2 temp;
			temp.x = x * other.x;
			temp.y = y * other.y;
			return temp;
		}
		Vector2 operator *(const float value)
		{
			Vector2 temp;
			temp.x = x * value;
			temp.y = y * value;
			return temp;
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
		void operator *=(const float value)
		{
			x = x * value;
			y = y * value;
		}
		void operator /=(const float value)
		{
			x = x / value;
			y = y / value;
		}
		void operator -=(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;
		}
		void operator +=(const Vector2& other)
		{
			
			x = x + other.x;
			y = y + other.y;
		}
		bool operator ==(const Vector2& other)
		{
			if (x != other.x)
				return false;
			if (y != other.y)
				return false;
			return true;
		}
		bool operator !=(const Vector2& other)
		{
			if (x != other.x)
				return true;
			if (y != other.y)
				return true;
			return false;
		}

		// 
		float Length()
		{
			return sqrtf(x * x + y * y);
		}

		Vector2& Normalize()
		{
			float length = Length();
			x /= length;
			y /= length;

			return *this;
		}
	};
	typedef Vector2 Pos, Size, Scale;

	namespace math
	{
		inline float DegreeToRadian(float degree)
		{
			return degree / 180 * PI;
		}
		inline float RadianToDegree(float radian)
		{
			return radian * 180 / PI;
		}
		// degree 로 벡터 회전
		inline Vector2 Rotate(const Vector2 value, float degree)
		{
			Vector2 ret = Vector2::Zero;
			float radian = DegreeToRadian(degree);

			ret.x = value.x * cosf(radian) - value.y * sinf(radian);
			ret.y = value.x * sinf(radian) + value.y * cosf(radian);

			return ret;
		}
		// 내적
		float Dot(const Vector2& v1, const Vector2& v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}
		float lerp(float begin, float end, float t)
		{
			return (1 - t) * begin + t * end;
		}
		Vector2 lerp(Vector2 begin, Vector2 end, float t)
		{
			Vector2 temp;
			temp.x = lerp(begin.x, end.x, t);
			temp.y = lerp(begin.y, end.y, t);
			return temp;
		}
	}
}