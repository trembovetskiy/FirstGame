#include "Player.h"

Player::Player()
{
	cards[0] = cards[1] = nullptr;
	this->money = START_MONEY;
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

float Player::getMoney()
{
	return this->money;
}