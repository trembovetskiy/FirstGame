#ifndef _PLAYER_H
#define _PLAYER_H

#include "Config.h"

class Player
{
private:
	Card* cards[2];
	float money;
public:
	Player();
	~Player();

	void setCards(Card* card0, Card* card1);
	float getMoney();
};

#endif