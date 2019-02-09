#include "easyDx.h"

easyDx::~easyDx()
{
}


HRESULT easyDx::Init()
{
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
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 2;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = m_rlHwnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	//创建设备
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hwnd, vp, &d3dpp, &m_gDev)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(pD3D);
	if (!(S_OK == Res_Init()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT easyDx::Res_Init()
{
	return E_NOTIMPL;
}

VOID easyDx::RenderModle()
{
	return VOID();
}

VOID easyDx::CleanUp()
{
	return VOID();
}
