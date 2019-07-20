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

	MenuInfo* menu;
	ID2D1RenderTarget* p_rndTarget = nullptr;
	// D2D device for text
	ID2D1Factory* p_Factory = nullptr;
	//std::array<MenuInfo* , 2> a_menus;

	UIData* rndData;

	// Menus
	bool createPause();


	// 
	void fillRndData();
public:
	//UIHandler();
	UIHandler(ID2D1RenderTarget* m_pRenderTarget = nullptr, ID2D1Factory* p_Factory = nullptr);
	~UIHandler();
	void cleanUp();

	bool openMenu(size_t index);
	bool closeMenu(size_t index);

	size_t nrOf;
	UIData* GETUIdata();
	
};


#endif // !UIHANDLER_h