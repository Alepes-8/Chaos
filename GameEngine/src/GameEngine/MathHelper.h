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


	class MathHelper {
	public: 
		MathHelper();
		~MathHelper();
		bool InvMatrix(const float m[16], float invOut[16]);
	};
}