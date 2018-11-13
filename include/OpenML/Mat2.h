#pragma once

#include "GlobalHeader.h"
#include <cassert>
#include <vector>
#include "MathPP.h"
#include "Mat.h"
#include "Vec2.h"

#define MAT2_SIZE 4
#define MAT2_ROWSIZE 2

template <typename T>
struct AutovalueAutovector2 {
	T autovalue;
	Vec2<T> autovector;
};

template <typename T>
class Mat2 : public Mat<T>
{
private:
	T values[MAT2_SIZE];

public:

	/// <summary>
	/// Default constructor
	/// Load a empty matrix = 0
	/// </summary>
	API_INTERFACE Mat2()
	{
		static T emptyMatrix[MAT2_SIZE] = {
			0.0f, 0.0f,
			0.0f, 0.0f,
		};

		memcpy(&values, emptyMatrix, sizeof(values));
	}

	/// <summary>
	/// Constructor with initialized values
	/// </summary>
	API_INTERFACE Mat2(T* values)
	{
		memcpy(&this->values, values, sizeof(this->values));
	}

	/// <summary>
	/// Constructor with initialized values - COL ORDER
	/// </summary>
	API_INTERFACE Mat2(T value11, T value12, 
					   T value21, T value22)
	{
		values[0] = value11;
		values[1] = value12;
		values[2] = value21;
		values[3] = value22;
	}

	/// <summary>
	/// Get the values from current matrix
	/// </summary>
	API_INTERFACE T* getValues()
	{
		return values;
	}

	/// <summary>
	/// Get the value from current matrix
	/// COLUMN MAJOR ORDER
	/// X and Y: 1 index base
	/// </summary>
	API_INTERFACE T getValue(int x, int y)
	{
		x--;
		y--;

		return values[y * MAT2_ROWSIZE + x];
	}

	/// <summary>
	/// Get the X axis
	/// COLUMN MAJOR ORDER
	/// </summary>
	API_INTERFACE Vec2<T> xAxis()
	{
		Vec2<T> result;

#ifdef MAJOR_COLUMN_ORDER
		result = Vec2<T>{
			values[0],
			values[2]
		};
#else
		result = Vec2<T>{
			values[0],
			values[1]
		};
#endif

		return result;
	}

	/// <summary>
	/// Get the Y axis
	/// COLUMN MAJOR ORDER
	/// </summary>
	API_INTERFACE Vec2<T> yAxis()
	{
		Vec2<T> result;

#ifdef MAJOR_COLUMN_ORDER
			result = Vec2<T>{
				values[1],
				values[3]
			};
#else
			result = Vec2<T>{
				values[2],
				values[3]
			};
#endif

		return result;
	}

	/// <summary>
	/// Get the main / principal / major / primary diagonal from matrix
	/// </summary>
	API_INTERFACE Vec2<T> primaryDiagonal()
	{
		return Vec2<T> {
				values[0],
				values[3]
		};
	}

	/// <summary>
	/// Get the antidiagonal / counter / minor / secondary diagonal from matrix
	/// </summary>
	API_INTERFACE Vec2<T> secondaryDiagonal()
	{
		return Vec2<T> {
				values[1],
				values[2]
		};
	}

	/// <summary>
	/// Load a identity matrix
	/// </summary>
	API_INTERFACE static Mat2<T> identity()
	{
		static T identityMatrix[MAT2_SIZE] = {
			1.0f, 0.0f,
			0.0f, 1.0f
		};

		Mat2 result;
		memcpy(&result, identityMatrix, sizeof(values));

		return result;
	}

	/// <summary>
	/// Transpose matrix - swap rows by columns
	/// </summary>
	API_INTERFACE Mat2<T> transpose()
	{
		Mat2<T> result;

		//copy principal diagonal
		result[0] = values[0];
		result[3] = values[3];

		//swap others numbers
		float temp = values[1];
		result[1] = values[2];
		result[2] = temp;

		return result;
	}

	/// <summary>
	/// Multiply this matrix with the parametrized matrix => AxB
	/// </summary>
	API_INTERFACE Mat2<T> multiply(Mat2<T> matrixB)
	{
		Mat2<T> result;

#ifdef MAJOR_COLUMN_ORDER
		for (int line = 0; line < MAT2_ROWSIZE; line++)
		{
			T ai0 = values[(0 * MAT2_ROWSIZE) + line];
			T ai1 = values[(1 * MAT2_ROWSIZE) + line];

			result[(0 * MAT2_ROWSIZE) + line] = ai0 * matrixB[(0 * MAT2_ROWSIZE) + 0] + ai1 * matrixB[(0 * MAT2_ROWSIZE) + 1];
			result[(1 * MAT2_ROWSIZE) + line] = ai0 * matrixB[(1 * MAT2_ROWSIZE) + 0] + ai1 * matrixB[(1 * MAT2_ROWSIZE) + 1];
		}
#else
		for (int column = 0; column < MAT2_ROWSIZE; column++)
		{
			T ai0 = values[(column * MAT2_ROWSIZE) + 0];
			T ai1 = values[(column * MAT2_ROWSIZE) + 1];

			result[(column * MAT2_ROWSIZE) + 0] = ai0 * matrixB[(0 * MAT2_ROWSIZE) + 0] + ai1 * matrixB[(1 * MAT2_ROWSIZE) + 0];
			result[(column * MAT2_ROWSIZE) + 1] = ai0 * matrixB[(0 * MAT2_ROWSIZE) + 1] + ai1 * matrixB[(1 * MAT2_ROWSIZE) + 1];
		}
#endif

		return result;
	}

	/// <summary>
	/// Multiply this matrix with the parametrized vector => AxB
	/// </summary>
	API_INTERFACE Vec2<T> multiply(Vec2<T> vector)
	{
		Vec2<T> result;

		result[0] = values[0 * MAT2_ROWSIZE + 0] * vector[0] + values[0 * MAT2_ROWSIZE + 1] * vector[1];
		result[1] = values[1 * MAT2_ROWSIZE + 0] * vector[0] + values[1 * MAT2_ROWSIZE + 1] * vector[1];

		return result;
	}

	/// <summary>
	/// Create a scaled matrix
	/// </summary>
	API_INTERFACE static Mat2<T> createScale(T xScale, T yScale)
	{
		Mat2<T> result = Mat2<T>::identity();

		result.scale(xScale, yScale);

		return result;
	}

	/// <summary>
	/// Scale the current matrix
	/// </summary>
	API_INTERFACE void scale(T xScale, T yScale)
	{
		values[0] *= xScale;
		values[3] *= yScale;
	}
	
	/// <summary>
	/// Craete a translation matrix
	/// </summary>
	API_INTERFACE static Mat2<T> createTranslate(T x, T y)
	{
		Mat2<T> result = Mat2<T>::identity();
		
#ifdef MAJOR_COLUMN_ORDER
		result[2] = x;
		result[3] = y;
#else
		result[1] = x;
		result[3] = y;
#endif

		return result;
	}

	/// <summary>
	/// Get the deeterminant of the Matrix
	/// </summary>
	API_INTERFACE T determinant()
	{
		return values[0] * values[3] - values[1] * values[2];
	}

	/// <summary>
	/// Get the autovalue of the matrix
	/// </summary>
	API_INTERFACE AutovalueAutovector2<T> getAutovalueAndAutovector(const unsigned short maxIteration = 5)
	{
		Mat2<T> matrix = *this;
		Vec2<T> autovector = { T(1), T(1) };
		T autovalue;

		for (unsigned short iterationIndex = 0; iterationIndex < maxIteration; iterationIndex++)
		{
			Vec2<T> ax = matrix * autovector;
			autovalue = ax.maximum();
			autovector = ax / autovalue;
		}

		return AutovalueAutovector2<T>{ autovalue, autovector };
	}

	/// <summary>
	/// Get the size in Bytes of Mat3
	/// </summary>
	API_INTERFACE size_t sizeInBytes()
	{
		return MAT2_SIZE * sizeof(T);
	}

	/// <summary>
	/// Clone this matrix
	/// </summary>
	API_INTERFACE Mat2<T> clone()
	{
		Mat2<T> result;

		memcpy(&result, this, sizeof(Mat2<T>));

		return result;
	}

	/// <summary>
	/// Get a index from the vector
	/// </summary>
	API_INTERFACE T& operator[](int index)
	{
		assert(index >= 0 && index < MAT2_SIZE);

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
	/// Multiply the matrix to another one
	/// </summary>
	API_INTERFACE Mat2<T> operator*(Mat2<T> matrix)
	{
		return multiply(matrix);
	}

	/// <summary>
	/// Multiply the matrix to 2D vector
	/// </summary>
	API_INTERFACE Vec2<T> operator*(Vec2<T> matrix)
	{
		return multiply(matrix);
	}

	/// <summary>
	/// Multiply the matrix to another one
	/// </summary>
	API_INTERFACE void operator*=(Mat2<T> matrix)
	{
		memcpy(&this->values, multiply(matrix).values, sizeof(this->values));
	}

	/// <summary>
	/// Get the matrix content as string
	/// </summary>
	API_INTERFACE string toString()
	{
		return Mat<T>::toString(values, MAT2_SIZE);
	}

};

typedef Mat2<int>	 Mat2i;
typedef Mat2<float>  Mat2f;
typedef Mat2<double> Mat2d;
