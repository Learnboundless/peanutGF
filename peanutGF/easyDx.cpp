#include "easyDx.h"
#include "renderQueue.h"


easyDx* easyDx::instance = nullptr;

HRESULT easyDx::Init(HWND hwnd)
{
	m_rlHwnd = hwnd;
	//�����豸�ӿ�
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
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING; //��������
	}
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	//��д����
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = false?width:640;
	d3dpp.BackBufferHeight = false?height:640;
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
	//�����豸
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		m_rlHwnd, vp, &d3dpp, &m_gDev)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(pD3D);
	if (!(S_OK == Res_Init()))
	{
		m_renderQueue=renderQue::Get();
		return E_FAIL;
	}
	return S_OK;
}

HRESULT easyDx::Res_Init()
{
	m_renderQueue->ParseRes(m_gDev);

	if (S_OK == D3DXCreateFont(m_gDev, 18, 16, 3, 5, TRUE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0,
		"΢���ź�", &ppFont))
	{
		//MessageBox(hWin, "Font Ok!", "DxOK", MB_OK);
	}
	return E_NOTIMPL;
}

VOID easyDx::RenderModle()
{
	m_gDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	m_gDev->BeginScene();
	

	m_renderQueue->Render();
	/*RECT resPos;
	resPos.top = resPos.left = 0;
	resPos.right = 640;
	resPos.bottom = 640;
	//ʵ�ʻ��ƴ���
	resPos.top = 250;
	ppFont->DrawText(0, ("Skill Begin!"), -1, &resPos, DT_CENTER, D3DCOLOR_XRGB(rand() % 255, rand() % 128, rand() % 225));
	resPos.top = 350;
	ppFont->DrawText(0, ("GamePrograming I am Coming Again!"), -1, &resPos, DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));
	*/

	m_gDev->EndScene();
	m_gDev->Present(NULL, NULL, NULL, NULL);
	return VOID();
}

VOID easyDx::CleanUp()
{
	return VOID();
}
