#pragma once

#include <ostream>

namespace AsciiEngine::Math
{
	struct Vector2 {
		float x, y;

		Vector2(float x, float y) : x(x), y(y) {}
		Vector2() { x = 0; y = 0; }

		static const Vector2 right;
		static const Vector2 left;
		static const Vector2 down;
		static const Vector2 up;

		float magnitude() const;
		float sqrMagnitude() const;
		Vector2 normalized() const;
		Vector2 rounded() const;
		Vector2 floored() const;

		Vector2 operator+(const Vector2& other) const {
			return Vector2(x + other.x, y + other.y);
		}

		Vector2 operator+(const float& f) const {
			return Vector2(x + f, y + f);
		}

		void operator+=(const Vector2& other) {
			x += other.x;
			y += other.y;
		}

		void operator+=(const float& f) {
			x += f;
			y += f;
		}

		Vector2 operator-(const Vector2& other) const {
			return Vector2(x - other.x, y - other.y);
		}

		Vector2 operator-(const float& f) const {
			return Vector2(x - f, y - f);
		}

		void operator-=(const Vector2& other) {
			x -= other.x;
			y -= other.y;
		}

		void operator-=(const float& f) {
			x -= f;
			y -= f;
		}

		Vector2 operator*(const Vector2& other) const {
			return Vector2(x * other.x, y * other.y);
		}

		Vector2 operator*(const float& f) const {
			return Vector2(x * f, y * f);
		}

		void operator*=(const Vector2& other) {
			x *= other.x;
			y *= other.y;
		}

		void operator*=(const float& f) {
			x *= f;
			y *= f;
		}

		Vector2 operator/(const Vector2& other) const {
			return Vector2(x / other.x, y / other.y);
		}

		Vector2 operator/(const float& f) const {
			return Vector2(x / f, y / f);
		}

		void operator/=(const Vector2& other) {
			x /= other.x;
			y /= other.y;
		}

		void operator/=(const float& f) {
			x /= f;
			y /= f;
		}

		bool operator<(const Vector2 &other) const {
			return (x*x + y*y) < (other.x*other.x + other.y*other.y);
		}

		bool operator<=(const Vector2 &other) const {
			return (x*x + y*y) <= (other.x*other.x + other.y*other.y);
		}

		bool operator>(const Vector2 &other) const {
			return (x*x + y*y) > (other.x*other.x + other.y*other.y);
		}

		bool operator>=(const Vector2 &other) const {
			return (x*x + y*y) >= (other.x*other.x + other.y*other.y);
		}

		bool operator==(const Vector2 &other) const {
			return x == other.x && y == other.y;
		}

		bool operator!=(const Vector2 &other) const {
			return x != other.x || y != other.y;
		}
	};

	std::ostream& operator<<(std::ostream &os, const Vector2 &v2);
}
