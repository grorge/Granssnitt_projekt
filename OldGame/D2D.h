#pragma once
#ifndef D2D_H
#define D2D_H

#include "ID2D.h"
#include <time.h>

#include "Locator.h"
#include "CleanupTools.h"

struct BoxGeoData {
	ID2D1RectangleGeometry* p_rectGeom = nullptr;
	ID2D1SolidColorBrush* p_colorBrush = nullptr;
	ID2D1SolidColorBrush* p_textBrush = nullptr;
	DirectX::XMFLOAT2 pos = DirectX::XMFLOAT2(0.0f, 0.0f);
	DirectX::XMFLOAT2 size = DirectX::XMFLOAT2(0.0f, 0.0f);
	float padding = 0.0f;
	D2D1_RECT_F rectf;
	D2D1_RECT_F paddedRectf;

	// Calcs Rect from the parameters
	void setRect() {
		this->rectf = D2D1::RectF(pos.x, pos.y, pos.x + size.x, pos.y + size.y ); 

		//Only padding on the left and rigth to align the text
		this->paddedRectf = D2D1::RectF(pos.x + padding, pos.y, pos.x + size.x + padding, pos.y + size.y); 
		
	}
	D2D1_RECT_F getRect() {
		return this->rectf;
	}
	D2D1_RECT_F getPadRect() {
		return this->paddedRectf;
	}

	void copyStyle(BoxGeoData* source)
	{
		pos = source->pos;
		size = source->size;
		padding = source->padding;
		p_rectGeom = source->p_rectGeom;
		p_colorBrush = source->p_colorBrush;
		p_textBrush = source->p_textBrush;

		
	};
};

struct MenuBox
{
	DirectX::XMFLOAT2 pos = DirectX::XMFLOAT2(0.0f, 0.0f);

	BoxGeoData Background;
	std::wstring Text;
	bool ToRender;
};

struct MenuInfo
{
	DirectX::XMFLOAT2 pos = DirectX::XMFLOAT2(0.0f, 0.0f);

	BoxGeoData boxStyle;
	D2D1::ColorF bColor = D2D1::ColorF(D2D1::ColorF::White);
	D2D1::ColorF tColor = D2D1::ColorF(D2D1::ColorF::White);

	int nrMenuBoxes = 1;
	std::vector<MenuBox> v_Box;

	void setText(int index, std::wstring text)
	{
		v_Box.at(index).Text = text;
	};

	MenuInfo()
	{
		this->nrMenuBoxes = 0;
		this->boxStyle = BoxGeoData();
	};
	
	//Nr of boxes, topLeft, Size, Padding, BackgroundColor, TextColor
	MenuInfo(int nrOf, DirectX::XMFLOAT2 pos, 
		DirectX::XMFLOAT2 size, float padding,
		D2D1::ColorF bColor, D2D1::ColorF tColor)
	{
		this->nrMenuBoxes = nrOf;
		//this->pos = pos;
		this->bColor = bColor;
		this->tColor = tColor;

		this->pos = pos;
		this->boxStyle.pos = pos;
		this->boxStyle.size = size;
		this->boxStyle.padding = padding;
		this->boxStyle.setRect();
	};
};


class D2D : public ID2D
{
public:
	// Register the window class and call methods for instantiating drawing resources
	virtual HRESULT Initialize(IDXGISurface1 *sSurface10);

	// Draw content.
	virtual HRESULT OnRender();

	virtual ID2D1RenderTarget* GETRenderTarget() { return this->m_pRenderTarget; }
	virtual IDWriteTextFormat* GETTextFormat() { return this->m_pTextFormat; }
	virtual void SETTextFormat(std::wstring input) { this->msgText = input; }
	virtual void openMenu();
	virtual void pauseMenu();
	virtual void closeMenu();
	virtual void cleanUp();
	virtual void setBackbuffer(ID3D11Texture2D* pBB);


private:
	// D3D backbuffer
	ID3D11Texture2D * r_pBackBuffer;

	// D2D device
	ID2D1Factory* m_pDirect2dFactory = nullptr;
	// Render target, dose all calls to render
	ID2D1RenderTarget* m_pRenderTarget = nullptr;
	// D2D device for text
	IDWriteFactory* m_pDirectWriteFactory = nullptr;
	// Holds formating for text, ea Font
	IDWriteTextFormat* m_pTextFormat = nullptr;

	// Initialize device-independent resources. Like factory
	HRESULT CreateDeviceIndependentResources();

	// Initialize device-dependent resources.
	HRESULT CreateDeviceResources(IDXGISurface1 *sSurface10);
	
	// Release device-dependent resource.
	void DiscardDeviceResources();

	//Brushes
	ID2D1SolidColorBrush * pTextColor = nullptr;

	//Geometries (1: pointer 2: position 3:Size)
	MenuInfo* g_Menu;
	BoxGeoData g_MsgBox;
	//std::vector<BoxGeoData*> v_BoxVector;


	IWICImagingFactory *pIWICFactory = nullptr;
	//PCWSTR uri = nullptr;
	UINT destinationWidth;
	UINT destinationHeight;
	ID2D1Bitmap* pBitmap = nullptr;

	// Holds the text that will be printed on the screen
	std::wstring printText;

	// Mesage to be changed during runtime
	std::wstring msgText = L"NaN";

	// FPS counter
	void checkFPS();
	int frames = 0;
	int fps = 0;
	clock_t lastFrame = clock_t();
	clock_t newFrame = clock_t();
	clock_t frametime = clock_t();
	clock_t lastDisplay = clock_t();


	void initMenu();
	void drawMenu();
};


#endif // !D2D_H