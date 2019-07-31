#include "UIHandler.h"
#include "Locator.h"

void UIHandler::initResources()
{
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

	this->menu = new MenuInfo(
		5,
		middlePoint, sizeFloat, 5.0f,
		D2D1::ColorF(D2D1::ColorF::Green), D2D1::ColorF(D2D1::ColorF::GreenYellow), D2D1::ColorF(D2D1::ColorF::Red)
	);

	// Creates the colors
	this->p_rndTarget->CreateSolidColorBrush(D2D1::ColorF(this->menu->bColor), &this->menu->boxStyle.p_colorBrush);
	this->p_rndTarget->CreateSolidColorBrush(D2D1::ColorF(this->menu->bHighColor), &this->menu->boxStyle.p_highligthColorBrush);
	this->p_rndTarget->CreateSolidColorBrush(D2D1::ColorF(this->menu->tColor), &this->menu->boxStyle.p_textBrush);


	//---------------------------------------------------

	//Create the boxes
	this->menu->v_Box.clear();
	for (size_t i = 0; i < this->menu->nrMenuBoxes; i++)
	{
		MenuBox tempMenuBox;
		tempMenuBox.Background.copyStyle(&this->menu->boxStyle);
		tempMenuBox.Background.pos =
			DirectX::XMFLOAT2(
				this->menu->pos.x,
				this->menu->pos.y + (i * (this->menu->boxStyle.size.y + (this->menu->boxStyle.padding)))
			);
		tempMenuBox.Background.setRect();

		p_Factory->CreateRectangleGeometry(
			tempMenuBox.Background.getRect(),
			&tempMenuBox.Background.p_rectGeom
		);

		tempMenuBox.ToRender = false;
		tempMenuBox.TxtData.wstring = L"NOTHING ASSINGED";
		tempMenuBox.TxtData.textFormat = this->tf_Buttons;
		this->menu->v_Box.push_back(tempMenuBox);
	}

	// Change the text of each box
	this->menu->setText(0, L"Start");
	this->menu->setText(1, L"Options");
	this->menu->setText(2, L"Exit");


	//---------------------------------------------------

	//Create the Title

	// Set the rect to a space from the top to the start of the buttons
	this->menu->titleRect = D2D1::RectF(this->menu->pos.x, 0, this->menu->pos.x + this->menu->boxStyle.size.x, this->menu->pos.y);
	this->menu->titleText.textFormat = this->tf_Title;
	this->menu->titleText.wstring = L"PAUSE";

	return true;
}

void UIHandler::fillRndData()
{
	size_t counter = 0;
	this->rndData.clear();
	for (size_t i = 0; i < this->menu->nrMenuBoxes; i++)
	{
		if (this->menu->v_Box.at(i).ToRender)
		{
			UIData* tempUIData = new UIData();
			tempUIData->GeoData = this->menu->v_Box.at(i).Background;
			tempUIData->TxtData.wstring = this->menu->v_Box.at(i).TxtData.wstring;

			this->rndData.push_back(tempUIData);
			counter++;
		};
	}

	this->nrOf = counter;
}

UIHandler::UIHandler(ID2D1RenderTarget * p_rndTarget, ID2D1Factory * p_Factory)
{
	this->p_rndTarget = p_rndTarget;
	this->p_Factory = p_Factory;

	this->initResources();


	this->rndData.clear();


	this->createPause();

}

UIHandler::~UIHandler()
{
}

void UIHandler::cleanUp()
{
	delete this->p_DirectWriteFactory;
	//delete this->menu->boxStyle.p_colorBrush;
	//delete this->menu->boxStyle.p_textBrush;
	//delete this->menu;
	//delete this->tf_Buttons;
	//delete this->tf_Title;

	//this->rndData.clear();
}

bool UIHandler::openMenu(size_t index)
{
	for (size_t i = 0; i < this->menu->nrMenuBoxes; i++)
	{
		this->menu->v_Box.at(i).ToRender = true;
	}
	this->fillRndData();
	return false;
}

bool UIHandler::closeMenu(size_t index)
{
	for (size_t i = 0; i < this->menu->nrMenuBoxes; i++)
	{
		this->menu->v_Box.at(i).ToRender = false;
	}
	this->fillRndData();
	return false;
}

std::vector<UIData*> UIHandler::GETUIdata()
{
	

	return this->rndData;
}

void UIHandler::drawData()
{
	//Draw the current menu
	bool drawMenu = false;
	for (auto i : this->menu->v_Box)
	{
		if (i.ToRender)
		{
			i.draw(this->p_rndTarget);
			drawMenu = true;
		}
	}

	// Draw title
	if (drawMenu)
	{
		p_rndTarget->DrawText(
			this->menu->titleText.wstring.c_str(),
			wcslen(this->menu->titleText.wstring.c_str()),
			this->menu->titleText.textFormat,
			this->menu->titleRect,
			this->menu->boxStyle.p_textBrush
		);
	}
	
}
