#pragma once
/*!
 * \file easyDx.h
 * \date 2019/02/09 22:36
 *
 * \author CodeLoser
 * Contact: pokkemon2@outlook.com
 *
 * \brief ������Ϸ�������ͼ����Ⱦ�������ͷ�ļ�(���ڶ�DirectXͼ�ο�ķ�װ)
 *
 * TODO: �ݶ�
 *
 * \note �ݶ�
*/

//�����ļ�
#include <d3dx9.h>



/*!
 * \class easyDx
 *
 * \brief ������Ϸ�������ͼ����Ⱦ������
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
	HRESULT Res_Init();//��Դ������ - ����װ�����ǵ���Դ,Ŀǰû���Զ�����Դ��ʽ,���� XML �� Json 
	VOID RenderModle();//��Ⱦģ�� - ���۳�������Ⱦ���Ƕ��������Ⱦ,������Ϊ����Ⱦ,��Ҫ��һ�������� ��Ⱦ���ȼ�����
	VOID CleanUp(); //�ͷ�ָ����Դ - 

private:
	LPDIRECT3DDEVICE9 m_gDev;//Dx�����豸
	HWND m_rlHwnd; //���ڽ����ǵ�Dx�豸�����ǵĴ�����й���
	int width, height;


	//test
	//����
	LPD3DXFONT ppFont;
};

static easyDx* eDx = easyDx::Get();