#include "BasicWin.h"
#include <iostream>
#include <windows.h>
#include "Cgdi.h"
#include <d3dx9.h>
#include <math.h>
#include <time.h>
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
LPDIRECT3DDEVICE9 g_pd3dDevice;
HRESULT Direct3D_Init(HWND hwnd);
HRESULT Objects_Init(HWND hwnd); //资源初始化
VOID Direct3D_Render(HWND hwnd);//渲染代码
VOID Direct3D_CleanUp();

void GDI_Render();
//GDI游戏数据
int radius = 10;
float theat = 0.0f;
bool isReturn = false;
int pastFrames = 0;



//Dx绘制数据
HWND hWin;
//字体
LPD3DXFONT ppFont;


//鼠标信息获取[Test]
POINT cursorPos;



int main() {
	std::cout << "开始创建游戏窗口" << std::endl;
	MSG msg;
	bool gameOver = false;
	hWin = BWind.RunWindow("Test.json");
	HDC hdc = GetDC(hWin);
	if (S_OK== Direct3D_Init(hWin))
	{
		MessageBox(hWin, "DxInit Ok!", "DxOK", MB_OK);
	}
	
	
	gdi->StartDrawing(hdc);
	mgdi->DoubleBuffer(true);

	while (!gameOver)
	{
		GetCursorPos(&cursorPos);
		//std::cout << "鼠标位置(屏幕坐标系)信息捕获("<< cursorPos.x<<","<<cursorPos.y<<")"<<std::endl;
		ScreenToClient(hWin, &cursorPos);
		//std::cout << "鼠标位置(客户端坐标系)信息捕获(" << cursorPos.x << "," << cursorPos.y << ")" << std::endl;
		//std::cout <<"FPS值:"<< BWind.GetFPS() << std::endl;
		
		
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//GDI_Render();
			Direct3D_Render(hWin);
			//Sleep(33.3);
			FixedFrameTimeSleep(30);
			//system("cls"); 
		}
	}
	gdi->StopDrawing(hdc);
	return msg.wParam;
}

HRESULT Direct3D_Init(HWND hwnd) {
	//创建设备接口
	LPDIRECT3D9 pD3D = NULL;
	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}
	D3DCAPS9 caps;
	int vp = 0;
	if (FAILED(pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		return E_FAIL;
	}
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING; //顶点运算
	}
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	//填写内容
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = BWind.GetScreenInfo().right;
	d3dpp.BackBufferHeight = BWind.GetScreenInfo().bottom;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 2;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	//创建设备
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hwnd, vp, &d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(pD3D);
	if (!(S_OK == Objects_Init(hwnd)))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT Objects_Init(HWND hwnd) {
	if (S_OK == D3DXCreateFont(g_pd3dDevice, 18, 16, 3, 5, TRUE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0,
		"微软雅黑", &ppFont))
	{
		//MessageBox(hWin, "Font Ok!", "DxOK", MB_OK);
	}
	

	return S_OK;
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
	mgdi->TextColor(mgid->blue);
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
	fps += to_string((int)BWind.GetFPS());
	mgdi->TextAtPos(Vector2D(0, 500), fps);

	string frames = "GDI文字___经过的帧数:";
	frames += to_string(++pastFrames);
	mgdi->TextAtPos(Vector2D(0, 525), frames);
	//
	mgdi->CopyOffBuffer(hWin);
	//清空屏幕
	mgdi->RefreshScreen(hWin);
}

VOID Direct3D_Render(HWND hwnd) {
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	g_pd3dDevice->BeginScene();

	RECT resPos = BWind.GetScreenInfo();

	//实际绘制代码
	resPos.top = 5;
	string fps = "FPS:";
	fps += to_string((int)BWind.GetFPS());
	ppFont->DrawText(0, fps.c_str(), fps.size(), &resPos, DT_LEFT, D3DCOLOR_XRGB(rand() % 25 + 230, rand() % 128 + 127, rand() % 50 + 200));
	resPos.top = 250;
	ppFont->DrawText(0, ("Skill Begin!"), -1, &resPos, DT_CENTER, D3DCOLOR_XRGB(rand() % 255, rand() % 128, rand() % 225));
	resPos.top = 350;
	ppFont->DrawText(0, ("GamePrograming I am Coming Again!"), -1, &resPos, DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));

	g_pd3dDevice->EndScene();
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}