#pragma once

//游戏世界基本物体渲染接口准则
class redObj
{
public:
	redObj() {}
	virtual ~redObj() {}
public:
	virtual void renderSel()const = 0; //渲染接口
};

