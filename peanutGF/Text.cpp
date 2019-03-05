#include "Text.h"


Text::Text(string text,  int x, int y, D3DCOLOR color,int order,string fontname, int fontsize):redObj(order)
{
	this->text = text;
	this->x = x;
	this->y = y;
	this->color = color;
}

Text::~Text()
{
}

void Text::renderSel() const
{
	RECT resPos;
	resPos.top = resPos.left = 0;
	resPos.right = 640;
	resPos.bottom = 640;
	resPos.top = 250 + y;
	font->DrawText(0, text.c_str(), -1, &resPos, DT_CENTER, color);
}

void Text::initRes(LPDIRECT3DDEVICE9 dev)
{
	D3DXCreateFont(dev, 24, 18, 3, 5, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0,
		"Î¢ÈíÑÅºÚ", &font);
}

void Text::SetFontText(string text)
{
	this->text = text;
}
