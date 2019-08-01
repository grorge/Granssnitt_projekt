#pragma once
#ifndef UIHANDLER_h
#define UIHANDLER_h

// Holds all includes
#include "MenuStructs.h"


//#define NR_MENUS 2


struct UIData
{
	BoxGeoData GeoData;
	TextData TxtData;
};


class UIHandler
{
private:

	void initResources();
	ID2D1RenderTarget* p_rndTarget = nullptr; // reff
	// D2D device for text
	ID2D1Factory* p_Factory = nullptr; // reff
	IDWriteFactory* p_DirectWriteFactory = nullptr;

	// TextFormats
	IDWriteTextFormat* tf_Buttons = nullptr;
	IDWriteTextFormat* tf_Title = nullptr;
	IDWriteTextFormat* tf_Progrbar = nullptr;

	// Menus
	int onButton = 99;
	int currmenu = 99;
	MenuInfo* menu;
	//std::array<MenuInfo* , 2> a_menus;

	//Progressbars
	std::vector<ProgressBar*> textProgbars;
	std::vector<ProgressBar*> numbProgbars;

	std::vector<UIData*> rndData;

	// Initiate Menus
	bool createPause();

	// Create Default UI
	bool createProgBars();


	// Updates the rndData to have the relevent geometries
	void fillRndData();
public:
	//UIHandler();
	UIHandler(ID2D1RenderTarget* m_pRenderTarget = nullptr, ID2D1Factory* p_Factory = nullptr);
	~UIHandler();
	void cleanUp();

	// Loops throuth and runs functions from highligthed buttons
	void onClick(); // is locataed in Buttonfunction.cpp


	bool openMenu(size_t index);
	bool closeMenu(size_t index);

	size_t nrOf;
	std::vector<UIData*> GETUIdata();

	void drawData();
	void update();

	

	// creates and returns a progress-bar to be saved and to be altered
	ProgressBar* makeProgbar( std::wstring startString,
		DirectX::XMFLOAT2 pos,
		DirectX::XMFLOAT2 size,
		D2D1::ColorF bColor, D2D1::ColorF fColor, D2D1::ColorF tColor);
};


#endif // !UIHANDLER_h