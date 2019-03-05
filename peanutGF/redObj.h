#pragma once
#include <d3d9.h>
#include "renderQueue.h"

//游戏世界基本物体渲染接口准则
class redObj
{
public:
	redObj(int order):index(order) { redQue->Push(this); }
	virtual ~redObj() {}
public:
	virtual void renderSel()const = 0; //渲染接口
	virtual void initRes(LPDIRECT3DDEVICE9 dev) = 0;
private:
	int index;
public:
	bool operator < (const redObj &a) const {
		return index > a.index;//最小值优先 
	}
};

