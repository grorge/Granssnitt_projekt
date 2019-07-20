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

	//std::array<MenuInfo* , 2> a_menus;


	// Menus
	bool createPause();
public:
	UIHandler();
	~UIHandler();
	void cleanUp();

	bool openMenu(size_t index);
	bool closeMenu(size_t index);

	size_t nrOf;
	UIData* GETUIdata();
	
};


#endif // !UIHANDLER_h