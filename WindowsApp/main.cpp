#include <stdlib.h>
#include <cstdlib>

#include <GlobalHeader.h>

#include <DisplayDeviceWindow.h>
#include <KeyboardInputDeviceWindows.h>
#include <PointerInputDeviceWindows.h>
#include <WindowInputDeviceWindows.h>
#include <Renderer.h>
#include <RendererSettings.h>


#ifdef WINDOWS
	#define ESUTIL_API  __cdecl
	#define ESCALLBACK  __cdecl
#else
	#define ESUTIL_API
	#define ESCALLBACK
#endif

#define WINDOW_TITLE "Windows App"
#define WINDOW_POSITION_X 300
#define WINDOW_POSITION_Y 200
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_FULLSCREEN false

int main(int argc, char *argv[])
{
	cout << "1" << endl;
	GLFWwindow* window;
	DisplayDeviceWindow* monitor = new DisplayDeviceWindow;
	KeyboardInputDeviceWindows* keyboard = new KeyboardInputDeviceWindows;
	PointerInputDeviceWindows* mouse = new PointerInputDeviceWindows;
	
	glfwSetErrorCallback( Log::onError );

	if (!glfwInit())
		return -1;
	
#ifdef OPENGLES
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
#endif

	int positionX = WINDOW_POSITION_X;
	int positionY = WINDOW_POSITION_Y;
	int width = WINDOW_WIDTH;
	int height = WINDOW_HEIGHT;

	if (WINDOW_FULLSCREEN) 
	{
		positionX = 0;
		positionY = 0;
		width = monitor->getWidth();
		height = monitor->getHeight();
	}

	window = glfwCreateWindow(width, height, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	RendererSettings::getInstance()->setScreenPosition({ float(positionX), float(positionY) });

	GLenum glewinit = glewInit();
	if (glewinit != GLEW_OK)
	{
		string errorMessage = reinterpret_cast<char*>( ((GLubyte*) glewGetErrorString(glewinit)) );
		Log::error(errorMessage);
		return -1;
	}

	cout << "2" << endl;

	monitor->init(window);

	keyboard->init(window);
	mouse->init(window);

	WindowInputDeviceWindows* windowsDevice = WindowInputDeviceWindows::getInstance();
	windowsDevice->init(window);
	
	Renderer* renderer = new Renderer;

	cout << "3" << endl;

	if (argc > 1)
		renderer->homeworkMode = float((int)*argv[1] - 48);

	if (argc > 2 && *argv[2] == 'D')
		renderer->isDebug = true;

	renderer->init(monitor);

	renderer->addInputDevice(mouse);
	renderer->addInputDevice(keyboard);
	renderer->addInputDevice(windowsDevice);

	keyboard->addHandler(renderer);
	mouse->addHandler(renderer);
	windowsDevice->addHandler(renderer);

	cout << "4" << endl;

	renderer->resize(width, height);
	renderer->start();

	cout << "5" << endl;
	
	delete renderer;

	glfwTerminate();

	return 0;
}