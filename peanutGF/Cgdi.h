#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <cassert>

#include "vector2D.h"


namespace pnGF{
//  Author: [1/30/2019 CodeLoser]	
//  文件名: Cgdi.h
//	描述: 这是一个单例模式的GDI封装类

	//定义颜色常量
	const int NumColors = 15;

	const COLORREF colors[NumColors] = {
		RGB(255,0,0),
		RGB(0, 0, 255),
		RGB(0,255,0),
		RGB(0,0,0),
		RGB(255,200,200),
		RGB(200,200,200),
		RGB(255,255,0),
		RGB(255,0,170),
		RGB(133,90,0),
		RGB(255,255,255),
		RGB(0,100,0),
		RGB(0,255,255),
		RGB(200,200,200),
		RGB(255,230,230)
	};

	#define gdi Cgdi::Instance()
	
	class Cgdi
	{
	public:
		int NumPenColors()const { return NumColors; }
		//枚举颜色
		enum 
		{
			red,
			blue,
			green,
			black,
			pink,
			grey,
			yellow,
			orange,
			purple,
			brown,
			white,
			dark_green,
			light_blue,
			light_grey,
			light_pink,
			hollow
		};
	private:
		HPEN m_OldPen;

		//所有类型的画笔
		HPEN   m_BlackPen;
		HPEN   m_WhitePen;
		HPEN   m_RedPen;
		HPEN   m_GreenPen;
		HPEN   m_BluePen;
		HPEN   m_GreyPen;
		HPEN   m_PinkPen;
		HPEN   m_OrangePen;
		HPEN   m_YellowPen;
		HPEN   m_PurplePen;
		HPEN   m_BrownPen;

		HPEN   m_DarkGreenPen;
		HPEN   m_LightBluePen;
		HPEN   m_LightGreyPen;
		HPEN   m_LightPinkPen;

		HPEN   m_ThickBlackPen;
		HPEN   m_ThickWhitePen;
		HPEN   m_ThickRedPen;
		HPEN   m_ThickGreenPen;
		HPEN   m_ThickBluePen;

		HBRUSH m_OldBrush;

		//所有的画刷
		HBRUSH  m_RedBrush;
		HBRUSH  m_GreenBrush;
		HBRUSH  m_BlueBrush;
		HBRUSH  m_GreyBrush;
		HBRUSH  m_BrownBrush;
		HBRUSH  m_YellowBrush;
		HBRUSH  m_OrangeBrush;

		HBRUSH  m_LightBlueBrush;
		HBRUSH  m_DarkGreenBrush;

		HDC    m_hdc;

		Cgdi();

		Cgdi(const Cgdi&);
		Cgdi& operator=(const Cgdi&);

		void BlackPen() { if (m_hdc) { SelectObject(m_hdc, m_BlackPen); } }
		void WhitePen() { if (m_hdc) { SelectObject(m_hdc, m_WhitePen); } }
		void RedPen() { if (m_hdc) { SelectObject(m_hdc, m_RedPen); } }
		void GreenPen() { if (m_hdc) { SelectObject(m_hdc, m_GreenPen); } }
		void BluePen() { if (m_hdc) { SelectObject(m_hdc, m_BluePen); } }
		void GreyPen() { if (m_hdc) { SelectObject(m_hdc, m_GreyPen); } }
		void PinkPen() { if (m_hdc) { SelectObject(m_hdc, m_PinkPen); } }
		void YellowPen() { if (m_hdc) { SelectObject(m_hdc, m_YellowPen); } }
		void OrangePen() { if (m_hdc) { SelectObject(m_hdc, m_OrangePen); } }
		void PurplePen() { if (m_hdc) { SelectObject(m_hdc, m_PurplePen); } }
		void BrownPen() { if (m_hdc) { SelectObject(m_hdc, m_BrownPen); } }

		void DarkGreenPen() { if (m_hdc) { SelectObject(m_hdc, m_DarkGreenPen); } }
		void LightBluePen() { if (m_hdc) { SelectObject(m_hdc, m_LightBluePen); } }
		void LightGreyPen() { if (m_hdc) { SelectObject(m_hdc, m_LightGreyPen); } }
		void LightPinkPen() { if (m_hdc) { SelectObject(m_hdc, m_LightPinkPen); } }

		void ThickBlackPen() { if (m_hdc) { SelectObject(m_hdc, m_ThickBlackPen); } }
		void ThickWhitePen() { if (m_hdc) { SelectObject(m_hdc, m_ThickWhitePen); } }
		void ThickRedPen() { if (m_hdc) { SelectObject(m_hdc, m_ThickRedPen); } }
		void ThickGreenPen() { if (m_hdc) { SelectObject(m_hdc, m_ThickGreenPen); } }
		void ThickBluePen() { if (m_hdc) { SelectObject(m_hdc, m_ThickBluePen); } }

		void BlackBrush() { if (m_hdc)SelectObject(m_hdc, GetStockObject(BLACK_BRUSH)); }
		void WhiteBrush() { if (m_hdc)SelectObject(m_hdc, GetStockObject(WHITE_BRUSH)); }
		void HollowBrush() { if (m_hdc)SelectObject(m_hdc, GetStockObject(HOLLOW_BRUSH)); }
		void GreenBrush() { if (m_hdc)SelectObject(m_hdc, m_GreenBrush); }
		void RedBrush() { if (m_hdc)SelectObject(m_hdc, m_RedBrush); }
		void BlueBrush() { if (m_hdc)SelectObject(m_hdc, m_BlueBrush); }
		void GreyBrush() { if (m_hdc)SelectObject(m_hdc, m_GreyBrush); }
		void BrownBrush() { if (m_hdc)SelectObject(m_hdc, m_BrownBrush); }
		void YellowBrush() { if (m_hdc)SelectObject(m_hdc, m_YellowBrush); }
		void LightBlueBrush() { if (m_hdc)SelectObject(m_hdc, m_LightBlueBrush); }
		void DarkGreenBrush() { if (m_hdc)SelectObject(m_hdc, m_DarkGreenBrush); }
		void OrangeBrush() { if (m_hdc)SelectObject(m_hdc, m_OrangeBrush); }
	public:
		
		~Cgdi();

		static Cgdi* Instance();

		///-------------------------
		/// 函数名:  StartDrawing
		/// 参数:	HDC 环境设备句柄
		/// 返回值:  -void
		/// 说明:  在每次绘制前都调用此方法
		void StartDrawing(HDC hdc) {
			assert(m_hdc == NULL);

			m_hdc = hdc;

			//获得当前画笔
			m_OldPen = (HPEN)SelectObject(hdc, m_BlackPen);

			SelectObject(hdc, m_OldPen);

			m_OldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));
			SelectObject(hdc, m_OldBrush);
		}


		///-------------------------
		/// 函数名:  StopDrawing
		/// 参数: HDC 环境设备句柄
		/// 返回值:  -void
		void StopDrawing(HDC hdc) {
			assert(hdc != NULL);
			SelectObject(hdc, m_OldPen);
			SelectObject(hdc, m_OldBrush);
			m_hdc = NULL;
		}

		//文本绘制相关

		//-------------------------
		// 函数名:  TextAtPos
		// 参数: 位置信息, 字符内容
		// 返回值:  void
		void TextAtPos(int x, int y, const std::string &str) {
			TextOut(m_hdc, x, y, str.c_str(), (int)str.size());
		}

		//-------------------------
		// 函数名:  TextAtPos
		// 参数: 位置信息, 字符内容
		// 返回值:  void
		void TextAtPos(double x, double y, const std::string &str) {
			TextOut(m_hdc, (int)x, (int)y, str.c_str(), (int)str.size());
		}
		//-------------------------
		// 函数名:  TextAtPos
		// 参数: 位置信息, 字符内容
		// 返回值:  void
		void TextAtPos(Vector2D pos, const std::string &str) {
			TextOut(m_hdc, (int)pos.x, (int)pos.y, str.c_str(), (int)str.size());
		}

		void TransparentText() { SetBkMode(m_hdc, TRANSPARENT); }

		void OpaqueText() { SetBkMode(m_hdc, OPAQUE); }

		void TextColor(int color) { assert(color < NumColors); SetTextColor(m_hdc, colors[color]); }
		void TextColor(int r, int g, int b) { SetTextColor(m_hdc, RGB(r, g, b)); }


		//-------------------------
		// 函数名:  DrawDot
		// 参数: pos 描述位置,color
		// 返回值:  void
		void DrawDot(Vector2D pos, COLORREF color) {
			SetPixel(m_hdc, (int)pos.x, (int)pos.y, color);
		}
		void DrawDot(int x, int y, COLORREF color) {
			SetPixel(m_hdc, x, y, color);
		}


		//-------------------------
		// 函数名:  Line
		// 参数: from , to
		// 返回值:  void
		void Line(Vector2D from, Vector2D to) {
			MoveToEx(m_hdc, (int)from.x, (int)from.y, NULL);
			LineTo(m_hdc, (int)to.x, (int)to.y);
		}
		void Line(int a, int b, int x, int y) {
			MoveToEx(m_hdc, a, b, NULL);
			LineTo(m_hdc, x, y);
		}
		void Line(double a, double b, double x, double y) {
			MoveToEx(m_hdc, (int)a, (int)b, NULL);
			LineTo(m_hdc, x, y);
		}


		//-------------------------
		// 函数名:  PolyLine 绘制多边形
		// 参数: 点的数组
		// 返回值:  void
		void PolyLine(const std::vector<Vector2D>& points) {
			if (points.size() < 2)
				return;
			MoveToEx(m_hdc, (int)points[0].x, (int)points[0].y, NULL);
			for (unsigned int p = 1;p<points.size();p++)
			{
				LineTo(m_hdc, (int)points[p].x, (int)points[p].y);
			}
		}


		///-------------------------
		/// 函数名:  LineWithArrow 绘制一个箭头
		/// 参数: -from ,-to ,-size 大小
		/// 返回值:  void
		void LineWithArrow(Vector2D from, Vector2D to, double size) {
			Vector2D norm = Vec2DNormalize(to - from);

			//计算我们的箭头朝向在哪里
			Vector2D CrossingPoint = to - (norm * size);

			//计算箭头的两个点
			Vector2D ArrowPoint1 = CrossingPoint + (norm.Perp() * 0.4f * size);
			Vector2D ArrowPoint2 = CrossingPoint - (norm.Perp() * 0.4f * size);

			//绘制封闭线
			MoveToEx(m_hdc, (int)from.x, (int)from.y, NULL);
			LineTo(m_hdc, (int)CrossingPoint.x, (int)CrossingPoint.y);

			//绘制箭头
			POINT p[3];

			p[0] = VectorToPOINT(ArrowPoint1);
			p[1] = VectorToPOINT(ArrowPoint2);
			p[2] = VectorToPOINT(to);

			SetPolyFillMode(m_hdc, WINDING);
			Polygon(m_hdc, p, 3);
		}

		void Circle(Vector2D pos, double radius)
		{
			Ellipse(m_hdc,
				(int)(pos.x - radius),
				(int)(pos.y - radius),
				(int)(pos.x + radius + 1),
				(int)(pos.y + radius + 1));
		}

		void Circle(double x, double y, double radius)
		{
			Ellipse(m_hdc,
				(int)(x - radius),
				(int)(y - radius),
				(int)(x + radius + 1),
				(int)(y + radius + 1));
		}

		void Circle(int x, int y, double radius)
		{
			Ellipse(m_hdc,
				(int)(x - radius),
				(int)(y - radius),
				(int)(x + radius + 1),
				(int)(y + radius + 1));
		}

		void SetPenColor(int color)
		{
			assert(color < NumColors);

			switch (color)
			{
			case black:BlackPen(); return;
			case white:WhitePen(); return;
			case red: RedPen(); return;
			case green: GreenPen(); return;
			case blue: BluePen(); return;
			case pink: PinkPen(); return;
			case grey: GreyPen(); return;
			case yellow: YellowPen(); return;
			case orange: OrangePen(); return;
			case purple: PurplePen(); return;
			case brown: BrownPen(); return;
			case light_blue: LightBluePen(); return;
			case light_grey: LightGreyPen(); return;
			case light_pink: LightPinkPen(); return;
			}//end switch
		}

		void SetBrushColor(int color)
		{
			assert(color < NumColors);

			switch (color)
			{
			case black:BlackBrush(); return;
			case white:WhiteBrush(); return;
			case red: RedBrush(); return;
			case green: GreenBrush(); return;
			case blue: BlueBrush(); return;
			case grey: GreyBrush(); return;
			case yellow: YellowBrush(); return;
			case orange: OrangeBrush(); return;
			case brown: BrownBrush(); return;
			case light_blue: LightBlueBrush(); return;
			}//end switch
		}

		void RefreshScreen(HWND hWnd) {
			RECT client;
			GetClientRect(hWnd, &client);
			//HBRUSH newBrush = CreateSolidBrush(RGB(255, 0, 0));
			//newBrush = (HBRUSH)SelectObject(m_hdc, newBrush);
			BlackBrush();
			Rectangle(m_hdc, client.left, client.top, client.right, client.bottom);

		}
	};

	
}
//static const pnGF::Cgdi& gdi = pnGF::Cgdi::Instance();
static pnGF::Cgdi* mgid = pnGF::Cgdi::Instance();