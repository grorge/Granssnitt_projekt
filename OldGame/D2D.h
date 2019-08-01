#pragma once
#ifndef D2D_H
#define D2D_H

#include "ID2D.h"
#include "UIHandler.h"
#include <time.h>

#include "Locator.h"
#include "CleanupTools.h"


class D2D : public ID2D
{
public:
	// Register the window class and call methods for instantiating drawing resources
	virtual HRESULT Initialize(IDXGISurface1 *sSurface10);

	// Draw content.
	virtual HRESULT OnRender();

	virtual ID2D1RenderTarget* GETRenderTarget() { return this->m_pRenderTarget; }
	virtual IDWriteTextFormat* GETTextFormat() { return this->m_pTextFormat; }
	virtual void sendClick() { this->ui->onClick(); };
	virtual void SETTextFormat(std::wstring input) { this->msgText = input; }
	virtual void openMenu();
	virtual void pauseMenu();
	virtual void closeMenu();
	virtual void cleanUp();
	virtual void setBackbuffer(ID3D11Texture2D* pBB);


private:
	// D3D Resourses needed
	ID3D11Texture2D * r_pBackBuffer;
	// Mutexes are used to sync over the different threads, prevents overlap from D2D and D3D
	IDXGIKeyedMutex *keyedMutex11;
	IDXGIKeyedMutex *keyedMutex10;

	// D2D device
	ID2D1Factory* m_pDirect2dFactory = nullptr;
	// Render target, calls to render
	ID2D1RenderTarget* m_pRenderTarget = nullptr;
	// D2D device for text
	IDWriteFactory* m_pDirectWriteFactory = nullptr;
	// Holds formating for text, ea Font etc.
	IDWriteTextFormat* m_pTextFormat = nullptr;

	// Initialize device-independent resources. Like factory
	HRESULT CreateDeviceIndependentResources();

	// Initialize mutexes.
	HRESULT CreateSharedResourses();

	// Initialize device-dependent resources.
	HRESULT CreateDeviceResources(IDXGISurface1 *sSurface10);
	
	// Release device-dependent resource.
	void DiscardDeviceResources();

	//Brushes
	ID2D1SolidColorBrush * pTextColor = nullptr;

	//Geometries (1: pointer 2: position 3:Size)
	// DebugWindow to write the frame-info
	BoxGeoData g_MsgBox;


	IWICImagingFactory *pIWICFactory = nullptr;
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
	void initProgbars();
	void drawMenu();
	void drawDebugWindow();

	UIHandler* ui;

};


#endif // !D2D_H