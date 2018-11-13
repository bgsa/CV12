#pragma once

#include "GlobalHeader.h"

class Camera
{
protected:
	Mat4f projectionMatrix;
	Mat4f viewMatrix;
	Mat4f projectionViewMatrix;

	Vec3f position;
	Vec3f target;
	Vec3f up;

	// Untransformed corners of the frustum
	Vec4f nearUL, nearLL, nearUR, nearLR;
	Vec4f farUL, farLL, farUR, farLR;

	// Transformed corners of Frustum
	Vec4f nearULT, nearLLT, nearURT, nearLRT;
	Vec4f farULT, farLLT, farURT, farLRT;

	// Base and Transformed plane equations
	Vec4f nearPlane, farPlane, leftPlane, rightPlane;
	Vec4f topPlane, bottomPlane;
	
public:
	void init(Vec3f position, Vec3f target, Vec3f up = Vec3f(0.0f , 1.0f, 0.0f) );

	Vec3f& getPosition();
	void setPosition(Vec3f newPostion);

	Vec3f& getTarget();
	void setTarget(Vec3f newTarget);

	Mat4f& getProjectionMatrix();
	Mat4f& getViewMatrix();
	Mat4f& getProjectionViewMatrix();

	void setPerspective(float fieldOfView, float aspect, float near, float far);
	void setOrthographic(GLfloat xMin, GLfloat xMax, GLfloat yMin, GLfloat yMax, GLfloat zMin, GLfloat zMax);

	Mat4f getHUDProjectionMatrix(float width, float height);

	void updateProjectionViewMatrix();
	void update(long long elapsedTime);
};
