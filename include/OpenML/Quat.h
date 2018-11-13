#pragma once

#include <cassert>
#include "GlobalHeader.h"
#include "Vec3.h"

#define QUAT_SIZE 4

template <typename T>
class Quat
{
private:
	T values[QUAT_SIZE];

public:

	/// <summary>
	/// Default constructor
	/// Load a empty quaternion = 0
	/// </summary>
	API_INTERFACE Quat()
	{
		static T emptyQuaternion[QUAT_SIZE] = { 0.0f, 0.0f, 0.0f, 0.0f };

		memcpy(&values, emptyQuaternion, sizeof(values));
	}

	/// <summary>
	/// Constructor with initialized values
	/// </summary>
	API_INTERFACE Quat(T* values)
	{
		memcpy(&this->values, values, sizeof(this->values));
	}

	/// <summary>
	/// Constructor with initialized values
	/// </summary>
	API_INTERFACE Quat(T value1, T value2, T value3, T value4)
	{
		values[0] = value1;
		values[1] = value2;
		values[2] = value3;
		values[3] = value4;
	}

	/// <summary>
	/// Constructor with a 3D vector
	/// </summary>
	API_INTERFACE Quat(Vec3<T> vector)
	{
		values[0] = vector[0];
		values[1] = vector[1];
		values[2] = vector[2];
		values[3] = 0.0f;
	}

	/// <summary>
	/// Get the values from current quaternion
	/// </summary>
	API_INTERFACE T* getValues()
	{
		return values;
	}
	
	/// <summary>
	/// Get the x value
	/// </summary>
	API_INTERFACE T x()
	{
		return values[0];
	}

	/// <summary>
	/// Get the y value
	/// </summary>
	API_INTERFACE T y()
	{
		return values[1];
	}

	/// <summary>
	/// Get the z value
	/// </summary>
	API_INTERFACE T z()
	{
		return values[2];
	}

	/// <summary>
	/// Get the w value
	/// </summary>
	API_INTERFACE T w()
	{
		return values[3];
	}

	/// <summary>
	/// Add/Sum two quaternions
	/// </summary>
	API_INTERFACE Quat<T> add(Quat<T> quatB)
	{
		Quat<T> result;

		result[0] = values[0] + quatB[0];
		result[1] = values[1] + quatB[1];
		result[2] = values[2] + quatB[2];
		result[3] = values[3] + quatB[3];

		return result;
	}

	/// <summary>
	/// Subtract two quaternions
	/// </summary>
	API_INTERFACE Quat<T> subtract(Quat<T> quatB)
	{
		Quat<T> result;

		result[0] = values[0] - quatB[0];
		result[1] = values[1] - quatB[1];
		result[2] = values[2] - quatB[2];
		result[3] = values[3] - quatB[3];

		return result;
	}

	/// <summary>
	/// Scale a quaternion
	/// </summary>
	API_INTERFACE void scale(T value)
	{
		values[0] *= value;
		values[1] *= value;
		values[2] *= value;
		values[3] *= value;
	}

	/// <summary>
	/// Create a new quaternion scaled
	/// </summary>
	API_INTERFACE Quat<T> createScale(T value)
	{
		Quat<T> result;

		result[0] = values[0] * value;
		result[1] = values[1] * value;
		result[2] = values[2] * value;
		result[3] = values[3] * value;

		return result;
	}

	/// <summary>
	/// Scale a quaternion
	/// </summary>
	API_INTERFACE Quat<T> multiply(Quat<T> quat)
	{
		Quat<T> result;

		result[0] =  values[0] * quat[3] + values[1] * quat[2] - values[2] * quat[1] + values[3] * quat[0];
		result[1] = -values[0] * quat[2] + values[1] * quat[3] + values[2] * quat[0] + values[3] * quat[1];
		result[2] =  values[0] * quat[1] - values[1] * quat[0] + values[2] * quat[3] + values[3] * quat[2];
		result[3] = -values[0] * quat[0] - values[1] * quat[1] - values[2] * quat[2] + values[3] * quat[3];

		return result;
	}

	/// <summary>
	/// Length/Magnitude of quaternion
	/// </summary>
	API_INTERFACE T length()
	{
		double value = sqrt(values[0] * values[0] + values[1] * values[1] + values[2] * values[2] + values[3] * values[3]);

		return T(value);
	}

	/// <summary>
	/// Craete a new Quaternion Normalized
	/// </summary>
	API_INTERFACE Quat<T> normalize()
	{
		Quat<T> quat;

		T magnitude = length();

		quat[0] = values[0] / magnitude;
		quat[1] = values[1] / magnitude;
		quat[2] = values[2] / magnitude;
		quat[3] = values[3] / magnitude;

		return quat;
	}

	/// <summary>
	/// Craete a new Quaternion Conjugated
	/// </summary>
	API_INTERFACE Quat<T> conjugate()
	{
		Quat<T> quat;

		quat[0] = -values[0];
		quat[1] = -values[1];
		quat[2] = -values[2];
		quat[3] = values[3];

		return quat;
	}

	/// <summary>
	/// Product Scalar of two quaternion
	/// </summary>
	API_INTERFACE T dot(Quat<T> quatB)
	{
		T result = sqrt(values[3] * quatB[3] + values[0] * quatB[0] + values[1] * quatB[1] + values[2] * quatB[2]);

		return result;
	}

	/// <summary>
	/// Craete a Inversed Quaternion
	/// Return a quaternion that if multiplied by current quaternion results in value 1 ot the current quternion ifs length/norm is zero
	/// </summary>
	API_INTERFACE Quat<T> inverse()
	{
		Quat<T> result(
			values[0],
			values[1],
			values[2],
			values[3]
		);

		T magnitude = length();

		if (magnitude == T(0))
			return result;
		
		result.scale(1 / (magnitude * magnitude));

		return result;
	}

	/// <summary>
	/// Craete a rotation unit quaternion bases on angle (in radians) and directional vector provided
	/// </summary>
	API_INTERFACE static Quat<T> createRotate(double angleInRadians, Vec3<T> position)
	{
		double halfAngle = angleInRadians / 2;
		double sinHalfAngle = sin(halfAngle);
		double cosineHalfAngle = cos(halfAngle);

		Vec3<T> positionNomralized = position.normalize();

		Quat<T> result(
			T(sinHalfAngle * positionNomralized[0]),
			T(sinHalfAngle * positionNomralized[1]),
			T(sinHalfAngle * positionNomralized[2]),
			T(cosineHalfAngle)
		);

		return result;
	}

	/// <summary>
	/// Return a quaternion rotated bases on rotation quaternion provided in parameter
	/// The parameter can/must be used with createRotation static method
	/// </summary>
	API_INTERFACE Quat<T> rotate(Quat<T> r)
	{
		return r * (*this * r.conjugate());
	}

	/// <summary>
	/// Return a quaternion rotated bases on angle and a directional vector
	/// </summary>
	API_INTERFACE Quat<T> rotate(double angleInRadians, Vec3<T> vector)
	{
		Quat<T> rotationalQuaternion = Quat<T>::createRotate(angleInRadians, vector);

		return rotate(rotationalQuaternion);
	}

	/// <summary>
	/// Quaternion lerp. Linear quaternion interpolation method. This method is the quickest, but is also least accurate. The method does not always generate normalized output.
	/// t parameter is [0,1]
	/// </summary>
	API_INTERFACE Quat<T> linearInterpolate(Quat<T> quatB, T t)
	{
		return createScale(T(1) - t) + quatB.scale(t);
	}

	/// <summary>
	/// Quaternion nlerp. Linear quaternion interpolation method. This method is the quickest, but is also least accurate.
	/// This method normalize the result
	/// t parameter is [0,1]
	/// </summary>
	API_INTERFACE Quat<T> linearInterpolateNormalized(Quat<T> quatB, T t)
	{
		return linearInterpolate(quatB, t).normalize();
	}

	/// <summary>
	/// Get the size in Bytes of Quaternion
	/// </summary>
	API_INTERFACE size_t sizeInBytes()
	{
		return QUAT_SIZE * sizeof(T);
	}

	/// <summary>
	/// Convertion to Vec3
	/// </summary>
	API_INTERFACE Vec3<T> toVec3()
	{
		return Vec3<T>(values[0], values[1], values[2]);
	}

	/// <summary>
	/// Get a index from the quaternion
	/// </summary>
	API_INTERFACE T& operator[](int index)
	{
		assert(index >= 0 && index < QUAT_SIZE);

		return values[index];
	}

	/// <summary>
	/// Add/Sum two quaternions
	/// </summary>
	API_INTERFACE Quat<T> operator+(Quat<T> quatB)
	{
		return add(quatB);
	}

	/// <summary>
	/// Add/Sum two quaternions
	/// </summary>
	API_INTERFACE Quat<T> operator-(Quat<T> quatB)
	{
		return subtract(quatB);
	}
	
	/// <summary>
	/// Multiply the quaternion to another one
	/// </summary>
	API_INTERFACE Quat<T> operator*(Quat<T> quat)
	{
		return multiply(quat);
	}

	/// <summary>
	/// Multiply the quaternion to a scalar
	/// Return a new quaternion scaled
	/// </summary>
	API_INTERFACE Quat<T> operator*(T value)
	{
		return createScale(value);
	}

	/// <summary>
	/// Auto convertion to Vec3
	/// </summary>
	API_INTERFACE operator Vec3<T>()
	{
		return toVec3();
	}

	/// <summary>
	/// Auto convertion to void *
	/// </summary>
	API_INTERFACE operator void*() const
	{
		return values;
	}

};

typedef Quat<int>	 Quati;
typedef Quat<float>  Quatf;
typedef Quat<double> Quatd;
