#ifndef _CARDPOOL_H
#define _CARDPOOL_H

#include "Config.h"
#include <list>

class CardPool
{
private:
	std::list<Card*> pool;
	static CardPool* instance;
public:
	CardPool();
	~CardPool();

	static CardPool* getInstance();
	Card* getRandomCard();
};

#endif