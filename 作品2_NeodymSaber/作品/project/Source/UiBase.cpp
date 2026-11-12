#include "UiBase.h"

UiBase::UiBase()
{
	hImage = -1;
	imageSizeX = 0;
	imageSizeY = 0;
}

 UiBase::UiBase(VECTOR2I Pos, int image)
{
	pos = Pos;
	hImage = image;
}

UiBase::~UiBase()
{
}
