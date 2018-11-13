#pragma once

#include "Vec3.h"

namespace OpenML 
{
	template <typename T>
	class Point3D
	{
	public:
		T x = 0.0f;
		T y = 0.0f;
		T z = 0.0f;

		Point3D() {
		}
		Point3D(T x, T y, T z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
		Point3D(Vec3<T> vector) {
			this->x = vector[0];
			this->y = vector[1];
			this->z = vector[2];
		}
		Point3D(T* values) {
			this->x = values[0];
			this->y = values[1];
			this->z = values[2];
		}

		T distance(Point3D<T> otherPoint) 
		{
			T distance = toVec3().distance(otherPoint.toVec3());
			return distance;
		}

		operator Vec3<T>&()
		{
			return Vec3<T>(x, y, z);
		}

		Vec3<T> toVec3()
		{
			return Vec3<T>(x, y, z);
		}

		/// <summary>
		/// Compare this point to another one. Compare each component.
		/// </summary>
		API_INTERFACE bool operator==(const Point3D<T> &other) const
		{
			return x == other.x
				&& y == other.y
				&& z == other.z;
		}

	};

	typedef Point3D<int> Point3Di;
	typedef Point3D<float> Point3Df;
	typedef Point3D<double> Point3Dd;
}