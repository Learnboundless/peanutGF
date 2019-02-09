#include "BasicWin.h"
#include <iostream>
namespace pnGF{

	BasicWin::BasicWin()
	{

	}


	BasicWin::~BasicWin()
	{
	}

	BasicWin & BasicWin::Instance()
	{
		static BasicWin instance;
		return instance;
	}

	int BasicWin::GetState()
	{
		//此处暂时使用简单返回值表示状态
		return 42;
	}

	HWND BasicWin::RunWindow(string jsonPath)
	{
		HINSTANCE hInstance = GetModuleHandle(0);
		ATOM res = RegisterClassEx(&readRegInfo(jsonPath));
		if (res == 0)
		{
			//MessageBox(hWindow,GetLastError())
		}
		InitInstance(hInstance, SW_SHOWNORMAL);
		return hWindow;
	}

	float BasicWin::GetFPS()
	{
		//定义四个静态变量
		static float  fps = 0; //我们需要计算的FPS值
		static int    frameCount = 0;//帧数
		static float  currentTime = 0.0f;//当前时间
		static float  lastTime = 0.0f;//持续时间

		frameCount++;//每调用一次Get_FPS()函数，帧数自增1
		currentTime = timeGetTime()*0.001f;//获取系统时间，其中timeGetTime函数返回的是以毫秒为单位的系统时间，所以需要乘以0.001，得到单位为秒的时间

		//如果当前时间减去持续时间大于了1秒钟，就进行一次FPS的计算和持续时间的更新，并将帧数值清零
		if (currentTime - lastTime > 1.0f) //将时间控制在1秒钟
		{
			fps = (float)frameCount / (currentTime - lastTime);//计算这1秒钟的FPS值
			lastTime = currentTime; //将当前时间currentTime赋给持续时间lastTime，作为下一秒的基准时间
			frameCount = 0;//将本次帧数frameCount值清零
		}
		return fps;
	}

	RECT BasicWin::GetScreenInfo()
	{
		RECT res;
		res.left = res.top = 0;
		res.bottom = height;
		res.right = width;
		return res;
	}

	WNDCLASSEX & BasicWin::readRegInfo(string jsonFilePath)
	{
		//读取Json数据使用的变量
		Json::Reader reader;
		Json::Value root; //可以代表任意C++数据类型
		std::ifstream is;
		is.open(jsonFilePath.c_str(), ios::binary);
		if (reader.parse(is,root,FALSE))
		{
			
			wndclass.style = CS_HREDRAW | CS_VREDRAW;
			wndclass.lpfnWndProc = (WNDPROC)DefaultProc;
			wndclass.cbClsExtra = 0;
			wndclass.cbWndExtra = 0;
			wndclass.hInstance = GetModuleHandle(0);
			wndclass.hIcon = NULL;
			wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
			wndclass.hbrBackground = (HBRUSH)GetStockObject(0);
			wndclass.lpszMenuName = NULL;
			swTitle = root.get("标题", "pnGF").asString();
			wndclass.lpszClassName = swTitle.c_str();
			wndclass.hIconSm = NULL;
			wndclass.cbSize = sizeof(WNDCLASSEX);
			width = root.get("宽", "640").asInt();
			height = root.get("高", "640").asInt();
		}

		is.close();
		return wndclass;
	}

	BOOL BasicWin::InitInstance(HINSTANCE hInstance, int nCmdShow)
	{
		std::cout << "创建窗口中...." << std::endl;
		hWindow = CreateWindow(
			swTitle.c_str(),
			swTitle.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			width, height,
			NULL,NULL,
			hInstance,
			NULL
		);
		if (hWindow==0)
		{
			MessageBox(hWindow, TEXT("窗口创建失败"), TEXT("失败"), MB_OK);
			return 0;
		}
		ShowWindow(hWindow, nCmdShow);
		UpdateWindow(hWindow);
		device = GetDC(hWindow);
		return 1;
	}

	LRESULT CALLBACK DefaultProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_LBUTTONDOWN:
			BWind.mouseClick = !BWind.mouseClick;
			break;
		case WM_LBUTTONUP:
			BWind.mouseClick = !BWind.mouseClick;
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}


}