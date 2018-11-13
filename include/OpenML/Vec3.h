#pragma once

#include "GlobalHeader.h"
#include <cassert>
#include "MathPP.h"

#define VEC3_SIZE 3

template <typename T>
class Vec3
{
private:
	T values[VEC3_SIZE];

public:

	Vec3() {
		values[0] = T(0.0f);
		values[1] = T(0.0f);
		values[2] = T(0.0f);
	}

	Vec3(T x, T y, T z) {
		values[0] = x;
		values[1] = y;
		values[2] = z;
	}

	/// <summary>
	/// First value in the vector
	/// </summary>
	API_INTERFACE
	T x() {
		return values[0];
	}

	/// <summary>
	/// Second value in the vector
	/// </summary>
	API_INTERFACE
	T y() {
		return values[1];
	}

	/// <summary>
	/// Third value in the vector
	/// </summary>
	API_INTERFACE
	T z() {
		return values[2];
	}

	/// <summary>
	/// Get the component values in the vector
	/// </summary>
	API_INTERFACE
	T* getValues() {
		return values;
	}

	/// <summary>
	/// Get the length / norma from the vector -> ||v||
	/// </summary>
	API_INTERFACE
	T length()
	{
		return sqrtf(squared());
	}
	
	/// <summary>
	/// Get the squared of the vector. It means the Vector Pow2 -> x^2 + y^2 + z^2
	/// </summary>
	API_INTERFACE
	T squared()
	{
		return (values[0] * values[0]) + (values[1] * values[1]) + (values[2] * values[2]);
	}

	/// <summary>
	/// Get the maximun value in the vector
	/// </summary>
	API_INTERFACE T maximum()
	{
		T value = values[0];

		for (size_t i = 1; i < 3; i++)
			if (values[i] > value)
				value = values[i];

		return value;
	}

	/// <summary>
	/// Get the min value in the vector
	/// </summary>
	API_INTERFACE T minimum()
	{
		T value = values[0];

		for (size_t i = 1; i < 3; i++)
			if (values[i] < value)
				value = values[i];

		return value;
	}

	/// <summary>
	/// Add a vector from current vector
	/// </summary>
	API_INTERFACE
	void add(Vec3<T> vector)
	{
		values[0] += vector[0];
		values[1] += vector[1];
		values[2] += vector[2];
	}

	/// <summary>
	/// Subtract a vector from current vector
	/// </summary>
	API_INTERFACE
	void subtract(Vec3<T> vector)
	{
		values[0] -= vector[0];
		values[1] -= vector[1];
		values[2] -= vector[2];
	}

	/// <summary>
	/// Scale the vector from a scalar => v * scalar
	/// </summary>
	API_INTERFACE
	void scale(T scale)
	{
		values[0] *= scale;
		values[1] *= scale;
		values[2] *= scale;
	}

	/// <summary>
	/// Cross Product - return a perpendicular vector, regards two vectors => u x v
	/// </summary>
	API_INTERFACE
	Vec3<T> cross(Vec3<T> vector)
	{
		Vec3<T> result = { 0,0,0 };

		result[0] = values[1] * vector[2] - vector[1] * values[2];
		result[1] = -values[0] * vector[2] + vector[0] * values[2];
		result[2] = values[0] * vector[1] - vector[0] * values[1];

		return result;
	}

	/// <summary>
	/// Dot Product / Scalar Product - between two vectors: A . B
	/// return u dot v
	/// </summary>
	API_INTERFACE
	T dot(Vec3<T> vector)
	{
		return values[0] * vector[0] + values[1] * vector[1] + values[2] * vector[2];
	}

	/// <summary>
	/// Get the andle in radians between the vectors
	/// Obs.: if the vectors are normalized, can use: acosf(dot(vectorB));
	/// </summary>
	API_INTERFACE
	T angleRandians(Vec3<T> vectorB)
	{
		return dot(vectorB) / (length() * vectorB.length());
	}

	/// <summary>
	/// Get the andle in radians between the vectors
	/// Obs.: if the vectors are normalized, can use: acosf(dot(vectorB));
	/// </summary>
	API_INTERFACE
	T angleDegree(Vec3<T> vectorB)
	{
		T angleRadians = dot(vectorB) / (length() * vectorB.length());

		return (T) radiansToDegrees( angleRadians );
	}

	/// <summary>
	/// Get a normalized vector
	/// </summary>
	API_INTERFACE
	Vec3<T> normalize()
	{
		T vectorLength = length();

		return Vec3<T> { 
			values[0] / vectorLength,
			values[1] / vectorLength,
			values[2] / vectorLength,
		};
	}

	/// <summary>
	/// Normalize the current vector - change to unit vector
	/// </summary>
	API_INTERFACE
	void transformToUnit()
	{
		scale(T(1) / length());
	}

	/// <summary>
	/// Calculate the distance (Euclidean) from this vector to another one
	/// </summary>
	API_INTERFACE
	T distance(Vec3<T> vector)
	{
		T x = values[0] - vector[0];
		x = x*x;

		T y = values[1] - vector[1];
		y = y*y;

		T z = values[2] - vector[2];
		z = z*z;

		return sqrtf(x + y + z);
	}
		
	/// <summary>
	/// Clone the vector to a new instance
	/// </summary>
	API_INTERFACE
	Vec3<T> clone() 
	{
		return Vec3<T>(values[0], values[1], values[2]);
	}

	/// <summary>
	/// Set new value to the vector
	/// </summary>
	API_INTERFACE void operator=(Vec3<T> value)
	{
		values[0] = value[0];
		values[1] = value[1];
		values[2] = value[2];
	}

	/// <summary>
	/// Multiply the vector to a scalar
	/// </summary>
	API_INTERFACE Vec3<T> operator/(T value)
	{
		Vec3<T> result;

		result[0] = values[0] / value;
		result[1] = values[1] / value;
		result[2] = values[2] / value;

		return result;
	}

	/// <summary>
	/// Multiply the vector to a scalar
	/// </summary>
	API_INTERFACE
	Vec3<T> operator*(T value)
	{
		Vec3<T> result;

		result[0] = values[0] * value;
		result[1] = values[1] * value;
		result[2] = values[2] * value;

		return result;
	}

	/// <summary>
	/// Multiply the vector to another one using Cross Product
	/// </summary>
	API_INTERFACE
	Vec3<T> operator*(Vec3<T> vector)
	{
		return cross(vector);
	}

	/// <summary>
	/// Sum this vector to another one
	/// </summary>
	API_INTERFACE
	Vec3<T> operator+(Vec3<T> vector)
	{
		Vec3<T> result;

		result[0] = values[0] + vector[0];
		result[1] = values[1] + vector[1];
		result[2] = values[2] + vector[2];

		return result;
	}

	/// <summary>
	/// Sum this vector to another one
	/// </summary>
	API_INTERFACE
	void operator+=(Vec3<T> vector)
	{
		values[0] = values[0] + vector[0];
		values[1] = values[1] + vector[1];
		values[2] = values[2] + vector[2];
	}

	/// <summary>
	/// Sum a scalar to this vector
	/// </summary>
	API_INTERFACE
	Vec3<T> operator+(T value)
	{
		Vec3<T> result;

		result[0] = values[0] + value;
		result[1] = values[1] + value;
		result[2] = values[2] + value;

		return result;
	}

	/// <summary>
	/// Subtract this vector to another one
	/// </summary>
	API_INTERFACE
	Vec3<T> operator-(Vec3<T> vector)
	{
		Vec3<T> result;

		result[0] = values[0] - vector[0];
		result[1] = values[1] - vector[1];
		result[2] = values[2] - vector[2];

		return result;
	}

	/// <summary>
	/// Subtract this vector to another one
	/// </summary>
	API_INTERFACE
	void operator-=(Vec3<T> vector)
	{
		values[0] = values[0] - vector[0];
		values[1] = values[1] - vector[1];
		values[2] = values[2] - vector[2];
	}

	/// <summary>
	/// Subtract a scalar from this vector
	/// </summary>
	API_INTERFACE
	Vec3<T> operator-(T value)
	{
		Vec3<T> result;

		result[0] = values[0] - value;
		result[1] = values[1] - value;
		result[2] = values[2] - value;

		return result;
	}

	/// <summary>
	/// Compare this vector to another one. Compare each component.
	/// </summary>
	API_INTERFACE
	bool operator==(Vec3<T> vector)
	{
		return values[0] == vector[0] 
			&& values[1] == vector[1] 
			&& values[2] == vector[2];
	}

	/// <summary>
	/// Compare this vector to another one. Compare each component.
	/// </summary>
	API_INTERFACE
	bool operator==(T value)
	{
		return values[0] == value
			&& values[1] == value
			&& values[2] == value;
	}

	/// <summary>
	/// Compare this vector to another one. Compare each component.
	/// </summary>
	API_INTERFACE
	bool operator!=(Vec3<T> vector)
	{
		return values[0] != vector[0]
			|| values[1] != vector[1]
			|| values[2] != vector[2];
	}

	/// <summary>
	/// Get a index from the vector
	/// </summary>
	T& operator[](int index)
	{
		assert(index >= 0 && index < VEC3_SIZE);

		return values[index];
	}

	/// <summary>
	/// Auto convertion to void *
	/// </summary>
	API_INTERFACE operator void*() const
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

	/*
	Vec3(Vec2<T> vector, T z) {
		values[0] = vector[0];
		values[1] = vector[1];
		values[2] = z;
	}
	/*
	API_INTERFACE Vec2<T> toVec2()
	{
		return Vec2<T>( values[0], values[1] );
	}
	*/

};

typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;