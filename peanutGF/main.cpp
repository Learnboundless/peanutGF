#include "BasicWin.h"
#include <iostream>
#include <windows.h>
#include "Cgdi.h"
#include <d3dx9.h>
#include <math.h>
#include <time.h>
#include "easyDx.h"
#include "Text.h"
using namespace pnGF;

#define SAFE_RELEASE(p) {if(p) { (p)->Release(); (p)=NULL; }}

int pastFrame = 0;

void FixedFrameTimeSleep(int frameTime) {
	static clock_t endClock = 0;
	pastFrame++;
	endClock += frameTime * CLOCKS_PER_SEC / 1000;
	if (clock()>endClock)
	{
		endClock = clock();
	}
	else {
		while (clock()<endClock)
		{
			Sleep(1);
		}
	}
}
float GetFPS()
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
void GDI_Render();
//GDI��Ϸ����
int radius = 10;
float theat = 0.0f;
bool isReturn = false;
int pastFrames = 0;

//Dx��������
HWND hWin;

//�����Ϣ��ȡ[Test]
POINT cursorPos;



int main() {
	std::cout << "��ʼ������Ϸ����" << std::endl;
	MSG msg;
	bool gameOver = false;
	//HWND hWin2 = BWind.RunWindow("Test.json");
	hWin = BWind.RunWindow("Test.json");
	HDC hdc = GetDC(hWin);
	Text mytest("��ʼ",-10,-25, D3DCOLOR_XRGB(100,100,200));
	Text mytest3("��3", 50, 22, D3DCOLOR_XRGB(0, 255, 120), 2);
	Text mytest2("��2", 50, 12, D3DCOLOR_XRGB(255, 0, 0),2);
	
	//HDC gdihdc = GetDC(hWin2);
/*
	if (S_OK== Direct3D_Init(hWin))
	{
		MessageBox(hWin, "DxInit Ok!", "DxOK", MB_OK);
	}*/
	if (S_OK==eDx->Init(hWin))
	{
		MessageBox(hWin, "DxInit Ok!", "DxOK", MB_OK);
	}
	
	//gdi->StartDrawing(gdihdc);
	mgdi->DoubleBuffer(true);
	PlaySound("Reynard Silva - Every Time.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (!gameOver)
	{
		
		GetCursorPos(&cursorPos);
		//std::cout << "���λ��(��Ļ����ϵ)��Ϣ����("<< cursorPos.x<<","<<cursorPos.y<<")"<<std::endl;
		ScreenToClient(hWin, &cursorPos);
		//std::cout << "���λ��(�ͻ�������ϵ)��Ϣ����(" << cursorPos.x << "," << cursorPos.y << ")" << std::endl;
		//std::cout <<"FPSֵ:"<< BWind.GetFPS() << std::endl;
		mytest.SetFontText("FPS:"+to_string((int)GetFPS()));
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//GDI_Render();
			eDx->RenderModle();
			//Direct3D_Render(hWin);
			//Sleep(33.3);
			FixedFrameTimeSleep(10);
			//system("cls"); 
		}
	}
	//gdi->StopDrawing(gdihdc);
	return msg.wParam;
}

void GDI_Render() {
	if (BWind.mouseClick)
	{
		bool isInside = InsideRegion(POINTtoVector(cursorPos), Vector2D(600 - radius, 255 - radius), Vector2D(600 + radius, 255 + radius));
		if (isInside)
		{
			gdi->TextAtPos(Vector2D(600, 450), "�������Բ��");
			std::cout << "�������Բ��" << POINTtoVector(cursorPos) << std::endl;
			PlaySound("Reynard Silva - Every Time.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
	}

	//ˢ����Ϸ
	if (radius < 140 && !isReturn)
	{
		radius += 1;
	}
	else {
		isReturn = true;
	}

	if (isReturn)
	{
		radius -= 1;
		if (radius < 0)
		{
			isReturn = false;
		}
	}

	theat += 0.1;
	//theat = 360 % theat;


	gdi->SetBrushColor(gdi->white);
	gdi->SetPenColor(gdi->red);
	gdi->Line(Vector2D(20, 50), Vector2D(60, 80));
	//gdi->SetPenColor(gdi->brown);
	gdi->Line(Vector2D(180, 20), Vector2D(250, 150));
	mgdi->LineWithArrow(Vector2D(180, 180), Vector2D(180, 179), 20);
	mgdi->TransparentText();
	mgdi->TextColor(mgdi->blue);
	mgdi->TextAtPos(Vector2D(188, 180), "����һ����ͷ");

	mgdi->Circle(Vector2D(600, 250), 150);
	gdi->SetBrushColor(gdi->red);
	mgdi->Circle(Vector2D(600, 250), radius);
	mgdi->TextAtPos(Vector2D(600, 255), "Բ��");
	gdi->SetPenColor(gdi->blue);
	mgdi->Line(Vector2D(600, 255), Vector2D(600 + sin(theat)*radius, 255 + cos(theat)*radius));
	//��������
	gdi->SetBrushColor(gdi->blue);
	mgdi->Circle(Vector2D(600 + sin(theat)*radius, 255 + cos(theat)*radius), 15);

	string fps = "GDI����___FPS:";
	fps += to_string((int)GetFPS());
	mgdi->TextAtPos(Vector2D(0, 500), fps);

	string frames = "GDI����___������֡��:";
	frames += to_string(++pastFrames);
	mgdi->TextAtPos(Vector2D(0, 525), frames);
	//
	mgdi->CopyOffBuffer(hWin);
	//�����Ļ
	mgdi->RefreshScreen(hWin);
}
