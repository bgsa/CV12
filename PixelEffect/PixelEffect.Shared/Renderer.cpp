#include <algorithm>
#include "Renderer.h"
#include "GLConfig.h"
#include "RendererSettings.h"
#include "Timer.h"
#include "Camera.h"
#include "Point2D.h"
#include "Line2D.h"
#include "GraphicObject.h"
#include "StringHelper.h"
#include "OpenML/Rectangle2D.h"
#include "Panel.h"

/*
#include "opencv2/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
*/

#include <OpenML/SystemOfLinearEquations.h>

bool isRunning = true;

Timer timer;
Camera camera;

Panel* panel = nullptr;
std::vector<Point2D*> points;
Line2D* currentLine = nullptr;
std::vector<Line2D*> listLines;
Vec3f l = Vec3f(8.47174670e-06f, -0.000845056260f, 1.0f);

SystemOfLinearEquations<float> linearEquation;

float homeworkMode = 2.5f;
int step = 1;

Mat3f mHp = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	8.47174670e-06f, -0.000845056260f, 1.0f
};

template <typename T>
void gaussianElimination(T *matrix, int rowSize)
{
	int       i = 0;
	int       j = 0;
	const int m = rowSize - 1;

	while (i < m && j < rowSize)
	{
		int maxi = i;

		for (int k = i + 1; k < m; ++k)
			if (abs(matrix[k * rowSize + j]) > abs(matrix[maxi * rowSize + j]))
				maxi = k;

		if (matrix[maxi * rowSize + j] != T(0))
		{
			if (i != maxi)
				for (int k = 0; k < rowSize; k++)
				{
					const T aux = matrix[i * rowSize + k];
					matrix[i * rowSize + k] = matrix[maxi * rowSize + k];
					matrix[maxi * rowSize + k] = aux;
				}

			const T aIj = matrix[i * rowSize + j];

			for (int k = 0; k < rowSize; k++)
				matrix[i * rowSize + k] /= aIj;

			for (int u = i + 1; u < m; u++)
			{
				const T aUj = matrix[u * rowSize + j];

				for (int k = 0; k < rowSize; k++)
					matrix[u * rowSize + k] -= aUj * matrix[i * rowSize + k];
			}

			++i;
		}

		++j;
	}

	for (i = m - 2; i >= 0; --i)
		for (j = i + 1; j < rowSize - 1; j++)
			matrix[i * rowSize + m] -= matrix[i * rowSize + j] * matrix[j * rowSize + m];
}

//retorna matriz de transformação homography para projetar de um plano a outro plano
Mat3f getPerspectiveTransform(Vec2f sourcePoints[4], Vec2f targetPoints[4])
{
	float p[8][9] = {
		{ -sourcePoints[0][0], -sourcePoints[0][1], -1, 0, 0, 0, sourcePoints[0][0] * targetPoints[0][0], sourcePoints[0][1] * targetPoints[0][0], -targetPoints[0][0] }, // h11
		{ 0, 0, 0, -sourcePoints[0][0], -sourcePoints[0][1], -1, sourcePoints[0][0] * targetPoints[0][1], sourcePoints[0][1] * targetPoints[0][1], -targetPoints[0][1] }, // h12
		{ -sourcePoints[1][0], -sourcePoints[1][1], -1, 0, 0, 0, sourcePoints[1][0] * targetPoints[1][0], sourcePoints[1][1] * targetPoints[1][0], -targetPoints[1][0] }, // h13
		{ 0, 0, 0, -sourcePoints[1][0], -sourcePoints[1][1], -1, sourcePoints[1][0] * targetPoints[1][1], sourcePoints[1][1] * targetPoints[1][1], -targetPoints[1][1] }, // h21
		{ -sourcePoints[2][0], -sourcePoints[2][1], -1, 0, 0, 0, sourcePoints[2][0] * targetPoints[2][0], sourcePoints[2][1] * targetPoints[2][0], -targetPoints[2][0] }, // h22
		{ 0, 0, 0, -sourcePoints[2][0], -sourcePoints[2][1], -1, sourcePoints[2][0] * targetPoints[2][1], sourcePoints[2][1] * targetPoints[2][1], -targetPoints[2][1] }, // h23
		{ -sourcePoints[3][0], -sourcePoints[3][1], -1, 0, 0, 0, sourcePoints[3][0] * targetPoints[3][0], sourcePoints[3][1] * targetPoints[3][0], -targetPoints[3][0] }, // h31
		{ 0, 0, 0, -sourcePoints[3][0], -sourcePoints[3][1], -1, sourcePoints[3][0] * targetPoints[3][1], sourcePoints[3][1] * targetPoints[3][1], -targetPoints[3][1] }, // h32
	};

	gaussianElimination(&p[0][0], 9);

	Mat3f result = Mat3f(
		p[0][8], p[1][8], p[2][8],
		p[3][8], p[4][8], p[5][8],
		p[6][8], p[7][8], 1.0f
	);

	return result;
}

/*
//retorna matriz de transformação afim
Mat3f getAffineTransform(std::vector<Vec2f> sourcePoints)
{
	std::vector<cv::Point2f> src;
	src.resize(3);

	for (size_t i = 0; i < 3; i++)
	{
		src[i].x = sourcePoints[i][0];
		src[i].y = sourcePoints[i][1];
	}

	std::vector<cv::Point2f> targetPoints = {
		cv::Point2f(0.0f , 0.0f),
		cv::Point2f(0.0f,800.0f),
		cv::Point2f(600.0f, 800.0f)
	};

	/*
	cv::Point2f src[3] = {
		cv::Point2f(146.0f , 378.0f),
		cv::Point2f(150.0f,120.0f),
		cv::Point2f(438.0f, 172.0f)
	};

	cv::Point2f targetPoints[3] = {
		cv::Point2f(2.0f , 150.0f),
		cv::Point2f(0.0f,0.0f),
		cv::Point2f(505.0f, 4.0f)
	};
	/

	cv::Mat mat = cv::getAffineTransform(src, targetPoints);

	//cv::transpose(mat, mat);

	Mat3f result = Mat3f::identity();

	for (int i = 0; i < mat.rows; i++)
		for (int j = 0; j < mat.cols; j++)
		{
			cout << (float)mat.data[i * mat.rows + j] << endl;
			result[i * mat.rows + j] = (float)mat.data[j * mat.cols + i];
			//result[j * mat.cols + i] = (float)mat.data[i * mat.rows + j];
		}

	//result = result.transpose();

	return result;
}
*/

OpenML::Line2Df* Renderer::getVanishLine() 
{
	std::vector<OpenML::Point2Df> intersectionPoints;

	for (size_t i = 0; i < listLines.size(); i += 2)
	{
		OpenML::Line2Df line1 = listLines[i]->toOpenMLLine2D();
		OpenML::Line2Df line2 = listLines[i + 1]->toOpenMLLine2D();

		OpenML::Point2Df line2Point1 = line2.point1;
		OpenML::Point2Df line2Point2 = line2.point2;

		float determinant = (line2Point2.x - line2Point1.x) * (line1.point2.y - line1.point1.y) - (line2Point2.y - line2Point1.y) * (line1.point2.x - line1.point1.x);

		if (determinant == 0.0)
			return nullptr; // intersection not found

		double s = ((line2Point2.x - line2Point1.x) * (line2Point1.y - line1.point1.y) - (line2Point2.y - line2Point1.y) * (line2Point1.x - line1.point1.x)) / determinant;

		OpenML::Point2Df intersection = OpenML::Point2Df(
			line1.point1.x + (line1.point2.x - line1.point1.x)* float(s),
			line1.point1.y + (line1.point2.y - line1.point1.y)* float(s)
		);

		intersectionPoints.push_back(intersection);
	}

	return new OpenML::Line2Df(intersectionPoints[0], intersectionPoints[1]);
}

void Renderer::onKeyDown(int keyCode)
{
	if (keyCode == 262) // right
	{
		panel->modelView *= Mat4f::createTranslate(0.1f, 0.0f, 0.0f);
		return;
	}
	if (keyCode == 263) // left
	{
		panel->modelView *= Mat4f::createTranslate(-0.1f, 0.0f, 0.0f);
		return;
	}
	if (keyCode == 265) // up
	{
		panel->modelView *= Mat4f::createTranslate(0.0f, 0.1f, 0.0f);
		return;
	}
	if (keyCode == 264) // down
	{
		panel->modelView *= Mat4f::createTranslate(0.0f, -0.1f, 0.0f);
		return;
	}

	if (keyCode != 257 && keyCode != 335)
		return;

	float screenWidth = float(RendererSettings::getInstance()->getWidth());
	float screenHeight = float(RendererSettings::getInstance()->getHeight());

	Mat3f tempHomographyMatrix = Mat3f::identity();

	if (homeworkMode == 1.0f) 
	{
		std::vector<Vec2f> sourcePoints;
		sourcePoints.resize(4);

		for (size_t i = 0; i < 4; i++)
			sourcePoints[i] = points[i]->getPosition().toVec2();

		std::vector<Vec2f> targetPoints = {
			Vec2f(0.0 , 0.0),
			Vec2f(0.0 ,screenHeight),
			Vec2f(screenWidth , screenHeight),
			Vec2f(screenWidth , 0.0)
		};

		tempHomographyMatrix = getPerspectiveTransform(sourcePoints.data(), targetPoints.data());
	}
	else if (homeworkMode == 2.0f)
	{
		if (step == 1) 
		{	
			OpenML::Line2Df* vanishLine = getVanishLine();
			//OpenML::Line2Df* vanishLine = new OpenML::Line2Df;
			//vanishLine->point1 = Vec2f(1648.97009f, 1199.88416f);
			//vanishLine->point2 = Vec2f(-923.694580f, 1174.09302);

			Vec3f x0 = Vec3f(vanishLine->point1.x, vanishLine->point1.y, 1.0f);
			Vec3f x1 = Vec3f(vanishLine->point2.x, vanishLine->point2.y, 1.0f);

			l = x0.cross(x1);
			l = l / l.z();

			mHp = {
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				l.x(), l.y(), l.z()
			};

			mHp *= Mat3f::createScale(0.5f, 0.5f, 1.0f);

			tempHomographyMatrix = mHp.invert();

			step = 2;
		}
		else 
		{
			OpenML::Line2Df linha1 = listLines[0]->toOpenMLLine2D();
			OpenML::Line2Df linha3 = listLines[1]->toOpenMLLine2D();
			OpenML::Line2Df linha2 = listLines[2]->toOpenMLLine2D();
			OpenML::Line2Df linha4 = listLines[3]->toOpenMLLine2D();

			/*
			OpenML::Point2Df linha1Point1 = OpenML::Point2Df(471.0f, 338.0f);
			OpenML::Point2Df linha1Point2 = OpenML::Point2Df(366.0f, 260.0f);
			OpenML::Line2Df linha1 = OpenML::Line2Df(linha1Point1, linha1Point2);			

			OpenML::Point2Df linha2Point1 = OpenML::Point2Df(366.0f, 260.0f);
			OpenML::Point2Df linha2Point2 = OpenML::Point2Df(452.0f, 152.0f);
			OpenML::Line2Df linha2 = OpenML::Line2Df(linha2Point1, linha2Point2);			

			OpenML::Point2Df linha3Point1 = OpenML::Point2Df(257.0f, 178.0f);
			OpenML::Point2Df linha3Point2 = OpenML::Point2Df(358.0f, 53.0f);
			OpenML::Line2Df linha3 = OpenML::Line2Df(linha3Point1, linha3Point2);			

			OpenML::Point2Df linha4Point1 = OpenML::Point2Df(255.0f, 180.0f);
			OpenML::Point2Df linha4Point2 = OpenML::Point2Df(140.0f, 95.0f);
			OpenML::Line2Df linha4 = OpenML::Line2Df(linha4Point1, linha4Point2);
			*/

			Vec2f l1 = linha1.toRay();
			Vec2f m1 = linha2.toRay();
			Vec2f l2 = linha3.toRay();
			Vec2f m2 = linha4.toRay();

			float cosine1 = l1.dot(m1);
			float cosine2 = l2.dot(m2);
			//assert(cosine1 < 0.05f);
			//assert(cosine2 < 0.05f);

			float l11 = l1.x();
			float l12 = l1.y();
			float m11 = m1.x();
			float m12 = m1.y();
			float l21 = l2.x();
			float l22 = l2.y();
			float m21 = m2.x();
			float m22 = m2.y();

			float result[2][3] = {
				{ l1.x() * m1.x(), l1.x() * m1.y() + l1.y() * m1.x(), l1.y() * m1.y() },
				{ l2.x() * m2.x(), l2.x() * m2.y() + l2.y() * m2.x(), l2.y() * m2.y() }
			};

			gaussianElimination(&result[0][0], 3);

			float s11 = result[0][2];
			float s12 = result[1][2];
			float s22 = 1.0f;
			
			tempHomographyMatrix = {
				s11, s12, 0.0f,
				s12, s22, 0.0f,
				0.0f, 0.0f, 1.0f
			};

			tempHomographyMatrix *= Mat3f::createScale(0.5f, 0.5f, 1.0f);

			tempHomographyMatrix = mHp * tempHomographyMatrix;
						
			tempHomographyMatrix = tempHomographyMatrix.invert();
		}
	}
	else if (homeworkMode == 2.5f)
	{
		Line2D * line1 = new Line2D;
		line1->setPoint1({ 66.0f, 374.0f });
		line1->setPoint2({ 69.0f, 439.0f });
		
		Line2D * line2 = new Line2D;
		line2->setPoint1({ 69.0f, 439.0f });
		line2->setPoint2({ 145.0f, 433.0f });

		Line2D * line3 = new Line2D;
		line3->setPoint1({ 235.0f, 425.0f });
		line3->setPoint2({ 309.0f, 420.0f });

		Line2D * line4 = new Line2D;
		line4->setPoint1({ 309.0f, 420.0f });
		line4->setPoint2({ 307.0f, 361.0f });
		 
		Line2D * line5 = new Line2D;
		line5->setPoint1({ 68.0f, 92.0f });
		line5->setPoint2({ 152.0f, 96.0f });

		Line2D * line6 = new Line2D;
		line6->setPoint1({ 152.0f, 96.0f });
		line6->setPoint2({ 152.0f, 187.0f });
		 
		Line2D * line7 = new Line2D;
		line7->setPoint1({ 237.0f, 186.0f });
		line7->setPoint2({ 240.0f, 102.0f });

		Line2D * line8 = new Line2D;
		line8->setPoint1({ 240.0f, 102.0f });
		line8->setPoint2({ 314.0f, 105.0f });

		Line2D * line9 = new Line2D;
		line9->setPoint1({ 390.0f, 190.0f });
		line9->setPoint2({ 464.0f, 108.0f });

		Line2D * line10 = new Line2D;
		line10->setPoint1({ 393.0f, 107.0f });
		line10->setPoint2({ 459.0f, 192.0f });

		listLines.push_back(line1);
		listLines.push_back(line2);
		listLines.push_back(line3);
		listLines.push_back(line4);
		listLines.push_back(line5);
		listLines.push_back(line6);
		listLines.push_back(line7);
		listLines.push_back(line8);
		listLines.push_back(line9);
		listLines.push_back(line10);

		/*
		parallelLines.push_back(line1);
		parallelLines.push_back(line3);
		parallelLines.push_back(line5);
		parallelLines.push_back(line7);
		parallelLines.push_back(line9);
		parallelLines.push_back(line2);
		parallelLines.push_back(line4);
		parallelLines.push_back(line6);
		parallelLines.push_back(line8);
		parallelLines.push_back(line10);
		*/

		float linearSystem[5][6];

		int row = 0;
		for (size_t i = 0; i < listLines.size(); i+=2)
		{
			Vec2f l = listLines[i]->toOpenMLLine2D().toRay();
			Vec2f m = listLines[i+1]->toOpenMLLine2D().toRay();

			float l1 = l.x();
			float l2 = l.y();
			float l3 = 1.0f;

			float m1 = m.x();
			float m2 = m.y();
			float m3 = 1.0f;

			float cossine = l.dot(m);
			
			linearSystem[row][0] = l1 * m1;
			linearSystem[row][1] = (l1 * m2 + l2 * m1) * 0.5f;
			linearSystem[row][2] = l2 * m2;
			linearSystem[row][3] = (l1 * m3 + l3 * m1) * 0.5f;
			linearSystem[row][4] = (l2 * m3 + l3 * m2) * 0.5f;
			linearSystem[row][5] = l3 * m3;

			row++;
		}

		gaussianElimination(&linearSystem[0][0], 6);
		float a = linearSystem[0][5];
		float b = linearSystem[1][5] * 0.5f;
		float c = linearSystem[2][5];
		float d = linearSystem[3][5] * 0.5f;
		float e = linearSystem[4][5] * 0.5f;
		float f = 1.0f;

		/*
		float* result = linearEquation.solve(&result[0][0], 5, 6);
		float a = result[0];
		float b = result[1] * 0.5f;
		float c = result[2];
		float d = result[3] * 0.5f;
		float e = result[4] * 0.5f;
		float f = 1.0f;
		*/

		tempHomographyMatrix = {
			a, b, d,
			b, c, e,
			d, e, f
		};

		//tempHomographyMatrix *= Mat3f::createScale(1000.0f, 1000.0f, 1.0f);
		//tempHomographyMatrix *= Mat3f::createScale(0.5f, 0.5f, 1.0f);
		
		tempHomographyMatrix = tempHomographyMatrix.invert();
	}
		
	panel->homographyMatrix = tempHomographyMatrix;
	panel->useHomography = 1;

	for (Line2D* line : listLines)
	{
		removeGraphicObject(line);
		//delete line;
	}
	listLines.clear();

	for (Point2D* point : points)
	{
		removeGraphicObject(point);
		delete point;
	}
	points.clear();
}

void Renderer::onMouseDown(MouseEvent e)
{
	if (e.button != MouseButton::LEFT)
		return;

	if (homeworkMode == 1.0f) {
		Point2D* point = new Point2D();
		point->setPosition(e.currentPosition);
		point->init();
		point->setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		point->setPointSize(8.0f);

		points.push_back(point);

		graphicObjects.push_back(point);
	}
	else
	{
		currentLine = new Line2D;
		currentLine->setPoint1(e.currentPosition);
		currentLine->setPoint2(e.currentPosition);
		currentLine->setColor({ 1.0f, 0.0f, 1.0f, 1.0f });
		currentLine->init();

		addGraphicObject(currentLine);
	}
};

void Renderer::onMouseMove(MouseEvent e)
{
	if (((int)homeworkMode) == 2)
	{
		if (currentLine == nullptr)
			return;

		currentLine->setPoint2(e.currentPosition);
	}
}

void Renderer::onMouseUp(MouseEvent e)
{
	if (((int)homeworkMode) == 2)
	{
		currentLine->setPoint2(e.currentPosition);

		Line2D* newParallelLine = new Line2D;
		newParallelLine->setPoint1(currentLine->getPoint1());
		newParallelLine->setPoint2(currentLine->getPoint2());
		newParallelLine->setColor({ 1.0f, 0.0f, 0.0f ,1.0f });
		newParallelLine->init();
		listLines.push_back(newParallelLine);

		addGraphicObject(newParallelLine);

		removeGraphicObject(currentLine);
		delete currentLine;
		currentLine = nullptr;
	}
};

void Renderer::start()
{
#ifdef WINDOWS
	while (isRunning)
	{
		update();
		render();

		Log::glErrors(__FILE__, __LINE__);
	}
#endif
}

void Renderer::addGraphicObject(GraphicObject* graphicObject)
{
	PointerInputDeviceHandler* pointerHandler = dynamic_cast<PointerInputDeviceHandler*>(graphicObject);

	if (pointerHandler != nullptr)
		for (PointerInputDevice* pointerInputDevice : pointerInputDevices)
			pointerInputDevice->addHandler(pointerHandler);


	KeyboardInputDeviceHandler* keyboardHandler = dynamic_cast<KeyboardInputDeviceHandler*>(graphicObject);

	if (keyboardHandler != nullptr)
		for (KeyboardInputDevice* keyboardInputDevice : keyboardInputDevices)
			keyboardInputDevice->addHandler(keyboardHandler);


	TouchInputDeviceHandler* touchHandler = dynamic_cast<TouchInputDeviceHandler*>(graphicObject);

	if (touchHandler != nullptr)
		for (TouchInputDevice* touchInputDevice : touchInputDevices)
			touchInputDevice->addHandler(touchHandler);


	WindowInputDeviceHandler* windowHandler = dynamic_cast<WindowInputDeviceHandler*>(graphicObject);

	if (windowHandler != nullptr)
		for (WindowInputDevice* windowInputDevice : windowInputDevices)
			windowInputDevice->addHandler(windowHandler);

	graphicObjects.push_back(graphicObject);
}

void Renderer::removeGraphicObject(GraphicObject* graphicObject)
{
	vector<GraphicObject*>::iterator item = std::find(graphicObjects.begin(), graphicObjects.end(), graphicObject);

	if (item != graphicObjects.end())
		graphicObjects.erase(item);
}

void Renderer::resize(int width, int height)
{
	glViewport(0, 0, width, height);

	RendererSettings::getInstance()->setWidth(width);
	RendererSettings::getInstance()->setHeight(height);

	panel->setSize(float(width), float(height));
}

void Renderer::init(DisplayDevice* displayDevice)
{
	this->displayDevice = displayDevice;

	Log::info("OpenGL Vendor: " + GLConfig::getGLVendor());
	Log::info("OpenGL Version: " + GLConfig::getGLVersion());
	Log::info("OpenGLSL Version: " + GLConfig::getGLShadingLanguageVersion());
	Log::info("OpenGL Renderer: " + GLConfig::getGLRenderer());
	Log::info("OpenGL Extensions:");

	for (string extension : GLConfig::getGLExtensions())
		Log::info(extension);

	timer.start();

	//glEnable(GL_CULL_FACE); //elimina os vértices que estão sendo renderizados atrás de outros vértices. Ex.: modelo 3D
	glEnable(GL_DEPTH_TEST); //elimina os vértices que sobrepoem outros vértices quando estão no mesmo eixo Z.
	glEnable(GL_BLEND);									  //enable alpha color
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    //enable alpha color

	Vec3f cameraPosition = { 0.0f, 5.0f, 10.0f };
	Vec3f cameraTarget = { 0.0f, 3.0f, 0.0f };
	camera.init(cameraPosition, cameraTarget);

	panel = new Panel;

	if (homeworkMode == 1.0f)
		panel->setBackgroundImage("resources/images/brahma01.png");
	else if (homeworkMode == 2.0f) 
	{
		if (step == 1)
			panel->setBackgroundImage("resources/images/piso1.png");
		else
			panel->setBackgroundImage("resources/images/retificacao-afim.png");
	}
	else if (homeworkMode == 2.5f) 
	{
		panel->setBackgroundImage("resources/images/wall25.png");
	}

	panel->init();
	graphicObjects.push_back(panel);
}

void Renderer::updateInputDevices(long long elapsedTime)
{
	for (InputDevice* device : pointerInputDevices)
		device->update(elapsedTime);

	for (InputDevice* device : keyboardInputDevices)
		device->update(elapsedTime);

	for (InputDevice* device : windowInputDevices)
		device->update(elapsedTime);

	for (InputDevice* device : touchInputDevices)
		device->update(elapsedTime);
}

void Renderer::update()
{
	long long elapsedTime = timer.getElapsedTime();
	//cout << "FPS: " << timer.getFramesPerSecond() << END_OF_LINE;
	//cout << elapsedTime << END_OF_LINE;

	updateInputDevices(elapsedTime);

	//camera
	camera.update(elapsedTime);

	//update graphs objects
	for (GraphicObject* graph : graphicObjects)
		graph->update(elapsedTime);

	//sprite.update(elapsedTime);

	timer.update();
}

void Renderer::render3D(Mat4f projectionViewMatrix)
{
}

void Renderer::render2D(Mat4f projectionViewMatrix)
{
	for (GraphicObject* graph : graphicObjects) {
		GraphicObject2D* graph2D = dynamic_cast<GraphicObject2D*>(graph);

		if (graph2D != nullptr)
			graph2D->render(projectionViewMatrix);
	}
}

void Renderer::render()
{
	int width = RendererSettings::getInstance()->getWidth();
	int height = RendererSettings::getInstance()->getHeight();
	ColorRGBAf backgroundColor = RendererSettings::getInstance()->getBackgroudColor().normalizeColor();

	glClearColor(backgroundColor.Red, backgroundColor.Green, backgroundColor.Blue, backgroundColor.Alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	float aspectRatio = RendererSettings::getInstance()->getAspectRatio();
	camera.setPerspective(90.0f, aspectRatio, 1.0f, 1000.0f);
	Mat4f projectionViewMatrix = camera.getProjectionViewMatrix().clone();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	render3D(projectionViewMatrix);

	projectionViewMatrix = camera.getHUDProjectionMatrix(float(width), float(height)).clone();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	render2D(projectionViewMatrix);

	displayDevice->swapBuffer();
}

void Renderer::exit()
{
	isRunning = false;
}

/* TOUCH INPUT HANDLE */
void Renderer::onTouchDown(TouchItem* touchItem)
{
	MouseEvent e;
	e.currentPosition = OpenML::Point2Df(float(touchItem->currentPosition.x), float(touchItem->currentPosition.y));
	e.button = MouseButton::LEFT;
	onMouseDown(e);
}
void Renderer::onTouchUp(TouchItem* touchItem)
{
	MouseEvent e;
	e.currentPosition = OpenML::Point2Df(float(touchItem->currentPosition.x), float(touchItem->currentPosition.y));
	e.button = MouseButton::LEFT;
	onMouseUp(e);
}
void Renderer::onTouchMove(TouchItem* touchItem)
{
	MouseEvent e;
	e.currentPosition = OpenML::Point2Df(float(touchItem->currentPosition.x), float(touchItem->currentPosition.y));
	onMouseMove(e);
}

void Renderer::onTouchPointerIn(TouchEvent e)
{

};
void Renderer::onTouchPointerOut(TouchEvent e)
{

};


void Renderer::addInputDevice(InputDevice* inputDevice)
{
	PointerInputDevice* pointerDevice = dynamic_cast<PointerInputDevice*>(inputDevice);
	if (pointerDevice)
		pointerInputDevices.push_back(pointerDevice);

	KeyboardInputDevice* keyboardDevice = dynamic_cast<KeyboardInputDevice*>(inputDevice);
	if (keyboardDevice)
		keyboardInputDevices.push_back(keyboardDevice);

	WindowInputDevice* windowDevice = dynamic_cast<WindowInputDevice*>(inputDevice);
	if (windowDevice)
		windowInputDevices.push_back(windowDevice);

	TouchInputDevice* touchDevice = dynamic_cast<TouchInputDevice*>(inputDevice);
	if (touchDevice)
		touchInputDevices.push_back(touchDevice);
}

void Renderer::onClose()
{
	this->exit();
}

Renderer::~Renderer()
{
	for (InputDevice* device : pointerInputDevices)
		delete device;

	delete displayDevice;
}

void Renderer::onKeyUp(int keyCode)
{
	if (keyCode == 27) //ESC pressed
		this->exit();
}