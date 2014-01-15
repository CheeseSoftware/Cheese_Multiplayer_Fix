#pragma once
#include "LargeTextureBlock.h"
#include "SolidBlock.h"

class Stone
	: public LargeTextureBlock
	, public SolidBlock
{
public:
	virtual unsigned short getTextureId(App &const app, const unsigned short metadata) const;
	virtual unsigned char getLayer() const;
	virtual const char *const getTextureName() const;
	virtual unsigned const short getTextureSize() const;
};