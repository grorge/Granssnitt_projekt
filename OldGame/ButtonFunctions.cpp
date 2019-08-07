#include "UIHandler.h"


void UIHandler::onClick()
{
	switch (this->currMenu)
	{
	case MEN_PA: // Pause menu
		switch (this->onButton)
		{
		case 0: // start
			this->a_menus[MEN_PA]->v_Box.at(onButton).TxtData.wstring = L"CLICKED";
			break;
		case 1: // Options
			this->closeMenu(MEN_PA);
			this->openMenu(MEN_OP);
			break;
		case 2: // Exit
			this->closeMenu(MEN_PA);
			break;
		case 3: // nan	  
			this->a_menus[MEN_PA]->v_Box.at(onButton).TxtData.wstring = L"CLICKED";
			break;
		default:
			break;
		}
		break;
	case MEN_OP: // Pause menu
		switch (this->onButton)
		{
		case 0: // Windowed
			break;
		case 1: // Mute
			break;
		case 2: // Back
			this->closeMenu(MEN_OP);
			this->openMenu(MEN_PA);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

}