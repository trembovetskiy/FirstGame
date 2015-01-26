#ifndef __COMBINATION_MANAGER_H_
#define __COMBINATION_MANAGER_H_

#include "GameCards.h"
#include "Player.h"
#include <vector>
#include <algorithm>
using namespace std;

enum GameResult
{
	WIN,
	HALF,
	FAIL
};

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
	STREET_FLASH,
	ROYAL_FLASH
};

struct Combination
{
	Combinations comb;
	Card* card;
	Card* secondCard;
};

typedef vector<Card*> CardSet;

class CombinationManager
{
private:
	static bool compareByRange(const Card* a, const Card* b);

	static vector<CardSet> getCardsBySuite(CardSet &cardSet);
	static vector<CardSet> getCardsSequence(CardSet &cardSet);
	static vector<CardSet> getCardsByRange(CardSet &cardSet);

	static Card* isFlashRoyal(CardSet &cardSet);
	static Card* isStreetFlash(CardSet &cardSet);
	static Card* isCare(CardSet &cardSet);
	static pair<Card*,Card*> isFullHouse(CardSet &cardSet);
	static Card* isFlash(CardSet &cardSet);
	static Card* isStreet(CardSet &cardSet);
	static Card* isSet(CardSet &cardSet);
	static pair<Card*, Card*> isTwoPair(CardSet &cardSet);
	static Card* isPair(CardSet &cardSet);

	static Combination* getMaxCombination(CardSet &cardSet);
public:
	static Combination* getCurrentCombination(Player* player, CardSet& tableCards);
	static GameResult getGameResult(Player* user, Player* comp, CardSet& tableCards);

};

#endif