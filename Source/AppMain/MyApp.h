#ifndef MYAPP_H_
#define MYAPP_H_


#include <time.h>
#include "../Win32/Window.h"
#include "../Win32/Application.h"



#define MAINWIDTH 960
#define MAINHEIGHT 640


class MainWindow :public Window
{
public:
	MainWindow(LPCTSTR lpWindowName = "�ޱ���");
	virtual ~MainWindow();
public:
	virtual void AddControl();
	virtual void Update();
public:
	//��Ϣ
	void OnCommand(WPARAM wParam, LPARAM lParam);
	void OnDraw(WPARAM wParam, LPARAM lParam);
	void OnSize(WPARAM wParam, LPARAM lParam);
public:
	//�ؼ�
private:
	HDC m_hdc;
	unsigned int m_uWidth;
	unsigned int m_uHeight;
};



class MyApp :public Application
{
public:
	MyApp();
	virtual ~MyApp();
public:
	virtual void AddControl();
private:
	MainWindow *m_pMainWindow;
};

#endif