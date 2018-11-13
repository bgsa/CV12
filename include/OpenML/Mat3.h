#pragma once

#include "GlobalHeader.h"
#include <cassert>
#include <vector>
#include "MathPP.h"
#include "Mat.h"
#include "Vec3.h"
#include "Mat2.h"

#define MAT3_SIZE 9
#define MAT3_ROWSIZE 3

template <typename T>
struct AutovalueAutovector3 {
	T autovalue;
	Vec3<T> autovector;
};

template <typename T>
class Mat3 : public Mat<T>
{
private:
	T values[MAT3_SIZE];

public:

	/// <summary>
	/// Default constructor
	/// Load a empty matrix = 0
	/// </summary>
	API_INTERFACE Mat3()
	{
		static T emptyMatrix[MAT3_SIZE] = {
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f
		};

		memcpy(&values, emptyMatrix, sizeof(values));
	}

	/// <summary>
	/// Constructor with initialized values
	/// </summary>
	API_INTERFACE Mat3(T* values)
	{
		memcpy(&this->values, values, sizeof(this->values));
	}

	/// <summary>
	/// Constructor with initialized values - COL ORDER
	/// </summary>
	API_INTERFACE Mat3(T value11, T value21, T value31,
					   T value12, T value22, T value32,
					   T value13, T value23, T value33)
	{
		values[0] = value11;
		values[1] = value21;
		values[2] = value31;
		values[3] = value12;
		values[4] = value22;
		values[5] = value32;
		values[6] = value13;
		values[7] = value23;
		values[8] = value33;
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

		return values[y * MAT3_ROWSIZE + x];
	}

	/// <summary>
	/// Get the X axis
	/// COLUMN MAJOR ORDER
	/// </summary>
	API_INTERFACE Vec3<T> xAxis()
	{
		Vec3<T> result;

#if MAJOR_COLUMN_ORDER
			result = Vec3<T>{
				values[0],
				values[3],
				values[6]
			};
#else
			result = Vec3<T>{
				values[0],
				values[1],
				values[2]
			};
#endif

		return result;
	}

	/// <summary>
	/// Get the Y axis
	/// COLUMN MAJOR ORDER
	/// </summary>
	API_INTERFACE Vec3<T> yAxis()
	{
		Vec3<T> result;

#if MAJOR_COLUMN_ORDER
			result = Vec3<T>{
				values[1],
				values[4],
				values[7]
			};
#else
			result = Vec3<T>{
				values[3],
				values[4],
				values[5]
			};
#endif

		return result;
	}

	/// <summary>
	/// Get the Z axis
	/// COLUMN MAJOR ORDER
	/// </summary>
	API_INTERFACE Vec3<T> zAxis()
	{
		Vec3<T> result;

#if MAJOR_COLUMN_ORDER
			result = Vec3<T>{
				values[2],
				values[5],
				values[8]
			};
#else
			result = Vec3<T>{
				values[6],
				values[7],
				values[8]
			};
#endif

		return result;
	}

	/// <summary>
	/// Get the main / principal / major / primary diagonal from matrix
	/// </summary>
	API_INTERFACE Vec3<T> primaryDiagonal()
	{
		return Vec3<T> {
			values[0],
			values[4],
			values[8]
		};
	}

	/// <summary>
	/// Get the antidiagonal / counter / minor / secondary diagonal from matrix
	/// </summary>
	API_INTERFACE Vec3<T> secondaryDiagonal()
	{
		return Vec3<T> {
			values[2],
			values[4],
			values[6]
		};
	}

	/// <summary>
	/// Load a identity matrix
	/// </summary>
	API_INTERFACE static Mat3<T> identity()
	{
		static T identityMatrix[MAT3_SIZE] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		};

		Mat3 result;
		memcpy(&result, identityMatrix, sizeof(values));

		return result;
	}

	/// <summary>
	/// Transpose matrix - swap rows by columns
	/// </summary>
	API_INTERFACE Mat3<T> transpose()
	{
		Mat3<T> result;

		//copy principal diagonal
		result[0] = values[0];
		result[4] = values[4];
		result[8] = values[8];

		//swap others numbers
		float temp = values[1];
		result[1] = values[3];
		result[3] = temp;

		temp = values[2];
		result[2] = values[6];
		result[6] = temp;

		temp = values[5];
		result[5] = values[7];
		result[7] = temp;

		return result;
	}

	/// <summary>
	/// Multiply this matrix with the parametrized matrix => AxB
	/// </summary>
	API_INTERFACE Mat3<T> multiply(Mat3<T> matrixB)
	{
		Mat3<T> result;

#if MAJOR_COLUMN_ORDER
		for (int line = 0; line < MAT3_ROWSIZE; line++)
		{
			T ai0 = values[(0 * MAT3_ROWSIZE) + line];
			T ai1 = values[(1 * MAT3_ROWSIZE) + line];
			T ai2 = values[(2 * MAT3_ROWSIZE) + line];

			result[(0 * MAT3_ROWSIZE) + line] = ai0 * matrixB[(0 * MAT3_ROWSIZE) + 0] + ai1 * matrixB[(0 * MAT3_ROWSIZE) + 1] + ai2 * matrixB[(0 * MAT3_ROWSIZE) + 2];
			result[(1 * MAT3_ROWSIZE) + line] = ai0 * matrixB[(1 * MAT3_ROWSIZE) + 0] + ai1 * matrixB[(1 * MAT3_ROWSIZE) + 1] + ai2 * matrixB[(1 * MAT3_ROWSIZE) + 2];
			result[(2 * MAT3_ROWSIZE) + line] = ai0 * matrixB[(2 * MAT3_ROWSIZE) + 0] + ai1 * matrixB[(2 * MAT3_ROWSIZE) + 1] + ai2 * matrixB[(2 * MAT3_ROWSIZE) + 2];
		}
#else
		for (int column = 0; column < MAT3_ROWSIZE; column++)
		{
			T ai0 = values[(column * MAT3_ROWSIZE) + 0];
			T ai1 = values[(column * MAT3_ROWSIZE) + 1];
			T ai2 = values[(column * MAT3_ROWSIZE) + 2];

			result[(column * MAT3_ROWSIZE) + 0] = ai0 * matrixB[(0 * MAT3_ROWSIZE) + 0] + ai1 * matrixB[(1 * MAT3_ROWSIZE) + 0] + ai2 * matrixB[(2 * MAT3_ROWSIZE) + 0];
			result[(column * MAT3_ROWSIZE) + 1] = ai0 * matrixB[(0 * MAT3_ROWSIZE) + 1] + ai1 * matrixB[(1 * MAT3_ROWSIZE) + 1] + ai2 * matrixB[(2 * MAT3_ROWSIZE) + 1];
			result[(column * MAT3_ROWSIZE) + 2] = ai0 * matrixB[(0 * MAT3_ROWSIZE) + 2] + ai1 * matrixB[(1 * MAT3_ROWSIZE) + 2] + ai2 * matrixB[(2 * MAT3_ROWSIZE) + 2];
		}
#endif

		return result;
	}

	/// <summary>
	/// Multiply this matrix with the parametrized vector => AxB
	/// </summary>
	API_INTERFACE Vec3<T> multiply(Vec3<T> vector)
	{
		Vec3<T> result;

		result[0] = values[0 * MAT3_ROWSIZE + 0] * vector[0] + values[0 * MAT3_ROWSIZE + 1] * vector[1] + values[0 * MAT3_ROWSIZE + 2] * vector[2];
		result[1] = values[1 * MAT3_ROWSIZE + 0] * vector[0] + values[1 * MAT3_ROWSIZE + 1] * vector[1] + values[1 * MAT3_ROWSIZE + 2] * vector[2];
		result[2] = values[2 * MAT3_ROWSIZE + 0] * vector[0] + values[2 * MAT3_ROWSIZE + 1] * vector[1] + values[2 * MAT3_ROWSIZE + 2] * vector[2];

		return result;
	}
	
	/// <summary>
	/// Get the determinant from index i,j
	/// Zero-Index based
	/// </summary>
	API_INTERFACE T determinantIJ(int i, int j)
	{
		T* matrixValues = new T[4];
		size_t index = 0;

		for (size_t row = 0; row < MAT3_ROWSIZE; row++)
		{
			if (i == row)
				continue;

			for (size_t column = 0; column < MAT3_ROWSIZE; column++)
			{
				if (j == column)
					continue;

				matrixValues[index] = values[row * MAT3_ROWSIZE + column];
				index++;
			}
		}

		Mat2<T> matrix = Mat2<T>(matrixValues);
		T determinant = matrix.determinant();

		return determinant;
	}

	/// <summary>
	/// Get the cofactor of the index i,j
	/// Zero-Index based
	/// </summary>
	API_INTERFACE T cofactorIJ(int i, int j)
	{
		T determinantIJValue = determinantIJ(i, j);

		if (OpenML::isOdd(i + j))
			determinantIJValue *= -1;

		return determinantIJValue;
	}

	/// <summary>
	/// Create a scaled matrix
	/// </summary>
	API_INTERFACE static Mat3<T> createScale(T xScale, T yScale, T zScale)
	{
		Mat3<T> result = Mat3<T>::identity();

		result.scale(xScale, yScale, zScale);

		return result;
	}

	/// <summary>
	/// Scale the current matrix
	/// </summary>
	API_INTERFACE void scale(T xScale, T yScale, T zScale)
	{
		values[0] *= xScale;
		values[4] *= yScale;
		values[8] *= zScale;
	}

	/// <summary>
	/// Create a rotation matrix
	/// Example: x = 1.0 to rotate over X axis; x = 0.0 to not rotate over X axis
	/// </summary>
	API_INTERFACE static Mat3<T> createRotate(T angleRadians, T x, T y, T z)
	{
		float mag, sine, cosine;
		float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

		sine = float(sin(angleRadians));
		cosine = float(cos(angleRadians));

		mag = float(sqrt(x*x + y*y + z*z));

		if (mag == 0.0f)
			return Mat3::identity();

		// Rotation matrix is normalized
		x /= mag;
		y /= mag;
		z /= mag;

		xx = x * x;
		yy = y * y;
		zz = z * z;
		xy = x * y;
		yz = y * z;
		zx = z * x;
		xs = x * sine;
		ys = y * sine;
		zs = z * sine;
		one_c = 1.0f - cosine;

		Mat3<T> result;

		result[0 * MAT3_ROWSIZE + 0] = (one_c * xx) + cosine;
		result[1 * MAT3_ROWSIZE + 0] = (one_c * xy) - zs;
		result[2 * MAT3_ROWSIZE + 0] = (one_c * zx) + ys;

		result[0 * MAT3_ROWSIZE + 1] = (one_c * xy) + zs;
		result[1 * MAT3_ROWSIZE + 1] = (one_c * yy) + cosine;
		result[2 * MAT3_ROWSIZE + 1] = (one_c * yz) - xs;

		result[0 * MAT3_ROWSIZE + 2] = (one_c * zx) - ys;
		result[1 * MAT3_ROWSIZE + 2] = (one_c * yz) + xs;
		result[2 * MAT3_ROWSIZE + 2] = (one_c * zz) + cosine;

		return result;
	}
	
	/// <summary>
	/// Craete a translation matrix
	/// </summary>
	API_INTERFACE static Mat3<T> createTranslate(T x, T y, T z)
	{
		Mat3<T> result = Mat3<T>::identity();

#if MAJOR_COLUMN_ORDER
		result[6] = x;
		result[7] = y;
		result[8] = z;
#else
		result[2] = x;
		result[5] = y;
		result[8] = z;
#endif

		return result;
	}

	/// <summary>
	/// Get the determinant of the matrix
	/// </summary>
	API_INTERFACE T determinant()
	{
		return
			(	  values[0] * values[4] * values[8]
				+ values[1] * values[5] * values[6]
				+ values[2] * values[3] * values[7]
			)
			-
			(  	  values[2] * values[4] * values[6]
				+ values[0] * values[5] * values[7]
				+ values[1] * values[3] * values[8]
			);
	}

	/// <summary>
	/// Get the size in Bytes of Mat3
	/// </summary>
	API_INTERFACE size_t sizeInBytes()
	{
		return MAT3_SIZE * sizeof(T);
	}

	/// <summary>
	/// Clone this matrix
	/// </summary>
	API_INTERFACE Mat3<T> clone()
	{
		Mat3<T> result;

		memcpy(&result, this, sizeof(Mat3<T>));

		return result;
	}

	/// <summary>
	/// Get a index from the vector
	/// </summary>
	API_INTERFACE T& operator[](int index)
	{
		assert(index >= 0 && index < MAT3_SIZE);

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
	API_INTERFACE Mat3<T> operator*(Mat3<T> matrix)
	{
		return multiply(matrix);
	}

	/// <summary>
	/// Multiply the matrix to 3D vector
	/// </summary>
	API_INTERFACE Vec3<T> operator*(Vec3<T> matrix)
	{
		return multiply(matrix);
	}

	/// <summary>
	/// Multiply the matrix to another one
	/// </summary>
	API_INTERFACE void operator*=(Mat3<T> matrix)
	{
		memcpy(&this->values, multiply(matrix).values, sizeof(this->values));
	}

	/// <summary>
	/// Get the matrix content as string
	/// </summary>
	API_INTERFACE string toString()
	{
		return Mat<T>::toString(values, MAT3_SIZE);
	}

	/// <summary>
	/// Decompose the matrix to Lower and Upper matrix
	/// </summary>
	API_INTERFACE Mat3<T>* decomposeLU()
	{
		Mat3<T> lowerMatrix = Mat3<T>::identity();
		Mat3<T> upperMatrix = Mat3<T>(values);
		Mat3<T>* result = new Mat3<T>[2];

		vector<Mat3<T>> elementarInverseMatrixes;
		Mat3<T> elementarInverseMatrix;

		size_t rowSize = MAT3_ROWSIZE;
		size_t colSize = MAT3_ROWSIZE;

#if MAJOR_COLUMN_ORDER
		size_t pivotRowIndex = 0;

		for (size_t column = 0; column < colSize; column++)
		{
			float pivot = upperMatrix[pivotRowIndex * rowSize + column];
			float pivotOperator = 1 / pivot;

			for (size_t row = 0; row < rowSize; row++)
				upperMatrix[row * rowSize + column] *= pivotOperator;

			elementarInverseMatrix = Mat3<T>::identity();
			elementarInverseMatrix[pivotRowIndex * rowSize + column] = pivot;
			elementarInverseMatrixes.push_back(elementarInverseMatrix);

			for (size_t lowerColumns = column + 1; lowerColumns < rowSize; lowerColumns++)
			{
				pivot = upperMatrix[pivotRowIndex * rowSize + lowerColumns];
				pivotOperator = -pivot;

				for (size_t row = 0; row < rowSize; row++)
					upperMatrix[row * rowSize + lowerColumns] += pivotOperator * upperMatrix[row * rowSize + column];

				elementarInverseMatrix = Mat3<T>::identity();
				elementarInverseMatrix[pivotRowIndex * rowSize + lowerColumns] = pivot;
				elementarInverseMatrixes.push_back(elementarInverseMatrix);
			}

			pivotRowIndex++;
		}

		for (size_t i = 0; i < elementarInverseMatrixes.size(); i++)
			lowerMatrix *= elementarInverseMatrixes[i];
#else
		size_t pivotColumnIndex = 0;

		for (size_t line = 0; line < rowSize; line++)
		{
			float pivot = upperMatrix[line * rowSize + pivotColumnIndex];
			float pivotOperator = 1 / pivot;

			for (size_t column = 0; column < colSize; column++)
				upperMatrix[line * rowSize + column] *= pivotOperator;

			elementarInverseMatrix = Mat3<T>::identity();
			elementarInverseMatrix[line * rowSize + pivotColumnIndex] = pivot;
			elementarInverseMatrixes.push_back(elementarInverseMatrix);

			for (size_t lowerLines = line + 1; lowerLines < rowSize; lowerLines++)
			{
				pivot = upperMatrix[lowerLines * rowSize + pivotColumnIndex];
				pivotOperator = -pivot;

				for (size_t column = 0; column < colSize; column++)
					upperMatrix[lowerLines * rowSize + column] += pivotOperator * upperMatrix[line * rowSize + column];

				elementarInverseMatrix = Mat3<T>::identity();
				elementarInverseMatrix[lowerLines * rowSize + pivotColumnIndex] = pivot;
				elementarInverseMatrixes.push_back(elementarInverseMatrix);
			}

			pivotColumnIndex++;
		}

		for (size_t i = 0; i < elementarInverseMatrixes.size(); i++)
			lowerMatrix *= elementarInverseMatrixes[i];
#endif

		result[0] = lowerMatrix;
		result[1] = upperMatrix;
		
		return result;
	}
	
	/// <summary>
	/// Decompose the matrix to Lower, Diagonal Matrix and Upper matrix
	/// </summary>
	API_INTERFACE Mat3<T>* decomposeLDU()
	{
		Mat3<T> diagonalMatrix = Mat3<T>::identity();
		Mat3<T>* result = new Mat3<T>[3];

		Mat3<T>* lowerAndUpperMatrixes = decomposeLU();

		Mat3<T> upperMatrix = lowerAndUpperMatrixes[1];
		unsigned short diagonalIndex = 0;

#if MAJOR_COLUMN_ORDER
		for (size_t column = 0; column < MAT3_ROWSIZE; column++)
		{
			T pivot = upperMatrix[diagonalIndex * MAT3_ROWSIZE + column];

			diagonalMatrix[column * MAT3_ROWSIZE + diagonalIndex] = pivot;

			for (size_t row = column; row < MAT3_ROWSIZE; row++)
				upperMatrix[column * MAT3_ROWSIZE + row] /= pivot;

			diagonalIndex++;
		}
#else
		for (size_t row = 0; row < MAT3_ROWSIZE; row++)
		{
			T pivot = upperMatrix[row * MAT3_ROWSIZE + diagonalIndex];

			diagonalMatrix[row * MAT3_ROWSIZE + diagonalIndex] = pivot;

			for (size_t column = row; column < MAT3_ROWSIZE; column++)
				upperMatrix[row * MAT3_ROWSIZE + column] /= pivot;

			diagonalIndex++;
		}
#endif

		result[0] = lowerAndUpperMatrixes[0];
		result[1] = diagonalMatrix;
		result[2] = upperMatrix;

		delete[] lowerAndUpperMatrixes;

		return result;
	}
	
	/// <summary>
	/// Get the autovalue of the matrix
	/// </summary>
	API_INTERFACE AutovalueAutovector3<T> getAutovalueAndAutovector(const unsigned short maxIteration = 5)
	{
		Mat3<T> matrix = *this;
		Vec3<T> autovector = { T(1), T(1), T(1) };		
		T autovalue;

		for (unsigned short iterationIndex = 0; iterationIndex < maxIteration; iterationIndex++)
		{			
			Vec3<T> ax = matrix * autovector;
			autovalue = ax.maximum();
			autovector = ax / autovalue;
		}

		return AutovalueAutovector3<T>{ autovalue, autovector };
	}


	/// <summary>
	/// Get the inverse matrix from current matrix => A^-1
	/// <summary>
	API_INTERFACE Mat3<T> invert()
	{
		Mat3<T> matrixInverse;
		float detij;

		float det = determinant();

		for (int i = 0; i < MAT3_ROWSIZE; i++)
			for (int j = 0; j < MAT3_ROWSIZE; j++)
			{
				detij = determinantIJ(j, i);

				if ((i + j) & 0x1)
					matrixInverse[i * MAT3_ROWSIZE + j] = -detij * det;
				else
					matrixInverse[i * MAT3_ROWSIZE + j] = detij * det;
			}

		return matrixInverse;
	}

};

typedef Mat3<int> Mat3i;
typedef Mat3<float> Mat3f;
typedef Mat3<double> Mat3d;
