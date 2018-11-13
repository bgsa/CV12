#pragma once

#include "GlobalHeader.h"
#include <cassert>
#include "MathPP.h"
#include "Vec4.h"
#include "Mat.h"
#include "Mat3.h"

#define MAT4_SIZE 16
#define MAT4_ROWSIZE 4

template <typename T>
struct AutovalueAutovector4 {
	T autovalue;
	Vec4<T> autovector;
};

template <typename T>
class Mat4 : public Mat<T>
{
private:
	T values[MAT4_SIZE];

public:

	/// <summary>
	/// Default constructor
	/// Load a empty matrix = 0
	/// </summary>
	API_INTERFACE Mat4()
	{
		static T emptyMatrix[MAT4_SIZE] = {
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f
		};

		memcpy(&values, emptyMatrix, sizeof(values));
	}

	/// <summary>
	/// Constructor with initialized values
	/// </summary>
	API_INTERFACE Mat4(T* values)
	{
		memcpy(&this->values, values, sizeof(this->values));
	}

	/// <summary>
	/// Constructor with initialized values - COL ORDER
	/// </summary>
	API_INTERFACE Mat4(T value11, T value21, T value31, T value41,
					   T value12, T value22, T value32, T value42,
					   T value13, T value23, T value33, T value43,
					   T value14, T value24, T value34, T value44)
	{
		values[0] = value11;
		values[1] = value21;
		values[2] = value31;
		values[3] = value41;

		values[4] = value12;
		values[5] = value22;
		values[6] = value32;
		values[7] = value42;

		values[8] = value13;
		values[9] = value23;
		values[10] = value33;
		values[11] = value43;

		values[12] = value14;
		values[13] = value24;
		values[14] = value34;
		values[15] = value44;
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

		return values[y * MAT4_ROWSIZE + x];
	}

	/// <summary>
	/// Get the X axis
	/// COLUMN MAJOR ORDER
	/// </summary>
	API_INTERFACE Vec4<T> xAxis()
	{
#if MAJOR_COLUMN_ORDER
		return Vec4<T> {
			values[0 * MAT4_ROWSIZE + 0],
			values[1 * MAT4_ROWSIZE + 0],
			values[2 * MAT4_ROWSIZE + 0],
			values[3 * MAT4_ROWSIZE + 0]
		};
#else
		return Vec4<T> {
			values[0 * MAT4_ROWSIZE + 0],
			values[0 * MAT4_ROWSIZE + 1],
			values[0 * MAT4_ROWSIZE + 2],
			values[0 * MAT4_ROWSIZE + 3]
		};
#endif
	}

	/// <summary>
	/// Get the Y axis
	/// COLUMN MAJOR ORDER
	/// <summary>
	API_INTERFACE Vec4<T> yAxis()
	{
#if MAJOR_COLUMN_ORDER
		return Vec4<T> {
			values[0 * MAT4_ROWSIZE + 1],
			values[1 * MAT4_ROWSIZE + 1],
			values[2 * MAT4_ROWSIZE + 1],
			values[3 * MAT4_ROWSIZE + 1]
		};
#else
		return Vec4<T> {
			values[1 * MAT4_ROWSIZE + 0],
			values[1 * MAT4_ROWSIZE + 1],
			values[1 * MAT4_ROWSIZE + 2],
			values[1 * MAT4_ROWSIZE + 3]
		};
#endif
	}

	/// <summary>
	/// Get the Z axis
	/// COLUMN MAJOR ORDER
	/// </summary>
	API_INTERFACE Vec4<T> zAxis()
	{
#if MAJOR_COLUMN_ORDER
		return Vec4<T> {
			values[0 * MAT4_ROWSIZE + 2],
			values[1 * MAT4_ROWSIZE + 2],
			values[2 * MAT4_ROWSIZE + 2],
			values[3 * MAT4_ROWSIZE + 2]
		};
#else
		return Vec4<T> {
			values[2 * MAT4_ROWSIZE + 0],
			values[2 * MAT4_ROWSIZE + 1],
			values[2 * MAT4_ROWSIZE + 2],
			values[2 * MAT4_ROWSIZE + 3]
		};
#endif
	}

	/// <summary>
	/// Get the Z axis
	/// COLUMN MAJOR ORDER
	/// </summary>
	API_INTERFACE Vec4<T> wAxis()
	{
#if MAJOR_COLUMN_ORDER
		return Vec4<T> {
			values[0 * MAT4_ROWSIZE + 3],
			values[1 * MAT4_ROWSIZE + 3],
			values[2 * MAT4_ROWSIZE + 3],
			values[3 * MAT4_ROWSIZE + 3]
		};
#else
		return Vec4<T> {
			values[3 * MAT4_ROWSIZE + 0],
			values[3 * MAT4_ROWSIZE + 1],
			values[3 * MAT4_ROWSIZE + 2],
			values[3 * MAT4_ROWSIZE + 3]
		};
#endif
	}

	/// <summary>
	/// Get the main / principal / major / primary diagonal from matrix
	/// </summary>
	API_INTERFACE Vec4<T> primaryDiagonal()
	{
		return Vec4<T> {
			values[0],
				values[5],
				values[10],
				values[15]
		};
	}

	/// <summary>
	/// Get the antidiagonal / counter / minor / secondary diagonal from matrix
	/// </summary>
	API_INTERFACE Vec4<T> secondaryDiagonal()
	{
		return Vec4<T> {
			values[3],
				values[6],
				values[9],
				values[12]
		};
	}

	/// <summary>
	/// Load a identity matrix
	/// </summary>
	API_INTERFACE static Mat4<T> identity()
	{
		static T identityMatrix[MAT4_SIZE] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		Mat4 result;
		memcpy(&result, identityMatrix, sizeof(values));

		return result;
	}

	/// <summary>
	/// Transpose matrix - swap rows by columns
	/// </summary>
	API_INTERFACE Mat4<T> transpose()
	{
		Mat4<T> result;

		//copy principal diagonal
		result[0] = values[0];
		result[5] = values[5];
		result[10] = values[10];
		result[15] = values[15];

		//swap others numbers
		float temp = values[1];
		result[1] = values[4];
		result[4] = temp;

		temp = values[2];
		result[2] = values[8];
		result[8] = temp;

		temp = values[3];
		result[3] = values[12];
		result[12] = temp;

		temp = values[6];
		result[6] = values[9];
		result[9] = temp;

		temp = values[7];
		result[7] = values[13];
		result[13] = temp;

		temp = values[11];
		result[11] = values[14];
		result[14] = temp;

		return result;
	}

	/// <summary>
	/// Get the determinant from index i,j
	/// Zero-Index based
	/// </summary>
	API_INTERFACE T determinantIJ(int i, int j)
	{
		int x, y, ii, jj;
		T ret, mat[3][3];

		x = 0;
		for (ii = 0; ii < 4; ii++)
		{
			if (ii == i)
				continue;

			y = 0;

			for (jj = 0; jj < 4; jj++)
			{
				if (jj == j)
					continue;

				mat[x][y] = values[(ii * 4) + jj];
				y++;
			}

			x++;
		}

		ret = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]);
		ret -= mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]);
		ret += mat[0][2] * (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]);

		return ret;
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
	/// Get the determinant from matrix
	/// </summary>
	API_INTERFACE T determinant()
	{
		T det = T(0);
		
		for (int i = 0; i < MAT4_ROWSIZE; i++)
		{
			det += (i & 0x1) ? (-values[i] * determinantIJ(0, i)) : (values[i] * determinantIJ(0, i));
		}

		return det;
	}

	/// <summary>
	/// Multiply this matrix with the parametrized matrix => AxB
	/// <summary>
	API_INTERFACE Mat4<T> multiply(Mat4<T> matrixB)
	{
		Mat4<T> result;

#if MAJOR_COLUMN_ORDER
		for (int line = 0; line < MAT4_ROWSIZE; line++)
		{
			T ai0 = values[(0 * MAT4_ROWSIZE) + line];
			T ai1 = values[(1 * MAT4_ROWSIZE) + line];
			T ai2 = values[(2 * MAT4_ROWSIZE) + line];
			T ai3 = values[(3 * MAT4_ROWSIZE) + line];

			result[(0 * MAT4_ROWSIZE) + line] = ai0 * matrixB[(0 * MAT4_ROWSIZE) + 0] + ai1 * matrixB[(0 * MAT4_ROWSIZE) + 1] + ai2 * matrixB[(0 * MAT4_ROWSIZE) + 2] + ai3 * matrixB[(0 * MAT4_ROWSIZE) + 3];
			result[(1 * MAT4_ROWSIZE) + line] = ai0 * matrixB[(1 * MAT4_ROWSIZE) + 0] + ai1 * matrixB[(1 * MAT4_ROWSIZE) + 1] + ai2 * matrixB[(1 * MAT4_ROWSIZE) + 2] + ai3 * matrixB[(1 * MAT4_ROWSIZE) + 3];
			result[(2 * MAT4_ROWSIZE) + line] = ai0 * matrixB[(2 * MAT4_ROWSIZE) + 0] + ai1 * matrixB[(2 * MAT4_ROWSIZE) + 1] + ai2 * matrixB[(2 * MAT4_ROWSIZE) + 2] + ai3 * matrixB[(2 * MAT4_ROWSIZE) + 3];
			result[(3 * MAT4_ROWSIZE) + line] = ai0 * matrixB[(3 * MAT4_ROWSIZE) + 0] + ai1 * matrixB[(3 * MAT4_ROWSIZE) + 1] + ai2 * matrixB[(3 * MAT4_ROWSIZE) + 2] + ai3 * matrixB[(3 * MAT4_ROWSIZE) + 3];
		}
#else 
		for (int column = 0; column < MAT4_ROWSIZE; column++) 
		{
			T ai0 = values[(column * MAT4_ROWSIZE) + 0];
			T ai1 = values[(column * MAT4_ROWSIZE) + 1];
			T ai2 = values[(column * MAT4_ROWSIZE) + 2];
			T ai3 = values[(column * MAT4_ROWSIZE) + 3];

			result[(column * MAT4_ROWSIZE) + 0] = ai0 * matrixB[(0 * MAT4_ROWSIZE) + 0] + ai1 * matrixB[(1 * MAT4_ROWSIZE) + 0] + ai2 * matrixB[(2 * MAT4_ROWSIZE) + 0] + ai3 * matrixB[(3 * MAT4_ROWSIZE) + 0];
			result[(column * MAT4_ROWSIZE) + 1] = ai0 * matrixB[(0 * MAT4_ROWSIZE) + 1] + ai1 * matrixB[(1 * MAT4_ROWSIZE) + 1] + ai2 * matrixB[(2 * MAT4_ROWSIZE) + 1] + ai3 * matrixB[(3 * MAT4_ROWSIZE) + 1];
			result[(column * MAT4_ROWSIZE) + 2] = ai0 * matrixB[(0 * MAT4_ROWSIZE) + 2] + ai1 * matrixB[(1 * MAT4_ROWSIZE) + 2] + ai2 * matrixB[(2 * MAT4_ROWSIZE) + 2] + ai3 * matrixB[(3 * MAT4_ROWSIZE) + 2];
			result[(column * MAT4_ROWSIZE) + 3] = ai0 * matrixB[(0 * MAT4_ROWSIZE) + 3] + ai1 * matrixB[(1 * MAT4_ROWSIZE) + 3] + ai2 * matrixB[(2 * MAT4_ROWSIZE) + 3] + ai3 * matrixB[(3 * MAT4_ROWSIZE) + 3];
		}
#endif

		return result;
	}

	/// <summary>
	/// Multiply this matrix with the parametrized vector => AxB
	/// </summary>
	API_INTERFACE Vec4<T> multiply(Vec4<T> vector)
	{
		Vec4<T> result;

#if MAJOR_COLUMN_ORDER
		for (int line = 0; line < MAT4_ROWSIZE; line++)
		{
			T ai0 = values[(0 * MAT4_ROWSIZE) + line];
			T ai1 = values[(1 * MAT4_ROWSIZE) + line];
			T ai2 = values[(2 * MAT4_ROWSIZE) + line];
			T ai3 = values[(3 * MAT4_ROWSIZE) + line];

			result[0] = ai0 * vector[0] + ai1 * vector[0] + ai2 * vector[0] + ai3 * vector[0];
			result[1] = ai0 * vector[1] + ai1 * vector[1] + ai2 * vector[1] + ai3 * vector[1];
			result[2] = ai0 * vector[2] + ai1 * vector[2] + ai2 * vector[2] + ai3 * vector[2];
			result[3] = ai0 * vector[3] + ai1 * vector[3] + ai2 * vector[3] + ai3 * vector[3];
		}
#endif
		return result;
	}

	/// <summary>
	/// Get the inverse matrix from current matrix => A^-1
	/// <summary>
	API_INTERFACE Mat4<T> invert()
	{
		Mat4<T> mInverse;

		int i, j;
		float det, detij;

		// calculate 4x4 determinant
		det = 0.0f;
		for (i = 0; i < 4; i++)
		{
			det += (i & 0x1) ? (-values[i] * determinantIJ(0, i)) : (values[i] * determinantIJ(0, i));
		}
		det = 1.0f / det;

		// calculate inverse
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				detij = determinantIJ(j, i);
				mInverse[(i * 4) + j] = ((i + j) & 0x1) ? (-detij * det) : (detij *det);
			}
		}

		return mInverse;
	}

	/// <summary>
	/// Create a scaled matrix
	/// </summary>
	API_INTERFACE static Mat4<T> createScale(T xScale, T yScale, T zScale)
	{
		Mat4<T> result = Mat4<T>::identity();

		result.scale(xScale, yScale, zScale);

		return result;
	}

	/// <summary>
	/// Scale the current matrix
	/// </summary>
	API_INTERFACE void scale(T xScale, T yScale, T zScale)
	{
		values[0] *= xScale;
		values[5] *= yScale;
		values[10] *= zScale;
	}

	/// <summary>
	/// Create a rotation matrix
	/// Example: x = 1.0 to rotate over X axis; x = 0.0 to not rotate over X axis
	/// </summary>
	API_INTERFACE static Mat4<T> createRotate(T angleRadians, T x, T y, T z)
	{
		float mag, sineAngle, cosineAngle;
		float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

		sineAngle = float(sin(angleRadians));
		cosineAngle = float(cos(angleRadians));

		mag = float(sqrt(x*x + y*y + z*z));

		if (mag == 0.0f)
			return Mat4::identity();

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
		xs = x * sineAngle;
		ys = y * sineAngle;
		zs = z * sineAngle;
		one_c = 1.0f - cosineAngle;

		Mat4<T> result;

#define M(row,col)  result[col * MAT4_ROWSIZE + row]
		M(0, 0) = (one_c * xx) + cosineAngle;
		M(0, 1) = (one_c * xy) - zs;
		M(0, 2) = (one_c * zx) + ys;
		M(0, 3) = 0.0f;

		M(1, 0) = (one_c * xy) + zs;
		M(1, 1) = (one_c * yy) + cosineAngle;
		M(1, 2) = (one_c * yz) - xs;
		M(1, 3) = 0.0f;

		M(2, 0) = (one_c * zx) - ys;
		M(2, 1) = (one_c * yz) + xs;
		M(2, 2) = (one_c * zz) + cosineAngle;
		M(2, 3) = 0.0f;

		M(3, 0) = 0.0f;
		M(3, 1) = 0.0f;
		M(3, 2) = 0.0f;
		M(3, 3) = 1.0f;
#undef M
		
		return result;
	}

	/// <summary>
	/// Craete a translation matrix
	/// </summary>
	API_INTERFACE static Mat4<T> createTranslate(T x, T y, T z)
	{
		Mat4<T> result = Mat4<T>::identity();

#if MAJOR_COLUMN_ORDER
		result[12] = x;
		result[13] = y;
		result[14] = z;
#else
		result[3] = x;
		result[7] = y;
		result[11] = z;
#endif

		return result;
	}

	/// <summary>
	/// Craete a orthographic matrix projection
	/// </summary>
	API_INTERFACE static Mat4<T> createOrthographicMatrix(T xMin, T xMax, T yMin, T yMax, T zMin, T zMax)
	{
		Mat4<T> projectionMatrix = Mat4<T>::identity();

		projectionMatrix[0] = 2.0f / (xMax - xMin);
		projectionMatrix[5] = 2.0f / (yMax - yMin);
		projectionMatrix[10] = -2.0f / (zMax - zMin);
		projectionMatrix[12] = -((xMax + xMin) / (xMax - xMin));
		projectionMatrix[13] = -((yMax + yMin) / (yMax - yMin));
		projectionMatrix[14] = -((zMax + zMin) / (zMax - zMin));
		projectionMatrix[15] = 1.0f;

		return projectionMatrix;
	}

	/// <summary>
	/// Get the size in Bytes of Mat4
	/// </summary>
	API_INTERFACE size_t sizeInBytes()
	{
		return MAT4_SIZE * sizeof(T);
	}

	/// <summary>
	/// Clone this matrix
	/// </summary>
	API_INTERFACE Mat4<T> clone()
	{
		Mat4<T> result;

		memcpy(&result, this, sizeof(Mat4<T>));

		return result;
	}
	
	/// <summary>
	/// Multiply the vector to a scalar
	/// </summary>
	API_INTERFACE Mat4<T> operator*(T value)
	{
		Mat4<T> result;
		
		for (size_t i = 0; i < MAT4_SIZE; i++)
			result[i] = values[i] * value;

		return result;
	}

	/// <summary>
	/// Multiply the matrix to another one
	/// </summary>
	API_INTERFACE void operator*=(Mat4<T> matrix)
	{
		memcpy(&this->values, multiply(matrix).values, sizeof(this->values));
	}

	/// <summary>
	/// Multiply the matrix to another one
	/// </summary>
	API_INTERFACE Mat4<T> operator*(Mat4<T> matrix)
	{
		return multiply(matrix);
	}

	/// <summary>
	/// Sum this matrix to another one
	/// </summary>
	API_INTERFACE Mat4<T> operator+(Mat4<T> matrix)
	{
		Mat4<T> result;

		for (size_t i = 0; i < MAT4_SIZE; i++)
			result[i] = values[i] + matrix[i];

		return result;
	}

	/// <summary>
	/// Sum a scalar to this matrix
	/// </summary>
	API_INTERFACE Mat4<T> operator+(T value)
	{
		Mat4<T> result;

		for (size_t i = 0; i < MAT4_SIZE; i++)
			result[i] = values[i] + value;

		return result;
	}

	/// <summary>
	/// Subtract this matrix to another one
	/// </summary>
	API_INTERFACE Mat4<T> operator-(Mat4<T> matrix)
	{
		Mat4<T> result;

		for (size_t i = 0; i < MAT4_SIZE; i++)
			result[i] = values[i] - matrix[i];

		return result;
	}

	/// <summary>
	/// Subtract a scalar from this matrix
	/// </summary>
	API_INTERFACE Mat4<T> operator-(T value)
	{
		Mat4<T> result;

		for (size_t i = 0; i < MAT4_SIZE; i++)
			result[i] = values[i] - value;

		return result;
	}

	/// <summary>
	/// Compare this vector to another one. Compare each component.
	/// </summary>
	API_INTERFACE bool operator==(Mat4<T> matrix)
	{
		for (size_t i = 0; i < MAT4_SIZE; i++)
			if (values[i] != matrix[i])
				return false;

		return true;
	}

	/// <summary>
	/// Compare this matrix to another one. Compare each component.
	/// </summary>
	API_INTERFACE bool operator==(T value)
	{
		for (size_t i = 0; i < MAT4_SIZE; i++)
			if (values[i] != value)
				return false;

		return true;
	}

	/// <summary>
	/// Compare this vector to another one. Compare each component.
	/// </summary>
	API_INTERFACE bool operator!=(Mat4<T> matrix)
	{
		for (size_t i = 0; i < MAT4_SIZE; i++)
			if (values[i] != matrix[i])
				return true;

		return false;
	}

	/// <summary>
	/// Get a index from the vector
	/// </summary>
	API_INTERFACE T& operator[](int index)
	{
		assert(index >= 0 && index < MAT4_SIZE);

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
	/// Convert the matrix to Matrix 3x3
	/// Returns the first 3 components of x-Axis, y-Axis, z-Axis
	/// </summary>
	API_INTERFACE Mat3<T> toMat3()
	{
		return Mat3<T> {
			values[0], values[1], values[2],
			values[4], values[5], values[6],
			values[8], values[9], values[10]
		};
	}

	/// <summary>
	/// Get the matrix content as string
	/// </summary>
	API_INTERFACE string toString()
	{
		return Mat<T>::toString(values, MAT4_SIZE);
	}

	/// <summary>
	/// Decompose the matrix to Lower and Upper matrix
	/// </summary>
	API_INTERFACE Mat4<T>* decomposeLU()
	{
		Mat4<T> lowerMatrix = Mat4<T>::identity();
		Mat4<T> upperMatrix = Mat4<T>(values);
		Mat4<T>* result = new Mat4<T>[2];

		vector<Mat4<T>> elementarInverseMatrixes;
		Mat4<T> elementarInverseMatrix;

		size_t rowSize = MAT4_ROWSIZE;
		size_t colSize = MAT4_ROWSIZE;

#if MAJOR_COLUMN_ORDER
		size_t pivotRowIndex = 0;

		for (size_t column = 0; column < colSize; column++)
		{
			float pivot = upperMatrix[pivotRowIndex * rowSize + column];
			float pivotOperator = 1 / pivot;

			for (size_t row = 0; row < rowSize; row++)
				upperMatrix[row * rowSize + column] *= pivotOperator;

			elementarInverseMatrix = Mat4<T>::identity();
			elementarInverseMatrix[pivotRowIndex * rowSize + column] = pivot;
			elementarInverseMatrixes.push_back(elementarInverseMatrix);

			for (size_t lowerColumns = column + 1; lowerColumns < rowSize; lowerColumns++)
			{
				pivot = upperMatrix[pivotRowIndex * rowSize + lowerColumns];
				pivotOperator = -pivot;

				for (size_t row = 0; row < rowSize; row++)
					upperMatrix[row * rowSize + lowerColumns] += pivotOperator * upperMatrix[row * rowSize + column];

				elementarInverseMatrix = Mat4<T>::identity();
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

			elementarInverseMatrix = Mat4<T>::identity();
			elementarInverseMatrix[line * rowSize + pivotColumnIndex] = pivot;
			elementarInverseMatrixes.push_back(elementarInverseMatrix);

			for (size_t lowerLines = line + 1; lowerLines < rowSize; lowerLines++)
			{
				pivot = upperMatrix[lowerLines * rowSize + pivotColumnIndex];
				pivotOperator = -pivot;

				for (size_t column = 0; column < colSize; column++)
					upperMatrix[lowerLines * rowSize + column] += pivotOperator * upperMatrix[line * rowSize + column];

				elementarInverseMatrix = Mat4<T>::identity();
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
	API_INTERFACE Mat4<T>* decomposeLDU()
	{
		Mat4<T> diagonalMatrix = Mat4<T>::identity();
		Mat4<T>* result = new Mat4<T>[3];

		Mat4<T>* lowerAndUpperMatrixes = decomposeLU();

		Mat4<T> upperMatrix = lowerAndUpperMatrixes[1];
		unsigned short diagonalIndex = 0;

#if MAJOR_COLUMN_ORDER
		for (size_t column = 0; column < MAT4_ROWSIZE; column++)
		{
			T pivot = upperMatrix[diagonalIndex * MAT4_ROWSIZE + column];

			diagonalMatrix[column * MAT4_ROWSIZE + diagonalIndex] = pivot;

			for (size_t row = column; row < MAT4_ROWSIZE; row++)
				upperMatrix[column * MAT4_ROWSIZE + row] /= pivot;

			diagonalIndex++;
		}
#else
		for (size_t row = 0; row < MAT4_ROWSIZE; row++)
		{
			T pivot = upperMatrix[row * MAT4_ROWSIZE + diagonalIndex];

			diagonalMatrix[row * MAT4_ROWSIZE + diagonalIndex] = pivot;

			for (size_t column = row; column < MAT4_ROWSIZE; column++)
				upperMatrix[row * MAT4_ROWSIZE + column] /= pivot;

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
	API_INTERFACE AutovalueAutovector4<T> getAutovalueAndAutovector(const unsigned short maxIteration = 5)
	{
		Mat4<T> matrix = *this;
		Vec4<T> autovector = { T(1), T(1), T(1), T(1) };
		T autovalue;

		for (unsigned short iterationIndex = 0; iterationIndex < maxIteration; iterationIndex++)
		{
			Vec4<T> ax = matrix * autovector;
			autovalue = ax.maximum();
			autovector = ax / autovalue;
		}

		return AutovalueAutovector4<T>{ autovalue, autovector };
	}
};

typedef Mat4<int> Mat4i;
typedef Mat4<float> Mat4f;
typedef Mat4<double> Mat4d;

