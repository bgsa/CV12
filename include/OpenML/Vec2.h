#pragma once

#include "GlobalHeader.h"
#include <cassert>
#include "MathPP.h"

#define VEC2_SIZE 2

template <typename T>
class Vec2
{
private:
	T values[VEC2_SIZE];

public:

	Vec2() { }
	Vec2(T x, T y) {
		values[0] = x;
		values[1] = y;
	}

	/// <summary>
	/// First value in the vector
	/// </summary>
	API_INTERFACE T x() {
		return values[0];
	}

	/// <summary>
	/// Second value in the vector
	/// </summary>
	API_INTERFACE T y() {
		return values[1];
	}

	/// <summary>
	/// Get the component values in the vector
	/// </summary>
	API_INTERFACE T* getValues() {
		return values;
	}
	
	/// <summary>
	/// Scale the current matrix
	/// </summary>
	API_INTERFACE T maximum()
	{
		if (values[0] > values[1])
			return values[0];
		else
			return values[1];
	}

	/// <summary>
	/// Scale the current matrix
	/// </summary>
	API_INTERFACE T minimum()
	{
		if (values[0] < values[1])
			return values[0];
		else
			return values[1];
	}

	/// <summary>
	/// Get the length / norma from the vector -> ||v||
	/// </summary>
	API_INTERFACE T length()
	{
		return sqrtf(squared());
	}

	/// <summary>
	/// Get the squared of the vector. It means the Vector Pow2 -> x^2 + y^2
	/// </summary>
	API_INTERFACE T squared()
	{
		return (values[0] * values[0]) + (values[1] * values[1]);
	}

	/// <summary>
	/// Add a vector from current vector
	/// </summary>
	API_INTERFACE void add(Vec2<T> vector)
	{
		values[0] += vector[0];
		values[1] += vector[1];
	}

	/// <summary>
	/// Subtract a vector from current vector
	/// </summary>
	API_INTERFACE void subtract(Vec2<T> vector)
	{
		values[0] -= vector[0];
		values[1] -= vector[1];
	}

	/// <summary>
	/// Scale the vector from a scalar => v * scalar
	/// </summary>
	API_INTERFACE void scale(T scale)
	{
		values[0] *= scale;
		values[1] *= scale;
	}

	/// <summary>
	/// Dot Product / Scalar Product between two vectors
	/// return u dot v
	/// <summary>
	API_INTERFACE T dot(Vec2<T> vector)
	{
		return values[0] * vector[0] + values[1] * vector[1];
	}

	/// <summary>
	/// Get the angle in radians between two vectors: A . B
	/// <summary>
	API_INTERFACE T angleRandians(Vec2<T> vectorB)
	{
		T vec1Len = length();
		T vec2Len = vectorB.length();

		if (vec1Len == T(0)) // vec-Len == 0 means division by zero and return "nan" (not a number)
			vec1Len = T(0.01);

		if (vec2Len == T(0)) // vec-Len == 0 means division by zero and return "nan" (not a number)
			vec2Len = T(0.01);

		return dot(vectorB) / (vec1Len * vec2Len);
	}

	/// <summary>
	/// Get the andle in radians between the vectors
	/// <summary>
	API_INTERFACE T angleDegree(Vec2<T> vectorB)
	{
		T angleRadians = dot(vectorB) / (length() * vectorB.length());

		return (T)radiansToDegrees(angleRadians);
	}

	/// <summary>
	/// Get a normalized vector
	/// <summary>
	API_INTERFACE Vec2<T> normalize()
	{
		T vectorLength = length();

		return Vec2<T> {
			values[0] / vectorLength,
			values[1] / vectorLength
		};
	}

	/// <summary>
	/// Normalize the current vector - change to unit vector
	/// <summary>
	API_INTERFACE void transformToUnit()
	{
		scale(T(1) / length());
	}

	/// <summary>
	/// Calculate the distance (Euclidean) from this vector to another one
	/// <summary>
	API_INTERFACE T distance(Vec2<T> vector)
	{
		T x = values[0] - vector[0];
		x = x*x;

		T y = values[1] - vector[1];
		y = y*y;
		
		return sqrtf(x + y);
	}

	/// <summary>
	/// Find a orthogonal projection between two vectors
	/// Return Two vectors
	/// <summary>
	API_INTERFACE Vec2<T>* orthogonalProjection(Vec2<T> vector) 
	{
		T value = dot(vector) / vector.squared();

		Vec2<T> v1 = vector * value;
		Vec2<T> v2 = {
			vector[0] - v1[0],
			vector[1] - v1[1]
		};

		Vec2<T>* result = new Vec2<T>[2];
		result[0] = v1;
		result[1] = v2;
		
		return result;
	}
	

	/// <summary>
	/// Clone the vector to a new instance
	/// <summary>
	API_INTERFACE Vec2<T> clone()
	{
		return Vec2<T>(values[0], values[1]);
	}

	/// <summary>
	/// Multiply the vector to a scalar
	/// <summary>
	API_INTERFACE Vec2<T> operator*(T value)
	{
		Vec2<T> result;

		result[0] = values[0] * value;
		result[1] = values[1] * value;

		return result;
	}

	/// <summary>
	/// Multiply the vector to a scalar
	/// </summary>
	API_INTERFACE Vec2<T> operator/(T value)
	{
		Vec2<T> result;

		result[0] = values[0] / value;
		result[1] = values[1] / value;

		return result;
	}

	/// <summary>
	/// Sum this vector to another one
	/// <summary>
	API_INTERFACE Vec2<T> operator+(Vec2<T> vector)
	{
		Vec2<T> result;

		result[0] = values[0] + vector[0];
		result[1] = values[1] + vector[1];

		return result;
	}

	/// <summary>
	/// Sum a scalar to this vector
	/// <summary>
	API_INTERFACE Vec2<T> operator+(T value)
	{
		Vec2<T> result;

		result[0] = values[0] + value;
		result[1] = values[1] + value;

		return result;
	}

	/// <summary>
	/// Subtract this vector to another one
	/// <summary>
	API_INTERFACE Vec2<T> operator-(Vec2<T> vector)
	{
		Vec2<T> result;

		result[0] = values[0] - vector[0];
		result[1] = values[1] - vector[1];

		return result;
	}

	/// <summary>
	/// Subtract a scalar from this vector
	/// <summary>
	API_INTERFACE Vec2<T> operator-(T value)
	{
		Vec2<T> result;

		result[0] = values[0] - value;
		result[1] = values[1] - value;

		return result;
	}

	/// <summary>
	/// Compare this vector to another one. Compare each component.
	/// <summary>
	API_INTERFACE bool operator==(Vec2<T> vector)
	{
		return values[0] == vector[0]
			&& values[1] == vector[1];
	}
	
	/// <summary>
	/// Compare this vector to another one. Compare each component.
	/// <summary>
	API_INTERFACE bool operator==(T value)
	{
		return values[0] == value
			&& values[1] == value;
	}

	/// <summary>
	/// Compare this vector to another one. Compare each component.
	/// <summary>
	API_INTERFACE bool operator!=(Vec2<T> vector)
	{
		return values[0] != vector[0]
			|| values[1] != vector[1];
	}

	/// <summary>
	/// Get a index from the vector
	/// <summary>
	T& operator[](int index)
	{
		assert(index >= 0 && index < VEC2_SIZE);

		return values[index];
	}

	/// <summary>
	/// Auto convertion to void *
	/// </summary>
	API_INTERFACE operator T*() const
	{
		return values;
	}

	/// <summary>
	/// Auto convertion to T *
	/// It is the same of convertion to float* or int* or double*, whatever T is.
	/// </summary>
	API_INTERFACE operator T*()
	{
		return values;
	}

};

typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;