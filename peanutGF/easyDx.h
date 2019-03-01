#pragma once
/*!
 * \file easyDx.h
 * \date 2019/02/09 22:36
 *
 * \author CodeLoser
 * Contact: pokkemon2@outlook.com
 *
 * \brief 跳兔游戏轻量框架图形渲染基础类的头文件(基于对DirectX图形库的封装)
 *
 * TODO: 暂定
 *
 * \note 暂定
*/

//依赖文件
#include <d3dx9.h>



/*!
 * \class easyDx
 *
 * \brief 跳兔游戏轻量框架图形渲染基础类
 *
 * \author CodeLoser
 * \date 2019/02/09 22:36
 */
class easyDx
{
#define SAFE_RELEASE(p) {if(p) { (p)->Release(); (p)=NULL; }}
public:
	~easyDx() { instance = nullptr; }

	static easyDx* Get()
	{
		if (instance == nullptr)
			instance = new easyDx;
		return instance;
	}
private:
	static easyDx* instance;
public:
	HRESULT Init(HWND hwnd);
	HRESULT Res_Init();//资源管理器 - 这里装载我们的资源,目前没有自定的资源格式,采用 XML 或 Json 
	VOID RenderModle();//渲染模块 - 无论场景的渲染还是对象结点的渲染,这里作为总渲染,需要另一个辅助类 渲染优先级队列
	VOID CleanUp(); //释放指针资源 - 

private:
	LPDIRECT3DDEVICE9 m_gDev;//Dx环境设备
	HWND m_rlHwnd; //用于将我们的Dx设备与我们的窗体进行关联
	int width, height;


	//test
	//字体
	LPD3DXFONT ppFont;
};

static easyDx* eDx = easyDx::Get();