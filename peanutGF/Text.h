#pragma once
#include "redObj.h"
#include <d3dx9.h>
#include <string>

using namespace std;

class Text :
	public redObj
{
public:
	Text(string fontname,int fontsize,int x,int y,int order);
	~Text();
	

	// Í¨¹ý redObj ¼Ì³Ð
	virtual void renderSel() const override;
private:
	int x, y;
	LPD3DXFONT font;

};

