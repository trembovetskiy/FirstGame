#ifndef _PLAYER_H
#define _PLAYER_H

#include "Config.h"

class Player
{
private:
	Card* cards[2];
	int money;
	int betMoney;
	PlayerType playerType;
public:
	Player(PlayerType pType);
	~Player();

	void setCards(Card* card0, Card* card1);
	void setBet(int value);

	int getMoney() { return money; }
	int getBetMoney() { return betMoney; }
	PlayerType getType() { return playerType; }
	Card* getCard(int index) { return cards[index]; }
};

#endif