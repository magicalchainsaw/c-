#pragma once
#include<cmath>
class vector2 {
public:
	vector2() = default;
	~vector2() = default;
	vector2(float w, float h) :
		x(w), y(h) {}
	vector2 operator+(const vector2& vsc) const
	{
		return vector2(x + vsc.x, y + vsc.y);
	}
	void operator+=(const vector2& vsc)
	{
		x = x + vsc.x;
		y = y + vsc.y;
	}
	void operator-=(const vector2& vsc)
	{
		x = x - vsc.x;
		y = y - vsc.y;
	}
	vector2 operator-(const vector2& vsc) const
	{
		return vector2(x - vsc.x, y - vsc.y);
	}
	float operator*(const vector2& vsc)const
	{
		return x * vsc.x + y * vsc.y;
	}
	vector2 operator*(float val)const
	{
		return vector2(x * val, y * val);
	}
	void operator*=(float val)
	{
		x = x * val;
		y - y * val;
	}
	float length()
	{
		return sqrt(x * x + y * y);
	}
	vector2 noramlize()
	{
		float len = length();
		if (len == 0)
		{
			return vector2(0, 0);
		}
		return vector2(x / len, y / len);
	}
	float x;
	float y;
}; 
