#pragma once

// Holds all includes
#include "ID2D.h"

// Holds the graphical data for each box on the screen
struct BoxGeoData {
	ID2D1RectangleGeometry* p_rectGeom = nullptr;
	ID2D1SolidColorBrush* p_colorBrush = nullptr;
	ID2D1SolidColorBrush* p_highligthColorBrush = nullptr;
	ID2D1SolidColorBrush* p_textBrush = nullptr;
	DirectX::XMFLOAT2 pos = DirectX::XMFLOAT2(0.0f, 0.0f);
	DirectX::XMFLOAT2 size = DirectX::XMFLOAT2(0.0f, 0.0f);
	float padding = 0.0f;
	D2D1_RECT_F rectf;
	D2D1_RECT_F paddedRectf;

	// Calcs Rect from the parameters
	void setRect() {
		this->rectf = D2D1::RectF(pos.x, pos.y, pos.x + size.x, pos.y + size.y);

		//Only padding on the left and rigth to align the text
		// Padded inside
		this->paddedRectf = D2D1::RectF(pos.x + padding, pos.y, pos.x + size.x - padding, pos.y + size.y);

	}
	D2D1_RECT_F getRect() {
		return this->rectf;
	}
	// Retuns RECT with margin to hte sides of the visual box
	D2D1_RECT_F getPadRect() {
		return this->paddedRectf;
	}

	// Used to copy the BoxStyle on the menu
	void copyStyle(BoxGeoData* source)
	{
		pos = source->pos;
		size = source->size;
		padding = source->padding;
		p_rectGeom = source->p_rectGeom;
		p_colorBrush = source->p_colorBrush;
		p_highligthColorBrush = source->p_highligthColorBrush;
		p_textBrush = source->p_textBrush;
	};
};
// Holds the graphical data for each box on the screen
struct TextData {
	std::wstring wstring;
	IDWriteTextFormat* textFormat;
};

// Holds the data of each Button
struct MenuBox
{
	DirectX::XMFLOAT2 pos = DirectX::XMFLOAT2(0.0f, 0.0f);

	BoxGeoData Background;
	bool highligth = false;
	TextData TxtData;
	bool ToRender = false;


	void draw(ID2D1RenderTarget * p_rndTarget);
};

// Handles the menu
struct MenuInfo
{
	DirectX::XMFLOAT2 pos = DirectX::XMFLOAT2(0.0f, 0.0f);

	TextData titleText;
	D2D1_RECT_F titleRect;

	BoxGeoData boxStyle;
	D2D1::ColorF bColor = D2D1::ColorF(D2D1::ColorF::White);
	D2D1::ColorF bHighColor = D2D1::ColorF(D2D1::ColorF::White);
	D2D1::ColorF tColor = D2D1::ColorF(D2D1::ColorF::White);

	int nrMenuBoxes = 0;
	std::vector<MenuBox> v_Box;

	// Changes the text of the indexed Button
	void setText(int index, std::wstring text)
	{
		v_Box.at(index).TxtData.wstring = text;
	};

	MenuInfo()
	{
		this->nrMenuBoxes = 0;
		this->boxStyle = BoxGeoData();
	};

	//Nr of boxes, topLeft, Size, Padding, BackgroundColor, TextColor
	MenuInfo(int nrOf, DirectX::XMFLOAT2 pos,
		DirectX::XMFLOAT2 size, float padding,
		D2D1::ColorF bColor, D2D1::ColorF bHighColor, D2D1::ColorF tColor)
	{
		this->nrMenuBoxes = nrOf;
		this->bColor = bColor;
		this->bHighColor = bHighColor;
		this->tColor = tColor;

		this->pos = pos;
		this->boxStyle.pos = pos;
		this->boxStyle.size = size;
		this->boxStyle.padding = padding;
		this->boxStyle.setRect();
	};
};