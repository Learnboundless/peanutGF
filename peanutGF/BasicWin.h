#pragma once

#include <windows.h>
#include <json/json.h>
#include <fstream>

using namespace std;

namespace pnGF{

LRESULT CALLBACK DefaultProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#define BWind BasicWin::Instance()

class BasicWin
	{
	private:
		BasicWin();
		virtual ~BasicWin();
		BasicWin(const BasicWin &);
		const BasicWin &operator =(const BasicWin &);
	public:
		//采用单例模式实现它
		static BasicWin &Instance();
		int GetState();
	public:
		//运行框架
		HWND RunWindow(string jsonPath);
		//获取刷新频率
		float GetFPS();
		//获取屏幕分辨率
		RECT GetScreenInfo();
		//鼠标事件
		bool mouseClick = false;
	private:
		//从指定路径中读取窗口注册所需要的信息
		WNDCLASSEX & readRegInfo(string jsonFilePath);
		BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
	private:
		int imState;
		//窗口申请相关
		HWND hWindow;
		HDC device;
		string swTitle;
		WNDCLASSEX wndclass;
		int width, height;
		
	};


}
