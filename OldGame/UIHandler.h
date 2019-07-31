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

	// Menus
	int onButton = 99;
	int currmenu = 99;
	MenuInfo* menu;
	//std::array<MenuInfo* , 2> a_menus;

	std::vector<UIData*> rndData;

	// Initiate Menus
	bool createPause();


	// Updates the rndData to have the relevent geometries
	void fillRndData();
public:
	//UIHandler();
	UIHandler(ID2D1RenderTarget* m_pRenderTarget = nullptr, ID2D1Factory* p_Factory = nullptr);
	~UIHandler();
	void cleanUp();

	bool openMenu(size_t index);
	bool closeMenu(size_t index);

	size_t nrOf;
	std::vector<UIData*> GETUIdata();

	void drawData();
	void update();

	// Loops throuth and runs any functions fropm highligthed buttons
	void onClick();
	
};


#endif // !UIHANDLER_h