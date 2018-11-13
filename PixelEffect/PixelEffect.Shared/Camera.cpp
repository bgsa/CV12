#include "Camera.h"

void Camera::init(Vec3f position, Vec3f target, Vec3f up)
{
	this->position[0] = position[0];
	this->position[1] = position[1];
	this->position[2] = position[2];

	this->target[0] = target[0];
	this->target[1] = target[1];
	this->target[2] = target[2];

	this->up[0] = up[0];
	this->up[1] = up[1];
	this->up[2] = up[2];
}

void Camera::setPosition(Vec3f newPostion)
{
	this->position[0] = newPostion[0];
	this->position[1] = newPostion[1];
	this->position[2] = newPostion[2];
}

void Camera::setTarget(Vec3f newTarget)
{
	this->target[0] = newTarget[0];
	this->target[1] = newTarget[1];
	this->target[2] = newTarget[2];
}

Vec3f& Camera::getPosition()
{
	return position;
}

Vec3f& Camera::getTarget()
{
	return target;
}

Mat4f& Camera::getProjectionMatrix()
{
	return projectionMatrix;
}

Mat4f& Camera::getViewMatrix()
{
	return viewMatrix;
}

Mat4f& Camera::getProjectionViewMatrix()
{
	return projectionViewMatrix;
}

void Camera::setPerspective(float fieldOfView, float aspect, float near, float far) 
{
	float xmin, xmax, ymin, ymax;       // Dimensions of near clipping plane
	float xFmin, xFmax, yFmin, yFmax;   // Dimensions of far clipping plane

	// Do the Math for the near clipping plane
	ymax = near * float(tan(fieldOfView * PI / 360.0));
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = -xmin;

	// Construct the projection matrix
	projectionMatrix = Mat4f::identity();
	projectionMatrix[0] = (2.0f * near) / (xmax - xmin);
	projectionMatrix[5] = (2.0f * near) / (ymax - ymin);
	projectionMatrix[8] = (xmax + xmin) / (xmax - xmin);
	projectionMatrix[9] = (ymax + ymin) / (ymax - ymin);
	projectionMatrix[10] = -((far + near) / (far - near));
	projectionMatrix[11] = -1.0f;
	projectionMatrix[14] = -((2.0f * far * near) / (far - near));
	projectionMatrix[15] = 0.0f;

	// Do the Math for the far clipping plane
	yFmax = far * float(tan(fieldOfView * PI / 360.0));
	yFmin = -yFmax;
	xFmin = yFmin * aspect;
	xFmax = -xFmin;
	
	// Fill in values for untransformed Frustum corners
	// Near Upper Left
	nearUL[0] = xmin; 
	nearUL[1] = ymax; 
	nearUL[2] = -near; 
	nearUL[3] = 1.0f;

	// Near Lower Left
	nearLL[0] = xmin; 
	nearLL[1] = ymin; 
	nearLL[2] = -near; 
	nearLL[3] = 1.0f;

	// Near Upper Right
	nearUR[0] = xmax; 
	nearUR[1] = ymax; 
	nearUR[2] = -near; 
	nearUR[3] = 1.0f;

	// Near Lower Right
	nearLR[0] = xmax; 
	nearLR[1] = ymin;
	nearLR[2] = -near;
	nearLR[3] = 1.0f;

	// Far Upper Left
	farUL[0] = xFmin;
	farUL[1] = yFmax;
	farUL[2] = -far;
	farUL[3] = 1.0f;

	// Far Lower Left
	farLL[0] = xFmin;
	farLL[1] = yFmin;
	farLL[2] = -far;
	farLL[3] = 1.0f;

	// Far Upper Right
	farUR[0] = xFmax;
	farUR[1] = yFmax;
	farUR[2] = -far;
	farUR[3] = 1.0f;

	// Far Lower Right
	farLR[0] = xFmax;
	farLR[1] = yFmin;
	farLR[2] = -far;
	farLR[3] = 1.0f;

	updateProjectionViewMatrix();
}

void Camera::setOrthographic(GLfloat xMin, GLfloat xMax, GLfloat yMin, GLfloat yMax, GLfloat zMin, GLfloat zMax)
{
	projectionMatrix = Mat4f::createOrthographicMatrix(xMin, xMax, yMin, yMax, zMin, zMax);
	projectionMatrix[15] = 1.0f;
	
	// Fill in values for untransformed Frustum corners	// Near Upper Left
	nearUL[0] = xMin; 
	nearUL[1] = yMax; 
	nearUL[2] = zMin; 
	nearUL[3] = 1.0f;

	// Near Lower Left
	nearLL[0] = xMin; 
	nearLL[1] = yMin; 
	nearLL[2] = zMin; 
	nearLL[3] = 1.0f;

	// Near Upper Right
	nearUR[0] = xMax; 
	nearUR[1] = yMax; 
	nearUR[2] = zMin;
	nearUR[3] = 1.0f;

	// Near Lower Right
	nearLR[0] = xMax; 
	nearLR[1] = yMin; 
	nearLR[2] = zMin; 
	nearLR[3] = 1.0f;

	// Far Upper Left
	farUL[0] = xMin; 
	farUL[1] = yMax; 
	farUL[2] = zMax;
	farUL[3] = 1.0f;

	// Far Lower Left
	farLL[0] = xMin; 
	farLL[1] = yMin; 
	farLL[2] = zMax; 
	farLL[3] = 1.0f;

	// Far Upper Right
	farUR[0] = xMax; 
	farUR[1] = yMax;
	farUR[2] = zMax; 
	farUR[3] = 1.0f;

	// Far Lower Right
	farLR[0] = xMax; 
	farLR[1] = yMin; 
	farLR[2] = zMax; 
	farLR[3] = 1.0f;

	updateProjectionViewMatrix();
}

Mat4f Camera::getHUDProjectionMatrix(float width, float height)
{
	Mat4f matrix = Mat4f::createOrthographicMatrix(0.0f, width, 0.0f, height, -1.0f, 1.0f);
	matrix[15] = 1.0f;

	return matrix;
}

void Camera::updateProjectionViewMatrix()
{
	Vec3f cameraDirection = (position - target).normalize(); //zAxis
	Vec3f cameraRight = up.cross(cameraDirection).normalize(); //xAxis
	Vec3f cameraUp = cameraDirection.cross(cameraRight); //yAxis
	
	Mat4f cameraMatrix = {
		cameraRight[0], cameraRight[1], cameraRight[2], 0.0f,
		cameraUp[0], cameraUp[1], cameraUp[2], 0.0f,
		cameraDirection[0], cameraDirection[1], cameraDirection[2], 0.0f,
		position[0], position[1], position[2], 1.0f
	};
	
	viewMatrix = cameraMatrix.invert();
	projectionViewMatrix = projectionMatrix * viewMatrix;
}

void Camera::update(long long elapsedTime) 
{
	updateProjectionViewMatrix();
}