#include "DisplayDeviceWindow.h"

void DisplayDeviceWindow::init(GLFWwindow* window)
{
	this->window = window;

	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

	const GLFWvidmode * video = glfwGetVideoMode(primaryMonitor);
		
	//glfwGetMonitorPhysicalSize(primaryMonitor, &width, &height);

	//int count;
	//GLFWmonitor** monitors = glfwGetMonitors(&count); // PEGA A QTD DE MONITORES
	//const char* name = glfwGetMonitorName(monitor); // pega o nome do monitor

	//glfwSetMonitorCallback(monitorEvent); // pega os eventos de monitores conectados e desconectados

	/*
	DEVMODE dmSettings;  // Device Mode variable - Needed to change modes

	memset(&dmSettings, 0, sizeof(dmSettings));	// Makes Sure Memory's Cleared

	// Get the current display settings.  This function fills our the settings.
	if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmSettings))
	{
	MessageBox(NULL, "Could Not Enum Display Settings", "Error", MB_OK);
	return;
	}

	setWidth(dmSettings.dmPelsWidth);
	setHeight(dmSettings.dmPelsHeight);
	*/

	setWidth(video->width);
	setHeight(video->height);
}

void DisplayDeviceWindow::swapBuffer() 
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

/*
Altera a resolução do monitor

void ChangeResolution(int width, int height)
{
	DEVMODE dmSettings;									// Device Mode variable - Needed to change modes

	memset(&dmSettings, 0, sizeof(dmSettings));			// Makes Sure Memory's Cleared

	// Get the current display settings.  This function fills our the settings.
	if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmSettings))
	{
		// Display error message if we couldn't get display settings
		MessageBox(NULL, "Could Not Enum Display Settings", "Error", MB_OK);
		return;
	}

	dmSettings.dmPelsWidth = width;					// Set the desired Screen Width
	dmSettings.dmPelsHeight = height;					// Set the desired Screen Height
	dmSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;	// Set the flags saying we're changing the Screen Width and Height

	// This function actually changes the screen to full screen
	// CDS_FULLSCREEN Gets Rid Of Start Bar.
	// We always want to get a result from this function to check if we failed
	int result = ChangeDisplaySettings(&dmSettings, CDS_FULLSCREEN);

	// Check if we didn't receive a good return message From the function
	if (result != DISP_CHANGE_SUCCESSFUL)
	{
		// Display the error message and quit the program
		MessageBox(NULL, "Display Mode Not Compatible", "Error", MB_OK);
		PostQuitMessage(0);
	}
}
*/