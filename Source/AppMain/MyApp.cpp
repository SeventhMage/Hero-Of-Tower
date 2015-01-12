#include "MyApp.h"
#include "../../XEng/Video/DriverData.h"
#include "../../XEng/Video/IVideoDriver.h"
#include "../../XEng/Video/OpenGL/OpenGLDriver.h"


#include "../../XEng/Video/OpenGL/GLShaderManager.h"
#include "../../XEng/Video/OpenGL/GLBatch.h"

using namespace xeng;

GLShaderManager		shaderManager;

GLBatch             triangleBatch;


int g_iWidth;
int g_iHeight;

MainWindow::MainWindow(LPCTSTR lpWindowName) :Window(lpWindowName)
{
	m_mapMsgFun[WM_COMMAND] = (PMSGFUN)&MainWindow::OnCommand;
	m_mapMsgFun[WM_PAINT] = (PMSGFUN)&MainWindow::OnDraw;
	m_mapMsgFun[WM_SIZE] = (PMSGFUN)&MainWindow::OnSize;

}
MainWindow::~MainWindow()
{
}

void MainWindow::AddControl()
{

	DriverData driverData;
	driverData.WindowWidth = 960;
	driverData.WindowHeight = 640;
	driverData.OpenGLWin32.HWnd = GetHandle();

	IVideoDriver *pDriver = new OpenGLDriver();
	pDriver->Init(&driverData);
}

void MainWindow::OnCommand(WPARAM wParam, LPARAM lParam)
{
	;
}

void MainWindow::OnDraw(WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(GetHandle(), &ps);



	EndPaint(GetHandle(), &ps);
}

void MainWindow::OnSize(WPARAM wParam, LPARAM lParam)
{
	m_uWidth = LOWORD(lParam);
	m_uHeight = HIWORD(lParam);
	glViewport(0, 0, m_uWidth, m_uHeight);
}

void MainWindow::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
	triangleBatch.Draw();

	// Perform the buffer swap to display back buffer

	HDC hdc = GetDC(GetHandle());
	SwapBuffers(hdc);
	ReleaseDC(GetHandle(), hdc);
	
}

void MainWindow::Init()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	shaderManager.InitializeStockShaders();

	// Load up a triangle
	GLfloat vVerts[] = { -0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f };

	triangleBatch.Begin(GL_TRIANGLES, 3);
	triangleBatch.CopyVertexData3f(vVerts);
	triangleBatch.End();
}

/////////////////////////////////////////////////////
//MyApp
/////////////////////////////////////////////////////
MyApp::MyApp()
{
	m_pMainWindow = new MainWindow("ÎÞ±êÌâ");
	assert(m_pMainWindow);
}

MyApp::~MyApp()
{

}


void MyApp::AddControl()
{
	m_pMainWindow->SetStyle(WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME);
	m_pMainWindow->SetWidth(MAINWIDTH);
	m_pMainWindow->SetHeight(MAINHEIGHT);
	HANDLE hWnd = ShowWindow(m_pMainWindow);
	WaitForSingleObject(hWnd, INFINITE);
	CloseHandle(hWnd);
}
