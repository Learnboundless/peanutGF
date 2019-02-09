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
		//���õ���ģʽʵ����
		static BasicWin &Instance();
		int GetState();
	public:
		//���п��
		HWND RunWindow(string jsonPath);
		//��ȡˢ��Ƶ��
		float GetFPS();
		//��ȡ��Ļ�ֱ���
		RECT GetScreenInfo();
		//����¼�
		bool mouseClick = false;
	private:
		//��ָ��·���ж�ȡ����ע������Ҫ����Ϣ
		WNDCLASSEX & readRegInfo(string jsonFilePath);
		BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
	private:
		int imState;
		//�����������
		HWND hWindow;
		HDC device;
		string swTitle;
		WNDCLASSEX wndclass;
		int width, height;
		
	};


}
