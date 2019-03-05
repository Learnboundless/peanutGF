#pragma once
#include <d3d9.h>
#include "renderQueue.h"

//��Ϸ�������������Ⱦ�ӿ�׼��
class redObj
{
public:
	redObj(int order):index(order) { redQue->Push(this); }
	virtual ~redObj() {}
public:
	virtual void renderSel()const = 0; //��Ⱦ�ӿ�
	virtual void initRes(LPDIRECT3DDEVICE9 dev) = 0;
private:
	int index;
public:
	bool operator < (const redObj &a) const {
		return index > a.index;//��Сֵ���� 
	}
};

