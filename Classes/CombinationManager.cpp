#include "CombinationManager.h"

bool CombinationManager::compareByRange(const Card* a, const Card* b)
{
	return a->range < b->range;
}

vector<CardSet> CombinationManager::getCardsBySuite(CardSet &cardSet)
{
	vector<CardSet> t;
	t.resize(SUITE_COUNT);
	
	for (CardSet::iterator i = cardSet.begin(); i != cardSet.end(); i++)
	{
		Card* card = *i;
		t[card->suite].push_back(card);
	}

	return t;
}

vector<CardSet> CombinationManager::getCardsSequence(CardSet &cardSet)
{
	vector<CardSet> t;
	CardSet *curr = new CardSet;
	(*curr).push_back(cardSet[0]);
	for (int i = 1; i < cardSet.size(); i++)
	{
		if (cardSet[i]->range - cardSet[i - 1]->range == 1)
			(*curr).push_back(cardSet[i]);
		else
		{
			t.push_back(*curr);
			curr = new CardSet;
			(*curr).push_back(cardSet[i]);
		}
	}
	t.push_back(*curr);
	return t;
}

Card* CombinationManager::isFlashRoyal(CardSet &cardSet)
{
	vector<CardSet> cardsBySuite = CombinationManager::getCardsBySuite(cardSet);

	for (vector<CardSet>::iterator i = cardsBySuite.begin(); i != cardsBySuite.end(); i++)
	{
		CardSet cards = *i;
		if (cards.empty())
			continue;

		vector<CardSet> cardSequences = CombinationManager::getCardsSequence(cards);
		for (vector<CardSet>::reverse_iterator j = cardSequences.rbegin(); j != cardSequences.rend(); j++)
		{
			CardSet sequence = *j;
			if (sequence.size() >= 5 && sequence[sequence.size() - 1]->range == Range::CARD_A)
				return sequence[sequence.size() - 1];
		}
	}

	return nullptr;
}

Card* CombinationManager::isStreetFlash(CardSet &cardSet)
{
	vector<CardSet> cardsBySuite = CombinationManager::getCardsBySuite(cardSet);

	for (vector<CardSet>::iterator i = cardsBySuite.begin(); i != cardsBySuite.end(); i++)
	{
		CardSet cards = *i;
		if (cards.empty())
			continue;

		vector<CardSet> cardSequences = CombinationManager::getCardsSequence(cards);
		for (vector<CardSet>::reverse_iterator j = cardSequences.rbegin(); j != cardSequences.rend(); j++)
		{
			CardSet sequence = *j;
			if (sequence.size() >= 5)
				return sequence[sequence.size() - 1];
		}
	}

	return nullptr;
}

Combination* CombinationManager::getMaxCombination(CardSet &cardSet)
{
	Combination* res = new Combination;
	Card* highCard;

	CardSet tCardSet(cardSet.begin(), cardSet.end());
	sort(tCardSet.begin(), tCardSet.end(), CombinationManager::compareByRange);
	
	//if royal flash
	highCard = CombinationManager::isFlashRoyal(tCardSet);
	if (highCard != NULL)
	{
		res->comb = Combinations::ROYAL_FLASH;
		res->card = highCard;
		return res;
	}

	//if street flash
	highCard = CombinationManager::isStreetFlash(tCardSet);
	if (highCard != NULL)
	{
		res->comb = Combinations::STEET_FLASH;
		res->card = highCard;
		return res;
	}



	return nullptr;
}

Card* GET_CARD( Suite suite, Range range )
{
	Card* c = new Card;
	c->suite = suite;
	c->range = range;

	return c;
}

CombinationManager::CombinationManager()
{
	CardSet cset;

	cset.push_back(GET_CARD(Suite::SUITE_CLUBS, Range::CARD_2));
	cset.push_back(GET_CARD(Suite::SUITE_DIAMONDS, Range::CARD_9));
	//cset.push_back(GET_CARD(Suite::SUITE_DIAMONDS, Range::CARD_J));
	cset.push_back(GET_CARD(Suite::SUITE_DIAMONDS, Range::CARD_K));
	cset.push_back(GET_CARD(Suite::SUITE_DIAMONDS, Range::CARD_Q));
	//cset.push_back(GET_CARD(Suite::SUITE_DIAMONDS, Range::CARD_A));
	cset.push_back(GET_CARD(Suite::SUITE_DIAMONDS, Range::CARD_10));


	CombinationManager::getMaxCombination(cset);
}