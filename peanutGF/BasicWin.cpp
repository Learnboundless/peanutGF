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
		//�˴���ʱʹ�ü򵥷���ֵ��ʾ״̬
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
		//�����ĸ���̬����
		static float  fps = 0; //������Ҫ�����FPSֵ
		static int    frameCount = 0;//֡��
		static float  currentTime = 0.0f;//��ǰʱ��
		static float  lastTime = 0.0f;//����ʱ��

		frameCount++;//ÿ����һ��Get_FPS()������֡������1
		currentTime = timeGetTime()*0.001f;//��ȡϵͳʱ�䣬����timeGetTime�������ص����Ժ���Ϊ��λ��ϵͳʱ�䣬������Ҫ����0.001���õ���λΪ���ʱ��

		//�����ǰʱ���ȥ����ʱ�������1���ӣ��ͽ���һ��FPS�ļ���ͳ���ʱ��ĸ��£�����֡��ֵ����
		if (currentTime - lastTime > 1.0f) //��ʱ�������1����
		{
			fps = (float)frameCount / (currentTime - lastTime);//������1���ӵ�FPSֵ
			lastTime = currentTime; //����ǰʱ��currentTime��������ʱ��lastTime����Ϊ��һ��Ļ�׼ʱ��
			frameCount = 0;//������֡��frameCountֵ����
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
		//��ȡJson����ʹ�õı���
		Json::Reader reader;
		Json::Value root; //���Դ�������C++��������
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
			swTitle = root.get("����", "pnGF").asString();
			wndclass.lpszClassName = swTitle.c_str();
			wndclass.hIconSm = NULL;
			wndclass.cbSize = sizeof(WNDCLASSEX);
			width = root.get("��", "640").asInt();
			height = root.get("��", "640").asInt();
		}

		is.close();
		return wndclass;
	}

	BOOL BasicWin::InitInstance(HINSTANCE hInstance, int nCmdShow)
	{
		std::cout << "����������...." << std::endl;
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
			MessageBox(hWindow, TEXT("���ڴ���ʧ��"), TEXT("ʧ��"), MB_OK);
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