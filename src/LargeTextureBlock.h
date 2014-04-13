#pragma once
#include "Block.h"

class LargeTextureBlock : public virtual Block
{
public:
	virtual unsigned const short getTextureSize() const=0;
	#ifdef CLIENT
	void Draw(const long posX, const long posY, App &app, Game *game, GameUtility *gameUtility, const unsigned short metadata);
#endif
};