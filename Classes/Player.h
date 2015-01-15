#ifndef _PLAYER_H
#define _PLAYER_H

#include "Config.h"
#include <vector>

enum Turns
{
	TURN_CHECK,
	TURN_CALL,
	TURN_RAISE,
	TURN_FOLD
};

struct Turn
{
	Turns turn;
	int value;
};

class Player
{
private:
	Card* cards[2];
	int money;
	int betMoney;
	PlayerType playerType;
	Turn* currentTurn;

	int callValue;
public:
	Player(PlayerType pType);
	~Player();

	void setCards(Card* card0, Card* card1);
	void setBet(int value);
	std::vector<Turn*> getAllowTurns(Player* enemyPlayer);
	void setTurn(Turn* turn);
	int releaseTurn();

	int getMoney() { return money; }
	int getBetMoney() { return betMoney; }
	PlayerType getType() { return playerType; }
	Card* getCard(int index) { return cards[index]; }
	Turn* getCurrentTurn() { return currentTurn; }
};

#endif