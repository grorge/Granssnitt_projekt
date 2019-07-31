#include "UIHandler.h"
#include "Locator.h"

void UIHandler::initResources()
{
	static const WCHAR msc_fontName[] = L"Script"; // Verdana, Rockwell, Agency FB, Script
	static const FLOAT msc_fontSize = 20;

	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown **>(&this->p_DirectWriteFactory)
	);

	// Create a DirectWrite text format object.
	this->p_DirectWriteFactory->CreateTextFormat(
		msc_fontName,
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		msc_fontSize,
		L"en-us", //L"", //locale
		&this->p_TextFormat
	);

	// Center the text horizontally and vertically.
	this->p_TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

	this->p_TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
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
		D2D1::ColorF(D2D1::ColorF::GreenYellow), D2D1::ColorF(D2D1::ColorF::Black)
	);

	// Creates the colors
	this->p_rndTarget->CreateSolidColorBrush(D2D1::ColorF(this->menu->bColor), &this->menu->boxStyle.p_colorBrush);
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
		tempMenuBox.TxtData.textFormat = this->p_TextFormat;
		this->menu->v_Box.push_back(tempMenuBox);
	}

	// Change the text of each box
	this->menu->setText(0, L"Start");
	this->menu->setText(1, L"Options");
	this->menu->setText(2, L"Exit");


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
	for (auto i : this->menu->v_Box)
	{
		if (i.ToRender)
			i.draw(this->p_rndTarget);
	}
}
