#include "BasicWin.h"
#include <iostream>
#include <windows.h>
#include "Cgdi.h"

using namespace pnGF;

int main() {
	std::cout << "开始创建游戏窗口" << std::endl;
	MSG msg;
	bool gameOver = false;
	HWND hWin = BWind.RunWindow("Test.json");
	HDC hdc = GetDC(hWin);
	
	gdi->StartDrawing(hdc);
	gdi->SetPenColor(gdi->red);
	gdi->Line(Vector2D(20, 50), Vector2D(60, 80));
	//gdi->SetPenColor(gdi->brown);
	gdi->Line(Vector2D(180, 20), Vector2D(250, 150));
	mgid->LineWithArrow(Vector2D(180, 180), Vector2D(180, 179), 20);
	mgid->TransparentText();
	mgid->TextColor(mgid->blue);
	mgid->TextAtPos(Vector2D(188, 180),"这是一个箭头");
	mgid->Circle(Vector2D(600, 250), 150);
	mgid->Circle(Vector2D(600, 250), 3);
	mgid->TextAtPos(Vector2D(600, 255), "圆心");

	//鼠标信息获取[Test]
	POINT cursorPos;
	HCURSOR cursorInfo;
	while (!gameOver)
	{
		//刷新世界
		mgid->RefreshScreen(hWin);

		GetCursorPos(&cursorPos);
		std::cout << "鼠标位置(屏幕坐标系)信息捕获("<< cursorPos.x<<","<<cursorPos.y<<")"<<std::endl;
		ScreenToClient(hWin, &cursorPos);
		std::cout << "鼠标位置(客户端坐标系)信息捕获(" << cursorPos.x << "," << cursorPos.y << ")" << std::endl;
		std::cout <<"FPS值:"<< BWind.GetFPS() << std::endl;
		
		
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (BWind.mouseClick)
		{
			bool isInside = InsideRegion(POINTtoVector(cursorPos), Vector2D(597, 252), Vector2D(603, 258));
			if (isInside)
			{
				gdi->TextAtPos(Vector2D(600, 380),"鼠标点击了圆心");
				std::cout << "鼠标点击了圆心"<< POINTtoVector(cursorPos) << std::endl;
			}
		}
		system("cls");
	}
	return msg.wParam;
}
