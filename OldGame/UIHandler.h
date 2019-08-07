#pragma once
#ifndef UIHANDLER_h
#define UIHANDLER_h

// Holds all includes
#include "MenuStructs.h"
#include <array>


#define NR_MENUS 2
#define MEN_OFF -1
#define MEN_PA 0
#define MEN_OP 1


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
	int onButton = MEN_OFF;
	//MenuInfo* menu;
	int currMenu = MEN_OFF;
	std::array<MenuInfo* , 2> a_menus;
	//0 pause
	//1 options

	//Progressbars
	std::vector<ProgressBar*> textProgbars;
	std::vector<ProgressBar*> numbProgbars;

	//std::vector<UIData*> rndData;

	// Initiate Menus
	bool createBoxes(int menuNr);
	bool createPause();
	bool createOptions();

	// Create Default UI
	void initProgBarGraph(ProgressBar* tempProg);
	bool createProgBars();


	// Updates the rndData to have the relevent geometries
	//void fillRndData();
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

	ProgressBar* makeProgbarTimer(int startTime,
		DirectX::XMFLOAT2 pos,
		DirectX::XMFLOAT2 size,
		D2D1::ColorF bColor, D2D1::ColorF fColor, D2D1::ColorF tColor);

	ProgressBar* makeProgbarNumber(int maxValue,
		DirectX::XMFLOAT2 pos,
		DirectX::XMFLOAT2 size,
		D2D1::ColorF bColor, D2D1::ColorF fColor, D2D1::ColorF tColor);
};


#endif // !UIHANDLER_h