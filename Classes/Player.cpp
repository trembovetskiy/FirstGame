#include "Player.h"

Player::Player(PlayerType pType)
{
	cards[0] = cards[1] = nullptr;
	this->money = START_MONEY;
	this->playerType = pType;
	this->betMoney = 0;
	this->currentTurn = nullptr;
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

std::vector<Turn*> Player::getAllowTurns(Player* enemyPlayer)
{
	std::vector<Turn*> res;
	Turn* t;

	if (this->money == 0)
		return res;

	if (this->betMoney == enemyPlayer->getBetMoney())
	{
		t = new Turn;
		t->turn = Turns::TURN_CHECK;
		t->value = 0;
		res.push_back(t);
	}
		
	else
	{
		t = new Turn;
		t->turn = Turns::TURN_CALL;
		t->value = enemyPlayer->getBetMoney() - this->betMoney;
		res.push_back(t);
	}
		

	if (this->money > enemyPlayer->getBetMoney() - this->betMoney)
	{
		t = new Turn;
		t->turn = Turns::TURN_RAISE;
		t->value = this->money;
		res.push_back(t);
	}
		
	t = new Turn;
	t->turn = Turns::TURN_FOLD;
	t->value = 0;
	res.push_back(t);

	return res;
}

void Player::setTurn(Turn* turn)
{
	this->currentTurn = turn;
	this->setBet(this->currentTurn->value);
}

int Player::releaseTurn()
{
	this->currentTurn = nullptr;
	int t = this->betMoney;
	this->betMoney = 0;
	return t;
}

void Player::reset()
{
	delete(this->cards[0]);
	delete(this->cards[1]);
	cards[0] = cards[1] = nullptr;
}