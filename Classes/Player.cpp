#include "Player.h"

Player::Player(PlayerType pType)
{
	cards[0] = cards[1] = nullptr;
	this->money = START_MONEY;
	this->playerType = pType;
	this->betMoney = 0;
}

Player::~Player()
{
	delete(this->cards[0]);
	delete(this->cards[1]);
}

void Player::setCards(Card* card0, Card* card1)
{
	cards[0] = card0;
	cards[1] = card1;
}

void Player::setBet(int value)
{
	if (this->money - value >= 0)
	{
		this->money -= value;
		this->betMoney += value;
	}
}