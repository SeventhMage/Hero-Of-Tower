#ifndef DRIVER_DATA_H_
#define DRIVER_DATA_H_

#include <d3d9.h>

namespace xeng
{
	struct DriverData
	{
		union
		{
			struct
			{
				IDirect3D9 *D3D9;
				IDirect3DDevice9 *D3DDev9;
				void *HWnd;

			} D3D9;

			struct
			{
				void *HDc;
				void *HRc;
				void *HWnd;
			} OpenGLWin32;

			struct
			{
				// XWindow handles
				void *X11Display;
				void *X11Context;
				unsigned long X11Window;
			} OpenGLLinux;
		};


		int WindowWidth;
		int WindowHeight;
	};
}



#endif
