#pragma once

#include "Vec2.h"

namespace OpenML 
{
	template <typename T>
	class Point2D
	{
	public:
		T x = 0.0f;
		T y = 0.0f;

		Point2D() {
		}

		Point2D(T x, T y) {
			this->x = x;
			this->y = y;
		}

		Point2D(Vec2<T> vector) {
			this->x = vector[0];
			this->y = vector[1];
		}

		T getDistance(Point2D<T> otherPoint) 
		{
			T distance = toVec2().distance(otherPoint.toVec2());
			return distance;
		}

		operator Vec2<T>&()
		{
			return Vec2<T>(x, y);
		}

		Vec2<T> toVec2()
		{
			return Vec2<T>(x, y);
		}

	};

	typedef Point2D<int> Point2Di;
	typedef Point2D<float> Point2Df;
	typedef Point2D<double> Point2Dd;
}