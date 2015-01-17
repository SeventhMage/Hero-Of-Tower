#include "OpenGLDriver.h"
#include <wingdi.h>
#include <Windows.h>
#include <assert.h>
#include "../../File/Log/Log.h"
#include "GL/glew.h"
#include "GL/wglew.h"


namespace xeng
{
	OpenGLDriver::OpenGLDriver()
	{

	}

	OpenGLDriver::~OpenGLDriver()
	{

	}



	bool OpenGLDriver::Init(DriverData *pDriverData)
	{
		assert(pDriverData);

		bool bRetVal = true;
		static	PIXELFORMATDESCRIPTOR pfd =					// /pfd 告诉窗口我们所希望的东东，即窗口使用的像素格式

		{

			sizeof(PIXELFORMATDESCRIPTOR),					// 上述格式描述符的大小

			1,								// 版本号

			PFD_DRAW_TO_WINDOW |						// 格式支持窗口

			PFD_SUPPORT_OPENGL |						// 格式必须支持OpenGL

			PFD_DOUBLEBUFFER,						// 必须支持双缓冲

			PFD_TYPE_RGBA,							// 申请 RGBA 格式

			32,								// 选定色彩深度

			0, 0, 0, 0, 0, 0,						// 忽略的色彩位

			0,								// 无Alpha缓存

			0,								// 忽略Shift Bit

			0,								// 无累加缓存

			0, 0, 0, 0,							// 忽略聚集位

			16,								// 16位 Z-缓存 (深度缓存)

			0,								// 无蒙板缓存

			0,								// 无辅助缓存

			PFD_MAIN_PLANE,							// 主绘图层

			0,								// Reserved

			0, 0, 0								// 忽略层遮罩

		};


		// now that we have a window, setup the pixel format descriptor
		pDriverData->OpenGLWin32.HDc = GetDC((HWND)pDriverData->OpenGLWin32.HWnd);

		GLuint PixelFormat = ChoosePixelFormat((HDC)pDriverData->OpenGLWin32.HDc, &pfd);

		// Set a dummy pixel format so that we can get access to wgl functions
		BOOL ret = SetPixelFormat((HDC)pDriverData->OpenGLWin32.HDc, PixelFormat, &pfd);
		// Create OGL context and make it current
		pDriverData->OpenGLWin32.HRc = wglCreateContext((HDC)pDriverData->OpenGLWin32.HDc);
		ret = wglMakeCurrent((HDC)pDriverData->OpenGLWin32.HDc, (HGLRC)pDriverData->OpenGLWin32.HRc);
		GLenum err = glewInit();
		if (err != 0)
		{
			bRetVal = false;
		}
		/*
		if ((HDC)pDriverData->OpenGLWin32.HDc == 0 ||
			(HDC)pDriverData->OpenGLWin32.HRc == 0)
		{
			bRetVal = false;
			DLOG("!!! An error occured creating an OpenGL window.\n");
		}

		// Setup GLEW which loads OGL function pointers
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			bRetVal = false;
			DLOG("Error: %s\n", glewGetErrorString(err));
		}
		const GLubyte *oglVersion = glGetString(GL_VERSION);
		DLOG("This system supports OpenGL Version %s.\n", oglVersion);

		OSVERSIONINFO osvi = { 0 };
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (!GetVersionEx(&osvi))
		{
			DLOG("GetVersionEx() Error.\n");
		}


		// Now that extensions are setup, delete window and start over picking a real format.
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext((HGLRC)pDriverData->OpenGLWin32.HRc);
		ReleaseDC((HWND)pDriverData->OpenGLWin32.HWnd, (HDC)pDriverData->OpenGLWin32.HDc);
		DestroyWindow((HWND)pDriverData->OpenGLWin32.HWnd);

		// Create the window again
		pDriverData->OpenGLWin32.HWnd = CreateWindowEx(dwExtStyle,     // Extended style
			szClassName,    // class name
			szWindowName,   // window name
			dwWindStyle |
			WS_CLIPSIBLINGS |
			WS_CLIPCHILDREN,// window stlye
			nWindowX,       // window position, x
			nWindowY,       // window position, y
			pDriverData->WindowWidth,   // height
			pDriverData->WindowHeight,  // width
			NULL,           // Parent window
			NULL,           // menu
			g_hInstance,    // instance
			NULL);          // pass this to WM_CREATE

		pDriverData->OpenGLWin32.HDc = GetDC((HWND)pDriverData->OpenGLWin32.HWnd);

		int nPixCount = 0;

		// Specify the important attributes we care about
		int pixAttribs[] = { WGL_SUPPORT_OPENGL_ARB, 1, // Must support OGL rendering
			WGL_DRAW_TO_WINDOW_ARB, 1, // pf that can run a window
			WGL_ACCELERATION_ARB, 1, // must be HW accelerated
			WGL_RED_BITS_ARB, 8, // 8 bits of red precision in window
			WGL_GREEN_BITS_ARB, 8, // 8 bits of green precision in window
			WGL_BLUE_BITS_ARB, 8, // 8 bits of blue precision in window
			WGL_DEPTH_BITS_ARB, 16, // 16 bits of depth precision for window
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB, // pf should be RGBA type
			WGL_TRANSPARENT_ALPHA_VALUE_ARB, 1,
			0 }; // NULL termination

		// Ask OpenGL to find the most relevant format matching our attribs
		// Only get one format back.

		wglChoosePixelFormatARB((HDC)pDriverData->OpenGLWin32.HDc, &pixAttribs[6], NULL, 1, &nPixelFormat, (UINT*)&nPixCount);

		if (nPixelFormat == -1)
		{
			// Couldn't find a format, perhaps no 3D HW or drivers are installed
			pDriverData->OpenGLWin32.HDc = 0;
			pDriverData->OpenGLWin32.HRc = 0;
			bRetVal = false;
			DLOG("!!! An error occurred trying to find a pixel format with the requested attribs.\n");
		}
		else
		{
			// Got a format, now set it as the current one
			BOOL bRet = SetPixelFormat((HDC)pDriverData->OpenGLWin32.HDc, nPixelFormat, &pfd);

			GLint attribs[] = { WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
				WGL_CONTEXT_MINOR_VERSION_ARB, 3,
				WGL_CONTEXT_FLAGS_ARB, 0,
				0 };

			pDriverData->OpenGLWin32.HRc = wglCreateContextAttribsARB((HDC)pDriverData->OpenGLWin32.HDc, 0, attribs);

			if (pDriverData->OpenGLWin32.HRc == NULL)
			{
				DLOG("%d\n", glGetError());
				DLOG("!!! Could not create an OpenGL 3.3 context.\n");
				attribs[3] = 2;
				pDriverData->OpenGLWin32.HRc = wglCreateContextAttribsARB((HDC)pDriverData->OpenGLWin32.HDc, 0, attribs);
				if (pDriverData->OpenGLWin32.HRc == NULL)
				{
					DLOG("%d\n", glGetError());
					DLOG("!!! Could not create an OpenGL 3.2 context.\n");
					attribs[3] = 1;
					pDriverData->OpenGLWin32.HRc = wglCreateContextAttribsARB((HDC)pDriverData->OpenGLWin32.HDc, 0, attribs);
					if (pDriverData->OpenGLWin32.HRc == NULL)
					{
						DLOG("%d\n", glGetError());
						DLOG("!!! Could not create an OpenGL 3.1 context.\n");
						attribs[3] = 0;
						pDriverData->OpenGLWin32.HRc = wglCreateContextAttribsARB((HDC)pDriverData->OpenGLWin32.HDc, 0, attribs);
						if (pDriverData->OpenGLWin32.HRc == NULL)
						{
							DLOG("%d\n", glGetError());
							DLOG("!!! Could not create an OpenGL 3.0 context.\n");
							DLOG("!!! OpenGL 3.0 and higher are not supported on this system.\n");
						}
					}
				}
			}

			wglMakeCurrent((HDC)pDriverData->OpenGLWin32.HDc, (HGLRC)pDriverData->OpenGLWin32.HRc);
		}
		*/
/*
		if (pDriverData->OpenGLWin32.HDc == 0 ||
			pDriverData->OpenGLWin32.HRc == 0)
		{
			bRetVal = false;
			DLOG("!!! An error occured creating an OpenGL window.\n");
		}

		// If everything went as planned, display the window 
		if (bRetVal)
		{
			::ShowWindow((HWND)pDriverData->OpenGLWin32.HWnd, SW_SHOW);
			::SetForegroundWindow((HWND)pDriverData->OpenGLWin32.HWnd);
			::SetFocus((HWND)pDriverData->OpenGLWin32.HWnd);


			::UpdateWindow((HWND)pDriverData->OpenGLWin32.HWnd);
			if (!(HWND)pDriverData->OpenGLWin32.HWnd)
			{
				DLOG("UpdateWindow() error:%d\n", GetLastError());
				bRetVal = false;
			}

		}
		*/
		return bRetVal;
	}

	void OpenGLDriver::Begin(IVideoData *pVideoData)
	{

	}

	void OpenGLDriver::End()
	{

	}

	void OpenGLDriver::Draw()
	{

	}

}