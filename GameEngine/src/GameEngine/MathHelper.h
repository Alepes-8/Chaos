#pragma once
#include <math.h>
#define PI 3.14159265
#define DEG_TO_RAD PI /180.0f
namespace GameEngine {

	struct Vector2 {
		float x;
		float y;

		Vector2(float _x = 0.0f, float _y = 0.0f)
			:x(_x), y(_y) {}

		float  MagnitudeSqr() {
			return x * x + y * y;
		}

		float Magnitude() {
			return (float)sqrt(x * x + y * y);
		}

		Vector2 Normalized() {
			float mag = Magnitude();
			return Vector2(x / mag, y / mag);
		}
	};

	inline Vector2 operator +(const Vector2& lhs, const Vector2& rhs) {
		return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	inline Vector2 operator -(const Vector2& lhs, const Vector2& rhs) {
		return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	struct Vector3 {
		float x;
		float y;
		float z;

		Vector3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
			:x(_x), y(_y), z(_z) {}

		float  MagnitudeSqr() {
			return x * x + y * y + z * z;
		}

		float Magnitude() {
			return (float)sqrt(MagnitudeSqr());
		}

		Vector3 Normalized() {
			float mag = Magnitude();
			return Vector3(x / mag, y / mag, z / mag);
		}

		Vector3 Vectorial_product(Vector3 v) {
			return Vector3{
				(y * v.z - z * v.y),
				(z * v.x - x * v.z),
				(x * v.y - y * v.x)
			};
		}
	};

	inline Vector3 operator +(const Vector3& lhs, const Vector3& rhs) {
		return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	inline Vector3 operator -(const Vector3& lhs, const Vector3& rhs) {
		return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	inline Vector3 operator+=(const Vector3& lhs, const Vector3& rhs) {
		return lhs + rhs;
	}

	inline Vector3 operator*(const Vector3& lhs, const float coef) {
		return Vector3(lhs.x * coef, lhs.y * coef, lhs.z * coef);
	}

	inline Vector3 operator*=(const Vector3& lhs, const float coef) {
		return lhs * coef;
	}

	struct rotationMatrix {
		float x00, x01, x02;
		float x10, x11, x12;
		float x20, x21, x22;

		rotationMatrix(Vector3 axis, float value) {
			float c = cos(value);
			float s = sin(value);

			Vector3 unit_axis = axis.Normalized();

			float x = unit_axis.x;
			float y = unit_axis.y;
			float z = unit_axis.z;

			//formula -> https://en.wikipedia.org/wiki/Rotation_matrix
			x00 = x * x * (1 - c) + c;
			x01 = x * y * (1 - c) - z * s;
			x02 = x * z * (1 - c) + y * s;
			x10 = x * y * (1 - c) + z * s;
			x11 = y * y * (1 - c) + c;
			x12 = y * z * (1 - c) - x * s;
			x20 = x * z * (1 - c) - y * s;
			x21 = y * z * (1 - c) + x * s;
			x22 = z * z * (1 - c) + c;
		}

		inline Vector3 rotate(const rotationMatrix& rm, const Vector3& v) {
			return Vector3(
				x00 * v.x + x01 * v.y + x02 * v.z,
				x10 * v.x + x11 * v.y + x12 * v.z,
				x20 * v.x + x21 * v.y + x22 * v.z
			);
		}
	};
}