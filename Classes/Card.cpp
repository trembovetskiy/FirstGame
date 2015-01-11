#include "Card.h"
USING_NS_CC;

CardSprite* CardSprite::createCard(Card card, CardPlace place)
{
	CardSprite* cardSprite = new CardSprite();
	std::string textureName = getTextureName(card);
	Vec2 pos = getCardPosition(place);

	if ( cardSprite && cardSprite->initWithFile( textureName ) )
	{
		cardSprite->autorelease();
		cardSprite->setScale( CARD_SCALE );
		cardSprite->setPosition(pos.x, pos.y);
		return cardSprite;
	}

	CC_SAFE_DELETE(cardSprite);
	return NULL;
}

std::string CardSprite::getTextureName(Card card)
{
	std::string suite = SUITE_NAMES[card.suite];
	std::string range = RANGE_NAMES[card.range];
	return "cards\\" + range + "_of_" + suite + ".png";
}

Vec2 CardSprite::getCardPosition(CardPlace place)
{
	Vec2 pos = TABLE_BEGIN_POSITION;
	if (place <= CardPlace::COMP_1)
	{
		pos.y -= TABLE_DELTA_Y;
		pos.x += TABLE_DELTA_X * ( place + 1.5f );
	}
	else if (place <= CardPlace::USER_1)
	{
		pos.y += TABLE_DELTA_Y;
		pos.x += TABLE_DELTA_X * (place - 2.0f + 1.5f);
	}
	else if (place <= CardPlace::PACK)
	{
		pos.x += TABLE_DELTA_X * (place - 4);
	}
	else
	{
		pos.x += TABLE_DELTA_X * (place - 3);
	}
	
	return pos;
}

