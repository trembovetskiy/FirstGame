#ifndef _PLAYER_H
#define _PLAYER_H

#include "Config.h"

class Player
{
private:
	Card* cards[2];
public:
	Player(Card* card0, Card* card1);
};

#endif