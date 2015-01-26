#include "CardPool.h"
using namespace std;


CardPool::CardPool()
{
	for (int i = SUITE_CLUBS; i <= SUITE_SPADES; i++)
		for (int j = CARD_2; j <= CARD_A; j++)
		{
			Card* card = new Card;
			card->suite = (Suite)i;
			card->range = (Range)j;
			pool.push_back(card);
		}
}

CardPool::~CardPool()
{
	for (std::list<Card*>::iterator i = pool.begin(); i != pool.end(); i++)
		delete(*i);
}

CardPool* CardPool::instance = nullptr;

CardPool* CardPool::getInstance()
{
	if (instance == NULL)
	{
		instance = new CardPool();
	};

	return instance;
}

Card* CardPool::getRandomCard()
{
	int cardCount = pool.size();
	int index = rand() % cardCount;
	std::list<Card*>::iterator i = pool.begin();
	for (int j = 0; j < index; j++)
	{
		i++;
	};
	Card* card = *(i);
	pool.erase(i);

	return card;
}

void CardPool::reset()
{
	pool.clear();
	for (int i = SUITE_CLUBS; i <= SUITE_SPADES; i++)
	for (int j = CARD_2; j <= CARD_A; j++)
	{
		Card* card = new Card;
		card->suite = (Suite)i;
		card->range = (Range)j;
		pool.push_back(card);
	}
}

