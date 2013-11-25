#include "LargeTextureBlock.h"
#include "GameUtility.h"
#include <math.h>

#ifndef _SERVER
void LargeTextureBlock::Draw(const long posX, const long posY, App &app, GameUtility *gameUtility, const unsigned short metadata)
{
	sf::Sprite *tempSprite = &gameUtility->getBlockRegister().getBlockTextures(this)
		[getTextureId(app, metadata)//*getTextureSize()*getTextureSize()
		//+(((short)floor(abs((posY < 0)? ~posY:posY)/16.0))%getTextureSize())*getTextureSize()
		];//+(((short)floor(abs((posX < 0)? ~posX:posX)/16.0))%getTextureSize())];

		/*tempSprite->setTextureRect(sf::IntRect
		(((posX < 0)? 16*getTextureSize()-16:0)+posX%(16*getTextureSize())
		,((posY < 0)? 16*getTextureSize()-16:0)+posY%(16*getTextureSize())
		, 16, 16));*/

		tempSprite->setTextureRect(sf::IntRect
		(posX
		,posY
		, 16, 16));

	if (tempSprite != nullptr)
	{
		tempSprite->setPosition(posX, posY);
		app.draw(*tempSprite);
	}
}
#endif