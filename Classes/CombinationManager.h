#ifndef __COMBINATION_MANAGER_H_
#define __COMBINATION_MANAGER_H_

#include "GameCards.h"
#include <vector>
#include <algorithm>
using namespace std;

enum Combinations
{
	KICKER,
	PAIR,
	TWO_PAIR,
	SET,
	STREET,
	FLASH,
	FULL_HOUSE,
	CARE,
	STEET_FLASH,
	ROYAL_FLASH
};

struct Combination
{
	Combinations comb;
	Card* card;
};

typedef vector<Card*> CardSet;

class CombinationManager
{
private:
	static bool compareByRange(const Card* a, const Card* b);

	static vector<CardSet> getCardsBySuite(CardSet &cardSet);
	static vector<CardSet> getCardsSequence(CardSet &cardSet);

	static Card* isFlashRoyal(CardSet &cardSet);
	static Card* isStreetFlash(CardSet &cardSet);
public:
	static Combination* getMaxCombination(CardSet &cardSet);

	CombinationManager();
};

#endif