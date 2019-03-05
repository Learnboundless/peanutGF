#pragma once
#include "redObj.h"
#include <d3dx9.h>
#include <string>

using namespace std;

class Text :
	public redObj
{
public:
	Text(string text,int x, int y,D3DCOLOR color, int order = 1,string fontname="微软雅黑", int fontsize=5 );
	~Text();
	

	// 实现redObj的渲染接口
	virtual void renderSel() const override;
	virtual void initRes(LPDIRECT3DDEVICE9 dev) override;

private:
	string text;
	int x, y;
	LPD3DXFONT font;
	D3DCOLOR color;
public:
	void SetFontText(string text);
};

