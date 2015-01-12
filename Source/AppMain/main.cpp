#include "MyApp.h"
#include "../../XEng/Video/DriverData.h"
#include "../../XEng/Video/OpenGL/OpenGLDriver.h"

using namespace xeng;

int main(int argc, char **argv)
{
	MyApp myApp;
	myApp.Run();

// 	DriverData driverData;
// 	driverData.WindowWidth = 960;
// 	driverData.WindowHeight = 640;
// 	IVideoDriver *pDriver = new OpenGLDriver();
// 	pDriver->Init(&driverData);

	return 0;
}