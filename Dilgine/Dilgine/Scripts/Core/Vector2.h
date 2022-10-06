#ifndef VECTOR2_H
#define VECTOR2_H
#include <math.h>

struct Vector2
{
	int x, y;

	Vector2() { x = 0; y = 0; }
	Vector2(int val) { x = val; y = val; }
	Vector2(int valX, int valY) { x = valX; y = valY; }

	float Magnitude() { return sqrt((x * x) + (y * y)); }
	Vector2 Normalized() {
		float mag = Magnitude();
		if (mag == 0)
			return Vector2(0);
		return Vector2(x / mag, y / mag);
	}

	Vector2 operator+(const Vector2& rhs) { return Vector2(x + rhs.x, y + rhs.y); }
	Vector2 operator-(const Vector2& rhs) { return Vector2(x - rhs.x, y - rhs.y); }
	Vector2 operator*(const int rhs) { return Vector2(x * rhs, y * rhs); }
	void operator+=(const Vector2& rhs) { x += rhs.x; y += rhs.y; }
	void operator-=(const Vector2& rhs) { x -= rhs.x; y -= rhs.y; }
	void operator*=(const int rhs) { x *= rhs; y *= rhs; }
};

#endif
#pragma once
