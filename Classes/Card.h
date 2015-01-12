#ifndef _CARD_HPP
#define _CARD_HPP

#include "Config.h"
#include "cocos2d.h"
using namespace cocos2d;


class CardSprite: public cocos2d::CCSprite
{
private:
	std::string textureName;
	CardPlace place;

	static std::string getTextureName(Card* card);
public:
	CardSprite(std::string textureName, CardPlace place);

	void animate(float firstDelay);
	void showCard();

	static CardSprite* createCard(Card* card, CardPlace place);
	static Vec2 getCardPosition(CardPlace place);	
};
#endif

