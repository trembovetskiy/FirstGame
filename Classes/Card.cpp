#include "Card.h"
USING_NS_CC;

CardSprite::CardSprite(std::string textureName, CardPlace place)
{
	this->textureName = textureName;
	this->place = place;
}

CardSprite* CardSprite::createCard(Card* card, CardPlace place)
{
	std::string txName = getTextureName(card);
	CardSprite* cardSprite = new CardSprite(txName, place);

	if (cardSprite && cardSprite->initWithFile(SHIRT_TEXTURE_NAME))
	{
		cardSprite->autorelease();
		cardSprite->setScale( CARD_SCALE );
		cardSprite->setPosition(getCardPosition(CardPlace::PACK));
		return cardSprite;
	}

	CC_SAFE_DELETE(cardSprite);
	return NULL;
}

std::string CardSprite::getTextureName(Card* card)
{
	std::string suite = SUITE_NAMES[card->suite];
	std::string range = RANGE_NAMES[card->range];
	return "cards\\" + range + "_of_" + suite + ".png";
}

Vec2 CardSprite::getCardPosition(CardPlace place)
{
	Vec2 pos = TABLE_BEGIN_POSITION;
	if (place <= CardPlace::COMP_1)
	{
		pos.y += TABLE_DELTA_Y;
		pos.x += TABLE_DELTA_X * ( place + 1.5f );
	}
	else if (place <= CardPlace::USER_1)
	{
		pos.y -= TABLE_DELTA_Y;
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


void CardSprite::animate(float firstDelay)
{
	DelayTime* delayAction = DelayTime::create(firstDelay);
	MoveTo* move = MoveTo::create(MOVE_CARD_DURATION, CardSprite::getCardPosition(this->place));
	auto callback = CallFunc::create([this]() {
		if ( this->place > CardPlace::COMP_1 )
			this->showCard();
	});

	Sequence* seq = Sequence::create(delayAction, move, callback, nullptr);
	this->runAction(seq);
}

void CardSprite::showCard()
{
	this->initWithFile(this->textureName);
}
