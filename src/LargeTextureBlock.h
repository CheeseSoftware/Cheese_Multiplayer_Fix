#include "Block.h"

class LargeTextureBlock : public virtual Block
{
public:
	virtual unsigned const short getTextureSize() const=0;
	#ifndef _SERVER
	void Draw(const long posX, const long posY, App &app, GameUtility *gameUtility, const unsigned short metadata);
#endif
};