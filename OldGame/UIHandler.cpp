#include "UIHandler.h"
#include "Locator.h"

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
		tempMenuBox.Text = L"NOTHING ASSINGED";
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
	for (size_t i = 0; i < this->menu->nrMenuBoxes; i++)
	{
		if (this->menu->v_Box.at(i).ToRender)
		{
			UIData tempUIData;
			tempUIData.GeoData = this->menu->v_Box.at(i).Background;
			tempUIData.TxtData.wstring = this->menu->v_Box.at(i).Text;

			this->rndData[counter] = tempUIData;
			counter++;
		};
	}

	this->nrOf = counter;
}

UIHandler::UIHandler(ID2D1RenderTarget * p_rndTarget, ID2D1Factory * p_Factory)
{
	this->p_rndTarget = p_rndTarget;
	this->p_Factory = p_Factory;

	this->rndData = new UIData();


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

UIData * UIHandler::GETUIdata()
{
	

	return this->rndData;
}
