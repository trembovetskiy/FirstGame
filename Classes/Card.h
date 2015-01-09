#ifndef _CARD_HPP
#define _CARD_HPP

#include "GameCards.h"
#include "VisualConfig.h"
#include "cocos2d.h"
using namespace cocos2d;




class CardSprite: public cocos2d::CCSprite
{
private:
	Card card;

	static std::string getTextureName(Card card);
	static Vec2 getCardPosition(CardPlace place);

public:
	static CardSprite* createCard(Card card, CardPlace place);
};
#endif

