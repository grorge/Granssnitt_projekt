#include "MenuStructs.h"

void MenuBox::draw(ID2D1RenderTarget * p_rndTarget)
{
	p_rndTarget->DrawGeometry(this->Background.p_rectGeom, this->Background.p_colorBrush);
	p_rndTarget->FillGeometry(this->Background.p_rectGeom, this->Background.p_colorBrush);

	//Draw the Text
	p_rndTarget->DrawText(
		this->TxtData.wstring.c_str(),
		wcslen(this->TxtData.wstring.c_str()),
		this->TxtData.textFormat,
		this->Background.getPadRect(),
		this->Background.p_textBrush
	);
}
