#pragma once
#include <cmath>

template<typename T>
class Vec2_
{
public:
	Vec2_() = default;
	Vec2_(T xin, T yin)
		:
		x(xin),
		y(yin)
	{}

	template<typename S>
	Vec2_(const Vec2_<S>& src)
		:
		x((T)src.x),
		y((T)src.y)
	{}

	Vec2_ operator+(const Vec2_& rhs) const
	{
		return Vec2_(x + rhs.x, y + rhs.y);
	}

	Vec2_& operator+=(const Vec2_& rhs)
	{
		return *this = *this + rhs;
	}

	Vec2_ operator*(T rhs) const	//multiplyes just with type
	{
		return Vec2_(x * rhs, y * rhs);
	}

	Vec2_& operator*=(T rhs)
	{
		return *this = *this * rhs;
	}

	Vec2_ operator-(const Vec2_& rhs) const
	{
		return Vec2_(x - rhs.x, y - rhs.y);
	}

	Vec2_& operator-=(const Vec2_& rhs)
	{
		return *this = *this - rhs;
	}

	T GetLength() const
	{
		return (T)std::sqrt(GetLengthSq());
	}

	T GetLengthSq() const
	{
		return x * x + y * y;
	}

	Vec2_& Normalize()
	{
		return *this = GetNormalized();
	}

	Vec2_ GetNormalized() const
	{
		const T len = GetLength();
		if (len != (T)0)
		{
			return *this * ((T)1 / len);
		}
		return *this;
	}

public:
	T x;
	T y;
};

typedef Vec2_<int> Vei2;
typedef Vec2_<float> Vec2;