#include "UIHandler.h"
#include "Locator.h"

void UIHandler::initResources()
{
	// The main font
	static const WCHAR msc_fontName[] = L"Script"; // Verdana, Rockwell, Agency FB, Script

	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown **>(&this->p_DirectWriteFactory)
	);

	// Create Textformats

	// For the buttons
	this->p_DirectWriteFactory->CreateTextFormat(
		msc_fontName,
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20, // Fontsize
		L"en-us", //L"", //locale
		&this->tf_Buttons
	);
	// Center the text horizontally and vertically.
	this->tf_Buttons->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	this->tf_Buttons->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	// For the Title
	this->p_DirectWriteFactory->CreateTextFormat(
		msc_fontName,
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		50, // forntsize
		L"en-us", //L"", //locale
		&this->tf_Title
	);
	// Center the text horizontally and vertically.
	this->tf_Title->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	this->tf_Title->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);


	// For the Title
	this->p_DirectWriteFactory->CreateTextFormat(
		msc_fontName,
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		15, // forntsize
		L"en-us", //L"", //locale
		&this->tf_Progrbar
	);
	// Center the text horizontally and vertically.
	this->tf_Progrbar->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	this->tf_Progrbar->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

bool UIHandler::createBoxes(int menuNr)
{
	this->a_menus[menuNr]->v_Box.clear();
	for (size_t i = 0; i < this->a_menus[menuNr]->nrMenuBoxes; i++)
	{
		MenuBox tempMenuBox;
		tempMenuBox.Background.copyStyle(&this->a_menus[menuNr]->boxStyle);
		tempMenuBox.Background.pos =
			DirectX::XMFLOAT2(
				this->a_menus[menuNr]->pos.x,
				this->a_menus[menuNr]->pos.y + (i * (this->a_menus[menuNr]->boxStyle.size.y + (this->a_menus[menuNr]->boxStyle.padding)))
			);
		tempMenuBox.Background.setRect();

		p_Factory->CreateRectangleGeometry(
			tempMenuBox.Background.getRect(),
			&tempMenuBox.Background.p_rectGeom
		);

		tempMenuBox.ToRender = false;
		tempMenuBox.TxtData.wstring = L"NOTHING ASSINGED";
		tempMenuBox.TxtData.textFormat = this->tf_Buttons;
		tempMenuBox.TxtData.p_textBrush = this->a_menus[menuNr]->p_textBrush;
		this->a_menus[menuNr]->v_Box.push_back(tempMenuBox);
	}



	return true;
}

bool UIHandler::createPause()
{
	// Create the style to be copied onto the boxes
	DirectX::XMFLOAT2 sizeFloat(
		DirectX::XMFLOAT2(200.0f, 100.0f)
	);
	DirectX::XMFLOAT2 middlePoint(
		(Locator::getD3D()->GETwWidth() / 2.0f) - sizeFloat.x / 2.0f,
		(Locator::getD3D()->GETwHeight() / 3.0f)
	);

	this->a_menus[MEN_PA] = new MenuInfo(
		5,
		middlePoint, sizeFloat, 5.0f,
		D2D1::ColorF(D2D1::ColorF::Green), D2D1::ColorF(D2D1::ColorF::GreenYellow), D2D1::ColorF(D2D1::ColorF::Red)
	);

	// Creates the colors
	this->p_rndTarget->CreateSolidColorBrush(D2D1::ColorF(this->a_menus[MEN_PA]->bColor), &this->a_menus[MEN_PA]->boxStyle.p_colorBrush);
	this->p_rndTarget->CreateSolidColorBrush(D2D1::ColorF(this->a_menus[MEN_PA]->bHighColor), &this->a_menus[MEN_PA]->boxStyle.p_highligthColorBrush);
	this->p_rndTarget->CreateSolidColorBrush(D2D1::ColorF(this->a_menus[MEN_PA]->tColor), &this->a_menus[MEN_PA]->p_textBrush);


	//---------------------------------------------------

	//Create the boxes
	this->createBoxes(MEN_PA);


	// Change the text of each box
	this->a_menus[MEN_PA]->setText(0, L"Start");
	this->a_menus[MEN_PA]->setText(1, L"Options");
	this->a_menus[MEN_PA]->setText(2, L"Exit");

	//---------------------------------------------------

	//Create the Title

	// Set the rect to a space from the top to the start of the buttons
	this->a_menus[MEN_PA]->titleRect = D2D1::RectF(this->a_menus[MEN_PA]->pos.x, 0, this->a_menus[MEN_PA]->pos.x + this->a_menus[MEN_PA]->boxStyle.size.x, this->a_menus[MEN_PA]->pos.y);
	this->a_menus[MEN_PA]->titleText.textFormat = this->tf_Title;
	this->a_menus[MEN_PA]->titleText.p_textBrush = this->a_menus[MEN_PA]->p_textBrush;
	this->a_menus[MEN_PA]->titleText.wstring = L"PAUSE";

	return true;
}

bool UIHandler::createOptions()
{
	// Create the style to be copied onto the boxes
	DirectX::XMFLOAT2 sizeFloat(
		DirectX::XMFLOAT2(200.0f, 100.0f)
	);
	DirectX::XMFLOAT2 middlePoint(
		(Locator::getD3D()->GETwWidth() / 2.0f) - sizeFloat.x / 2.0f,
		(Locator::getD3D()->GETwHeight() / 3.0f)
	);

	this->a_menus[MEN_OP] = new MenuInfo(
		3,
		middlePoint, sizeFloat, 5.0f,
		D2D1::ColorF(D2D1::ColorF::Red), D2D1::ColorF(D2D1::ColorF::PaleVioletRed), D2D1::ColorF(D2D1::ColorF::Green)
	);

	// Creates the colors
	this->p_rndTarget->CreateSolidColorBrush(D2D1::ColorF(this->a_menus[MEN_OP]->bColor), &this->a_menus[MEN_OP]->boxStyle.p_colorBrush);
	this->p_rndTarget->CreateSolidColorBrush(D2D1::ColorF(this->a_menus[MEN_OP]->bHighColor), &this->a_menus[MEN_OP]->boxStyle.p_highligthColorBrush);
	this->p_rndTarget->CreateSolidColorBrush(D2D1::ColorF(this->a_menus[MEN_OP]->tColor), &this->a_menus[MEN_OP]->p_textBrush);


	//---------------------------------------------------

	//Create the boxes
	this->createBoxes(MEN_OP);


	// Change the text of each box
	this->a_menus[MEN_OP]->setText(0, L"Windowwed");
	this->a_menus[MEN_OP]->setText(1, L"Mute");
	this->a_menus[MEN_OP]->setText(2, L"Back");

	//---------------------------------------------------

	//Create the Title

	// Set the rect to a space from the top to the start of the buttons
	this->a_menus[MEN_OP]->titleRect = 
		D2D1::RectF(
			this->a_menus[MEN_OP]->pos.x, 
			0, 
			this->a_menus[MEN_OP]->pos.x + this->a_menus[MEN_OP]->boxStyle.size.x, 
			this->a_menus[MEN_OP]->pos.y
		);
	this->a_menus[MEN_OP]->titleText.textFormat = this->tf_Title;
	this->a_menus[MEN_OP]->titleText.p_textBrush = this->a_menus[MEN_OP]->p_textBrush;
	this->a_menus[MEN_OP]->titleText.wstring = L"OPTIONS";

	return true;

	return true;
}

void UIHandler::initProgBarGraph(ProgressBar * tempProg)
{
	// Create the colorbrushes
	this->p_rndTarget->CreateSolidColorBrush(D2D1::ColorF(tempProg->bColor), &tempProg->Back.p_colorBrush);
	this->p_rndTarget->CreateSolidColorBrush(D2D1::ColorF(tempProg->fColor), &tempProg->Front.p_colorBrush);
	this->p_rndTarget->CreateSolidColorBrush(D2D1::ColorF(tempProg->tColor), &tempProg->TxtData.p_textBrush);


	// Create the geoData
	p_Factory->CreateRectangleGeometry(
		tempProg->Back.getRect(),
		&tempProg->Back.p_rectGeom
	);
	p_Factory->CreateRectangleGeometry(
		tempProg->Front.getRect(),
		&tempProg->Front.p_rectGeom
	);
}

bool UIHandler::createProgBars()
{
	DirectX::XMFLOAT2 size(
		DirectX::XMFLOAT2(300.0f, 50.0f)
	);
	DirectX::XMFLOAT2 initPos(
		(Locator::getD3D()->GETwWidth() / 5.0f),
		(Locator::getD3D()->GETwHeight() * 0.8f)
	);

	this->makeProgbar(
		L"TEST",
		initPos, size,
		D2D1::ColorF(D2D1::ColorF::Red), D2D1::ColorF(D2D1::ColorF::GreenYellow), D2D1::ColorF(D2D1::ColorF::Blue)
	);

	initPos.y -= 100.0f;
	this->makeProgbarTimer(
		100,
		initPos, size,
		D2D1::ColorF(D2D1::ColorF::Red), D2D1::ColorF(D2D1::ColorF::GreenYellow), D2D1::ColorF(D2D1::ColorF::Blue)
	);

	initPos.y -= 100.0f;
	this->makeProgbarTimer(
		300,
		initPos, size,
		D2D1::ColorF(D2D1::ColorF::Red), D2D1::ColorF(D2D1::ColorF::GreenYellow), D2D1::ColorF(D2D1::ColorF::Blue)
	);

	return true;
}

//void UIHandler::fillRndData()
//{
//	size_t counter = 0;
//	this->rndData.clear();
//	for (size_t i = 0; i < this->menu->nrMenuBoxes; i++)
//	{
//		if (this->menu->v_Box.at(i).ToRender)
//		{
//			UIData* tempUIData = new UIData();
//			tempUIData->GeoData = this->menu->v_Box.at(i).Background;
//			tempUIData->TxtData.wstring = this->menu->v_Box.at(i).TxtData.wstring;
//
//			this->rndData.push_back(tempUIData);
//			counter++;
//		};
//	}
//
//	this->nrOf = counter;
//}

UIHandler::UIHandler(ID2D1RenderTarget * p_rndTarget, ID2D1Factory * p_Factory)
{
	this->p_rndTarget = p_rndTarget;
	this->p_Factory = p_Factory;

	this->initResources();


	//this->rndData.clear();


	this->createPause();
	this->createOptions();


	this->createProgBars();

}

UIHandler::~UIHandler()
{
	this->cleanUp();
}

void UIHandler::cleanUp()
{
	this->textProgbars.clear();
	this->numbProgbars.clear();
	//delete this->p_DirectWriteFactory;
	//delete this->menu->boxStyle.p_colorBrush;
	//delete this->menu->boxStyle.p_textBrush;
	//delete this->menu;
	//delete this->tf_Buttons;
	//delete this->tf_Title;

	//this->rndData.clear();
}

bool UIHandler::openMenu(size_t index)
{
	for (size_t i = 0; i < this->a_menus[index]->nrMenuBoxes; i++)
	{
		this->a_menus[index]->v_Box.at(i).ToRender = true;
	}
	//this->fillRndData();
	this->currMenu = index;
	return false;
}

bool UIHandler::closeMenu(size_t index)
{
	for (size_t i = 0; i < this->a_menus[index]->nrMenuBoxes; i++)
	{
		this->a_menus[index]->v_Box.at(i).ToRender = false;
	}
	//this->fillRndData();
	this->currMenu = MEN_OFF;
	return false;
}

std::vector<UIData*> UIHandler::GETUIdata()
{
	

	return std::vector<UIData*>();
	//return this->rndData;
}

void UIHandler::drawData()
{
	//Draw the current menu
	bool drawMenu = false;
	if (currMenu != MEN_OFF)
	{
		for (auto i : this->a_menus[currMenu]->v_Box)
		{
			if (i.ToRender)
			{
				i.draw(this->p_rndTarget);
				drawMenu = true;
			}
		}

		// The menu is open
		if (drawMenu)
		{

			//Draw the title
			p_rndTarget->DrawText(
				this->a_menus[currMenu]->titleText.wstring.c_str(),
				wcslen(this->a_menus[currMenu]->titleText.wstring.c_str()),
				this->a_menus[currMenu]->titleText.textFormat,
				this->a_menus[currMenu]->titleRect,
				this->a_menus[currMenu]->p_textBrush
			);
		}
	}
	

	
	
	for (auto bar : this->textProgbars)
	{
		bar->update();
		p_Factory->CreateRectangleGeometry(
			bar->Front.getRect(),
			&bar->Front.p_rectGeom
		);
		bar->draw(this->p_rndTarget);
	}
	for (auto bar : this->numbProgbars)
	{
		bar->update();
		p_Factory->CreateRectangleGeometry(
			bar->Front.getRect(),
			&bar->Front.p_rectGeom
		);

		// not in update because of no subclass yet, 
		bar->TxtData.wstring = std::to_wstring(int((bar->startNumb * bar->filled))) + L"/" + std::to_wstring(bar->startNumb);

		bar->draw(this->p_rndTarget);
	}
}

void UIHandler::update()
{
	if (currMenu != MEN_OFF)
	{
		// Check to see if the button is to be highligthed
		POINT p;
		GetCursorPos(&p);
		if (ScreenToClient(Locator::getD3D()->GEThwnd(), &p))
		{
			int index = 0;
			for (auto i : a_menus[currMenu]->v_Box)
			{

				if (i.Background.pos.x < p.x && i.Background.pos.x + i.Background.size.x > p.x
					&&
					i.Background.pos.y < p.y && i.Background.pos.y + i.Background.size.y > p.y)
				{

					a_menus[currMenu]->v_Box.at(index).highligth = true;
					this->onButton = index; // Used to check what button is the currrent when pressing
				}
				else if (i.highligth)
				{
					a_menus[currMenu]->v_Box.at(index).highligth = false;
				}
				index++;
			}
		}
	}
	

	this->textProgbars.front()->modifBar(0.9995f);
	this->numbProgbars.front()->modifBar(0.996f);
}



ProgressBar * UIHandler::makeProgbar(std::wstring startString, DirectX::XMFLOAT2 pos, DirectX::XMFLOAT2 size, D2D1::ColorF bColor, D2D1::ColorF fColor, D2D1::ColorF tColor)
{
	ProgressBar* tempProg = new ProgressBar(pos, size, bColor, fColor, tColor);

	this->initProgBarGraph(tempProg);

	// Assign the textData
	tempProg->TxtData.textFormat = tf_Progrbar;
	tempProg->TxtData.wstring = startString;

	// Add to internal structure and return pointer
	this->textProgbars.push_back(tempProg);
	return tempProg;
}

ProgressBar * UIHandler::makeProgbarTimer(int startTime, DirectX::XMFLOAT2 pos, DirectX::XMFLOAT2 size, D2D1::ColorF bColor, D2D1::ColorF fColor, D2D1::ColorF tColor)
{
	ProgressBar* tempProg = new ProgressBar(pos, size, bColor, fColor, tColor);

	this->initProgBarGraph(tempProg);

	// Assign the textData
	tempProg->TxtData.textFormat = tf_Progrbar;
	tempProg->TxtData.wstring = std::to_wstring(startTime) + L"/" + std::to_wstring(startTime);

	// Add to internal structure and return pointer
	tempProg->startNumb = startTime;
	this->numbProgbars.push_back(tempProg);
	return tempProg;
}

ProgressBar * UIHandler::makeProgbarNumber(int maxValue, DirectX::XMFLOAT2 pos, DirectX::XMFLOAT2 size, D2D1::ColorF bColor, D2D1::ColorF fColor, D2D1::ColorF tColor)
{
	ProgressBar* tempProg = new ProgressBar(pos, size, bColor, fColor, tColor);

	this->initProgBarGraph(tempProg);

	// Assign the textData
	tempProg->TxtData.textFormat = tf_Progrbar;
	tempProg->TxtData.wstring = std::to_wstring(maxValue) + L"/" + std::to_wstring(maxValue);

	// Add to internal structure and return pointer
	tempProg->startNumb = maxValue;
	this->numbProgbars.push_back(tempProg);
	return tempProg;
}

