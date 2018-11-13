#pragma once

#include "GlobalHeader.h"
#include <cstring>
#include <sstream>


namespace OpenML 
{
	
#define PI (3.14159265358979323846)
#define TWO_PI (6.28318530717958647692)
#define HALF_PI (1.57079632679489661923)
#define PI_DIV_180 (0.017453292519943296)
#define INV_PI_DIV_180 (57.2957795130823229)

#define degreesToRadians(x)	((x) * PI_DIV_180)
#define radiansToDegrees(x)	((x) * INV_PI_DIV_180)

#define hourToDegrees(x) ( x * (1.0 / 15.0) )
#define hourToRadians(x)	degreesToRadians(hourToDegrees(x))

#define degreesToHout(x)	((x) * 15.0))
#define radiansToHour(x)	degreesToHout(radiansToDegrees(x))

#ifdef UNIT_TEST
	template <typename T>
	API_INTERFACE T round(T value, int decimals)
	{
		double arredondado = value * pow(10, decimals);

		ostringstream os;
		os << arredondado;

		string number = os.str();
		size_t dotIndex = number.find(".");

		number = number.substr(dotIndex + 1, 1);

		int decimalDigit;
		istringstream(number) >> decimalDigit;

		if (decimalDigit >= 5)
			arredondado = ceil(arredondado);
		else
			arredondado = floor(arredondado);

		arredondado /= (pow(10, decimals));

		return T(arredondado);
	}
#endif

	API_INTERFACE
	inline bool isEven(int value)
	{
		return (value % 2) == 0;
	}

	API_INTERFACE
	inline bool isOdd(int value)
	{
		return ! isEven(value);
	}

	API_INTERFACE
	inline unsigned int isPow2(unsigned int value)
	{
		unsigned int nPow2 = 1;

		while (value > nPow2)
			nPow2 = (nPow2 << 1);

		return nPow2;
	}

	API_INTERFACE
	inline unsigned int nextPowOf2(int value)
	{
		int rval = 1;

		while (rval < value) 
			rval *= 2;

		return rval;
	}

/*

	///////////////////////////////////////////////////////////////////////////////
	// Extract a rotation matrix from a 4x4 matrix
	// Extracts the rotation matrix (3x3) from a 4x4 matrix
	inline void m3dExtractRotationMatrix33(M3DMatrix33f dst, const M3DMatrix44f src)
	{
		memcpy(dst, src, sizeof(float) * 3); // X column
		memcpy(dst + 3, src + 4, sizeof(float) * 3); // Y column
		memcpy(dst + 6, src + 8, sizeof(float) * 3); // Z column
	}

	// Ditto above, but for doubles
	inline void m3dExtractRotationMatrix33(M3DMatrix33d dst, const M3DMatrix44d src)
	{
		memcpy(dst, src, sizeof(double) * 3); // X column
		memcpy(dst + 3, src + 4, sizeof(double) * 3); // Y column
		memcpy(dst + 6, src + 8, sizeof(double) * 3); // Z column
	}

	// Inject Rotation (3x3) into a full 4x4 matrix...
	inline void m3dInjectRotationMatrix44(M3DMatrix44f dst, const M3DMatrix33f src)
	{
		memcpy(dst, src, sizeof(float) * 4);
		memcpy(dst + 4, src + 4, sizeof(float) * 4);
		memcpy(dst + 8, src + 8, sizeof(float) * 4);
	}

	// Ditto above for doubles
	inline void m3dInjectRotationMatrix44(M3DMatrix44d dst, const M3DMatrix33d src)
	{
		memcpy(dst, src, sizeof(double) * 4);
		memcpy(dst + 4, src + 4, sizeof(double) * 4);
		memcpy(dst + 8, src + 8, sizeof(double) * 4);
	}
	

	// Transform - Does rotation and translation via a 4x4 matrix. Transforms
	// a point or vector.
	// By-the-way __inline means I'm asking the compiler to do a cost/benefit analysis. If 
	// these are used frequently, they may not be inlined to save memory. I'm experimenting
	// with this....
	// Just transform a 3 compoment vector
	__inline void m3dTransformVector3(M3DVector3f vOut, const M3DVector3f v, const M3DMatrix44f m)
	{
		vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12];// * v[3];	// Assuming 1 
		vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13];// * v[3];	
		vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14];// * v[3];	
																   //vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
	}

	// Ditto above, but for doubles
	__inline void m3dTransformVector3(M3DVector3d vOut, const M3DVector3d v, const M3DMatrix44d m)
	{
		vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12];// * v[3];	 
		vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13];// * v[3];	
		vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14];// * v[3];	
																   //vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
	}

	// Full four component transform
	__inline void m3dTransformVector4(M3DVector4f vOut, const M3DVector4f v, const M3DMatrix44f m)
	{
		vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12] * v[3];
		vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13] * v[3];
		vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3];
		vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
	}

	// Ditto above, but for doubles
	__inline void m3dTransformVector4(M3DVector4d vOut, const M3DVector4d v, const M3DMatrix44d m)
	{
		vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12] * v[3];
		vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13] * v[3];
		vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3];
		vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
	}



	// Just do the rotation, not the translation... this is usually done with a 3x3
	// Matrix.
	__inline void m3dRotateVector(M3DVector3f vOut, const M3DVector3f p, const M3DMatrix33f m)
	{
		vOut[0] = m[0] * p[0] + m[3] * p[1] + m[6] * p[2];
		vOut[1] = m[1] * p[0] + m[4] * p[1] + m[7] * p[2];
		vOut[2] = m[2] * p[0] + m[5] * p[1] + m[8] * p[2];
	}

	// Ditto above, but for doubles
	__inline void m3dRotateVector(M3DVector3d vOut, const M3DVector3d p, const M3DMatrix33d m)
	{
		vOut[0] = m[0] * p[0] + m[3] * p[1] + m[6] * p[2];
		vOut[1] = m[1] * p[0] + m[4] * p[1] + m[7] * p[2];
		vOut[2] = m[2] * p[0] + m[5] * p[1] + m[8] * p[2];
	}

	
	// Find a normal from three points
	// Implemented in math3d.cpp
	void m3dFindNormal(M3DVector3f result, const M3DVector3f point1, const M3DVector3f point2, const M3DVector3f point3);
	void m3dFindNormal(M3DVector3d result, const M3DVector3d point1, const M3DVector3d point2, const M3DVector3d point3);


	// Calculates the signed distance of a point to a plane
	inline float m3dGetDistanceToPlane(const M3DVector3f point, const M3DVector4f plane)
	{
		return point[0] * plane[0] + point[1] * plane[1] + point[2] * plane[2] + plane[3];
	}

	inline double m3dGetDistanceToPlane(const M3DVector3d point, const M3DVector4d plane)
	{
		return point[0] * plane[0] + point[1] * plane[1] + point[2] * plane[2] + plane[3];
	}


	// Get plane equation from three points
	void m3dGetPlaneEquation(M3DVector4f planeEq, const M3DVector3f p1, const M3DVector3f p2, const M3DVector3f p3);
	void m3dGetPlaneEquation(M3DVector4d planeEq, const M3DVector3d p1, const M3DVector3d p2, const M3DVector3d p3);

	// Determine if a ray intersects a sphere
	// Return value is < 0 if the ray does not intersect
	// Return value is 0.0 if ray is tangent
	// Positive value is distance to the intersection point
	double m3dRaySphereTest(const M3DVector3d point, const M3DVector3d ray, const M3DVector3d sphereCenter, double sphereRadius);
	float m3dRaySphereTest(const M3DVector3f point, const M3DVector3f ray, const M3DVector3f sphereCenter, float sphereRadius);


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// Faster (and one shortcut) replacements for gluProject
	void m3dProjectXY(M3DVector2f vPointOut, const M3DMatrix44f mModelView, const M3DMatrix44f mProjection, const int iViewPort[4], const M3DVector3f vPointIn);
	void m3dProjectXYZ(M3DVector3f vPointOut, const M3DMatrix44f mModelView, const M3DMatrix44f mProjection, const int iViewPort[4], const M3DVector3f vPointIn);


	//////////////////////////////////////////////////////////////////////////////////////////////////
	// This function does a three dimensional Catmull-Rom "spline" interpolation between p1 and p2
	void m3dCatmullRom(M3DVector3f vOut, const M3DVector3f vP0, const M3DVector3f vP1, const M3DVector3f vP2, const M3DVector3f vP3, float t);
	void m3dCatmullRom(M3DVector3d vOut, const M3DVector3d vP0, const M3DVector3d vP1, const M3DVector3d vP2, const M3DVector3d vP3, double t);

	//////////////////////////////////////////////////////////////////////////////////////////////////
	// Compare floats and doubles... 
	inline bool m3dCloseEnough(const float fCandidate, const float fCompare, const float fEpsilon)
	{
		return (fabs(fCandidate - fCompare) < fEpsilon);
	}

	inline bool m3dCloseEnough(const double dCandidate, const double dCompare, const double dEpsilon)
	{
		return (fabs(dCandidate - dCompare) < dEpsilon);
	}

	////////////////////////////////////////////////////////////////////////////
	// Used for normal mapping. Finds the tangent bases for a triangle...
	// Only a floating point implementation is provided. This has no practical use as doubles.
	void m3dCalculateTangentBasis(M3DVector3f vTangent, const M3DVector3f pvTriangle[3], const M3DVector2f pvTexCoords[3], const M3DVector3f N);

	////////////////////////////////////////////////////////////////////////////
	// Smoothly step between 0 and 1 between edge1 and edge 2
	double m3dSmoothStep(const double edge1, const double edge2, const double x);
	float m3dSmoothStep(const float edge1, const float edge2, const float x);

	/////////////////////////////////////////////////////////////////////////////
	// Planar shadow Matrix
	void m3dMakePlanarShadowMatrix(M3DMatrix44d proj, const M3DVector4d planeEq, const M3DVector3d vLightPos);
	void m3dMakePlanarShadowMatrix(M3DMatrix44f proj, const M3DVector4f planeEq, const M3DVector3f vLightPos);

	/////////////////////////////////////////////////////////////////////////////
	// Closest point on a ray to another point in space
	double m3dClosestPointOnRay(M3DVector3d vPointOnRay, const M3DVector3d vRayOrigin, const M3DVector3d vUnitRayDir,
		const M3DVector3d vPointInSpace);

	float m3dClosestPointOnRay(M3DVector3f vPointOnRay, const M3DVector3f vRayOrigin, const M3DVector3f vUnitRayDir,
		const M3DVector3f vPointInSpace);

*/

}

