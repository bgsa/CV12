#pragma once

#include "GlobalHeader.h"
#include <cassert>
#include "MathPP.h"
#include "Vec3.h"

#define VEC4_SIZE 4

template <typename T>
class Vec4
{
private:
	T values[VEC4_SIZE];

public:

	Vec4() { 
		values[0] = 0;
		values[1] = 0;
		values[2] = 0;
		values[3] = 0;
	}

	Vec4(Vec3<T> vector, T w) { 
		values[0] = vector.x();;
		values[1] = vector.y();
		values[2] = vector.z();
		values[3] = w;
	}

	Vec4(T x, T y, T z, T w) {
		values[0] = x;
		values[1] = y;
		values[2] = z;
		values[3] = w;
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
	/// Fourth value in the vector
	/// </summary>
	API_INTERFACE
	T w() {
		return values[3];
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
	/// Get the squared of the vector. It means the Vector Pow2 -> x^2 + y^2 + z^2 + w^2
	/// </summary>
	API_INTERFACE
	T squared()
	{
		return (values[0] * values[0]) + (values[1] * values[1]) + (values[2] * values[2]) + (values[3] * values[3]);
	}


	/// <summary>
	/// Get the maximun value in the vector
	/// </summary>
	API_INTERFACE T maximum()
	{
		T value = values[0];

		for (size_t i = 1; i < 4; i++)
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

		for (size_t i = 1; i < 4; i++)
			if (values[i] < value)
				value = values[i];

		return value;
	}

	/// <summary>
	/// Add a vector from current vector
	/// </summary>
	API_INTERFACE
	void add(Vec4<T> vector)
	{
		values[0] += vector[0];
		values[1] += vector[1];
		values[2] += vector[2];
		values[3] += vector[3];
	}

	/// <summary>
	/// Subtract a vector from current vector
	/// </summary>
	API_INTERFACE
	void subtract(Vec4<T> vector)
	{
		values[0] -= vector[0];
		values[1] -= vector[1];
		values[2] -= vector[2];
		values[3] -= vector[3];
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
		values[3] *= scale;
	}
	
	/// <summary>
	/// Dot Product / Scalar Product - return the angle between two vectors: A . B
	/// return u dot v
	/// <summary>
	API_INTERFACE
	T dot(Vec4<T> vector)
	{
		return values[0] * vector[0] + values[1] * vector[1] + values[2] * vector[2] + values[3] * vector[3];
	}

	/// <summary>
	/// Get the andle in radians between the vectors
	/// <summary>
	API_INTERFACE
	T angleRandians(Vec4<T> vectorB)
	{
		return dot(vectorB) / (length() * vectorB.length());
	}

	/// <summary>
	/// Get the andle in radians between the vectors
	/// <summary>
	API_INTERFACE
	T angleDegree(Vec4<T> vectorB)
	{
		T angleRadians = dot(vectorB) / (length() * vectorB.length());

		return (T)radiansToDegrees(angleRadians);
	}

	/// <summary>
	/// Get a normalized vector
	/// <summary>
	API_INTERFACE
	Vec4<T> normalize()
	{
		T vectorLength = length();

		return Vec4<T> {
			values[0] / vectorLength,
			values[1] / vectorLength,
			values[2] / vectorLength,
			values[3] / vectorLength,
		};
	}

	/// <summary>
	/// Normalize the current vector - change to unit vector
	/// <summary>
	API_INTERFACE
	void transformToUnit()
	{
		scale(T(1) / length());
	}

	/// <summary>
	/// Calculate the distance (Euclidean) from this vector to another one
	/// <summary>
	API_INTERFACE
	T distance(Vec4<T> vector)
	{
		T x = values[0] - vector[0];
		x = x*x;

		T y = values[1] - vector[1];
		y = y*y;

		T z = values[2] - vector[2];
		z = z*z;

		T w = values[3] - vector[3];
		w = w*w;

		return sqrtf(x + y + z + w);
	}

	/// <summary>
	/// Clone the vector to a new instance
	/// <summary>
	API_INTERFACE
	Vec4<T> clone()
	{
		return Vec4<T>(values[0], values[1], values[2], values[3]);
	}

	/// <summary>
	/// Multiply the vector to a scalar
	/// <summary>
	API_INTERFACE
	Vec4<T> operator*(T value)
	{
		Vec4<T> result;

		result[0] = values[0] * value;
		result[1] = values[1] * value;
		result[2] = values[2] * value;
		result[3] = values[3] * value;

		return result;
	}

	/// <summary>
	/// Sum this vector to another one
	/// <summary>
	API_INTERFACE
	Vec4<T> operator+(Vec4<T> vector)
	{
		Vec4<T> result;

		result[0] = values[0] + vector[0];
		result[1] = values[1] + vector[1];
		result[2] = values[2] + vector[2];
		result[3] = values[3] + vector[3];

		return result;
	}

	/// <summary>
	/// Sum a scalar to this vector
	/// <summary>
	API_INTERFACE
	Vec4<T> operator+(T value)
	{
		Vec4<T> result;

		result[0] = values[0] + value;
		result[1] = values[1] + value;
		result[2] = values[2] + value;
		result[3] = values[3] + value;

		return result;
	}

	/// <summary>
	/// Subtract this vector to another one
	/// <summary>
	API_INTERFACE
	Vec4<T> operator-(Vec4<T> vector)
	{
		Vec4<T> result;

		result[0] = values[0] - vector[0];
		result[1] = values[1] - vector[1];
		result[2] = values[2] - vector[2];
		result[3] = values[3] - vector[3];

		return result;
	}

	/// <summary>
	/// Subtract a scalar from this vector
	/// <summary>
	API_INTERFACE
	Vec4<T> operator-(T value)
	{
		Vec4<T> result;

		result[0] = values[0] - value;
		result[1] = values[1] - value;
		result[2] = values[2] - value;
		result[3] = values[3] - value;

		return result;
	}

	/// <summary>
	/// Compare this vector to another one. Compare each component.
	/// <summary>
	API_INTERFACE
	bool operator==(Vec4<T> vector)
	{
		return values[0] == vector[0]
			&& values[1] == vector[1]
			&& values[2] == vector[2]
			&& values[3] == vector[3];
	}

	/// <summary>
	/// Compare this vector to another one. Compare each component.
	/// <summary>
	API_INTERFACE
	bool operator==(T value)
	{
		return values[0] == value
			&& values[1] == value
			&& values[2] == value
			&& values[3] == value;
	}

	/// <summary>
	/// Compare this vector to another one. Compare each component.
	/// <summary>
	API_INTERFACE
	bool operator!=(Vec4<T> vector)
	{
		return values[0] != vector[0]
			|| values[1] != vector[1]
			|| values[2] != vector[2]
			|| values[3] != vector[3];
	}

	/// <summary>
	/// Get a index from the vector
	/// <summary>
	API_INTERFACE
	T& operator[](int index)
	{
		assert(index >= 0 && index < VEC4_SIZE);

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

	/// <summary>
	/// Convert to Vec3 - ignore the W component
	/// <summary>
	API_INTERFACE
	Vec3<T> toVec3() {
		return Vec3<T> { values[0], values[1], values[2] };
	}

};

typedef Vec4<unsigned char> Vec4uc;
typedef Vec4<unsigned int> Vec4ui;
typedef Vec4<unsigned short> Vec4us;
typedef Vec4<char> Vec4c;
typedef Vec4<short> Vec4s;
typedef Vec4<int> Vec4i;
typedef Vec4<float> Vec4f;
typedef Vec4<double> Vec4d;