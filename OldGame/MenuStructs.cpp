#include "MenuStructs.h"

void MenuBox::draw(ID2D1RenderTarget * p_rndTarget)
{
	if (highligth)
	{
		p_rndTarget->DrawGeometry(this->Background.p_rectGeom, this->Background.p_highligthColorBrush);
		p_rndTarget->FillGeometry(this->Background.p_rectGeom, this->Background.p_highligthColorBrush);
	}
	else
	{
		p_rndTarget->DrawGeometry(this->Background.p_rectGeom, this->Background.p_colorBrush);
		p_rndTarget->FillGeometry(this->Background.p_rectGeom, this->Background.p_colorBrush);
	}

	//Draw the Text
	p_rndTarget->DrawText(
		this->TxtData.wstring.c_str(),
		wcslen(this->TxtData.wstring.c_str()),
		this->TxtData.textFormat,
		this->Background.getPadRect(),
		this->TxtData.p_textBrush
	);
}

ProgressBar::ProgressBar(DirectX::XMFLOAT2 pos, DirectX::XMFLOAT2 size, D2D1::ColorF bColor, D2D1::ColorF fColor, D2D1::ColorF tColor)
{
	this->filled = 1.0f;
	
	this->bColor = bColor;
	this->fColor = fColor;
	this->tColor = tColor;

	this->pos = pos;
	this->size = size;
	

	this->Back.pos = pos;
	this->Back.size = size;
	this->Back.padding = 0;
	this->Back.setRect();

	this->Front.pos = pos;
	this->Front.size = size;
	this->Front.padding = 0;
	this->Front.setRect();
}

void ProgressBar::draw(ID2D1RenderTarget * p_rndTarget)
{
	p_rndTarget->DrawGeometry(this->Back.p_rectGeom, this->Back.p_colorBrush);
	p_rndTarget->FillGeometry(this->Back.p_rectGeom, this->Back.p_colorBrush);

	p_rndTarget->DrawGeometry(this->Front.p_rectGeom, this->Front.p_colorBrush);
	p_rndTarget->FillGeometry(this->Front.p_rectGeom, this->Front.p_colorBrush);


	//Draw the Text
	p_rndTarget->DrawText(
		this->TxtData.wstring.c_str(),
		wcslen(this->TxtData.wstring.c_str()),
		this->TxtData.textFormat,
		this->Back.getPadRect(),
		this->TxtData.p_textBrush
	);
}

void ProgressBar::update()
{
	// Change the front box depending on the filled member
	Front.size.x = Back.size.x * filled;
	Front.setRect();

	// Change the text if that is relevant
}
