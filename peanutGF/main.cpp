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
void GDI_Render();
//GDI游戏数据
int radius = 10;
float theat = 0.0f;
bool isReturn = false;
int pastFrames = 0;

//Dx绘制数据
HWND hWin;

//鼠标信息获取[Test]
POINT cursorPos;



int main() {
	std::cout << "开始创建游戏窗口" << std::endl;
	MSG msg;
	bool gameOver = false;
	//HWND hWin2 = BWind.RunWindow("Test.json");
	hWin = BWind.RunWindow("Test.json");
	HDC hdc = GetDC(hWin);
	Text mytest("开始",-10,-25, D3DCOLOR_XRGB(100,100,200));
	Text mytest3("层3", 50, 22, D3DCOLOR_XRGB(0, 255, 120), 2);
	Text mytest2("层2", 50, 12, D3DCOLOR_XRGB(255, 0, 0),2);
	
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
		//std::cout << "鼠标位置(屏幕坐标系)信息捕获("<< cursorPos.x<<","<<cursorPos.y<<")"<<std::endl;
		ScreenToClient(hWin, &cursorPos);
		//std::cout << "鼠标位置(客户端坐标系)信息捕获(" << cursorPos.x << "," << cursorPos.y << ")" << std::endl;
		//std::cout <<"FPS值:"<< BWind.GetFPS() << std::endl;
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
			gdi->TextAtPos(Vector2D(600, 450), "鼠标点击了圆心");
			std::cout << "鼠标点击了圆心" << POINTtoVector(cursorPos) << std::endl;
			PlaySound("Reynard Silva - Every Time.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
	}

	//刷新游戏
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
	mgdi->TextAtPos(Vector2D(188, 180), "这是一个箭头");

	mgdi->Circle(Vector2D(600, 250), 150);
	gdi->SetBrushColor(gdi->red);
	mgdi->Circle(Vector2D(600, 250), radius);
	mgdi->TextAtPos(Vector2D(600, 255), "圆心");
	gdi->SetPenColor(gdi->blue);
	mgdi->Line(Vector2D(600, 255), Vector2D(600 + sin(theat)*radius, 255 + cos(theat)*radius));
	//绘制链球
	gdi->SetBrushColor(gdi->blue);
	mgdi->Circle(Vector2D(600 + sin(theat)*radius, 255 + cos(theat)*radius), 15);

	string fps = "GDI文字___FPS:";
	fps += to_string((int)GetFPS());
	mgdi->TextAtPos(Vector2D(0, 500), fps);

	string frames = "GDI文字___经过的帧数:";
	frames += to_string(++pastFrames);
	mgdi->TextAtPos(Vector2D(0, 525), frames);
	//
	mgdi->CopyOffBuffer(hWin);
	//清空屏幕
	mgdi->RefreshScreen(hWin);
}
