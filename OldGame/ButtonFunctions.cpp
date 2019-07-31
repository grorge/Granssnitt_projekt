#include "UIHandler.h"


void UIHandler::onClick()
{
	switch (this->currmenu)
	{
	case 0: // Pause menu
		switch (this->onButton)
		{
		case 0: // start
			this->menu->v_Box.at(onButton).TxtData.wstring = L"CLICKED";
			break;
		case 1: // Options
			this->menu->v_Box.at(onButton).TxtData.wstring = L"CLICKED";
			break;
		case 2: // Exit
			this->menu->v_Box.at(onButton).TxtData.wstring = L"CLICKED";
			break;
		case 3: // nan
			this->menu->v_Box.at(onButton).TxtData.wstring = L"CLICKED";
			break;
		default:
			break;
		}
		break;
	case 1:
		break;
	default:
		break;
	}

}
