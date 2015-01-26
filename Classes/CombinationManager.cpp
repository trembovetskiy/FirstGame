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

vector<CardSet> CombinationManager::getCardsByRange(CardSet &cardSet)
{
	vector<CardSet> t;
	t.resize(RANGE_COUNT);

	for (CardSet::iterator i = cardSet.begin(); i != cardSet.end(); i++)
	{
		Card* card = *i;
		t[card->range].push_back(card);
	}

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
			if ( sequence.size() >= 5 ||
				 (sequence.size() == 4 && sequence[3]->range == Range::CARD_5 && cards[cards.size() - 1]->range == Range::CARD_A) )
				return sequence[sequence.size() - 1];
		}
	}

	return nullptr;
}

Card* CombinationManager::isCare(CardSet &cardSet)
{
	vector<CardSet> cardsByRange = CombinationManager::getCardsByRange(cardSet);
	
	for (vector<CardSet>::reverse_iterator i = cardsByRange.rbegin(); i != cardsByRange.rend(); i++)
	{
		if ((*i).size() == 4)
			return (*i)[0];
	}

	return nullptr;
}

pair<Card*, Card*> CombinationManager::isFullHouse(CardSet &cardSet)
{
	pair<Card*, Card*> res;
	res.first = nullptr;

	vector<CardSet> cardsByRange = CombinationManager::getCardsByRange(cardSet);

	int threeIndex = -1;
	int j = cardsByRange.size() - 1;
	for (vector<CardSet>::reverse_iterator i = cardsByRange.rbegin(); i != cardsByRange.rend(); i++)
	{
		if ((*i).size() == 3)
		{
			threeIndex = j;
			res.first = (*i)[0];
			break;
		}
		j--;
	}

	if (threeIndex == -1)
		return res;

	j = cardsByRange.size() - 1;
	for (vector<CardSet>::reverse_iterator i = cardsByRange.rbegin(); i != cardsByRange.rend(); i++)
	{
		if ( threeIndex != j && (*i).size() >= 2)
		{
			threeIndex = j;
			res.second = (*i)[0];
			return res;
		}
		j--;
	}
	
	res.first = nullptr;
	return res;
}

Card* CombinationManager::isFlash(CardSet &cardSet)
{
	vector<CardSet> cardsBySuite = CombinationManager::getCardsBySuite(cardSet);

	for (vector<CardSet>::iterator i = cardsBySuite.begin(); i != cardsBySuite.end(); i++)
	{
		CardSet cards = *i;
		if (cards.size() >= 5)
			return cards[cards.size() - 1];
	}

	return nullptr;
}

 Card* CombinationManager::isStreet(CardSet &cardSet)
{
	vector<CardSet> cardsByRange = CombinationManager::getCardsByRange(cardSet);
	CardSet cards;
	for (vector<CardSet>::iterator i = cardsByRange.begin(); i != cardsByRange.end(); i++)
	{
		if ((*i).size() > 0)
			cards.push_back((*i)[0]);
	}
	
	vector<CardSet> cardSequences = CombinationManager::getCardsSequence(cards);
	for (vector<CardSet>::reverse_iterator j = cardSequences.rbegin(); j != cardSequences.rend(); j++)
	{
		CardSet sequence = *j;
		if (sequence.size() >= 5 ||
			(sequence.size() == 4 && sequence[3]->range == Range::CARD_5 && cards[cards.size() - 1]->range == Range::CARD_A))
			return sequence[sequence.size() - 1];
	}

	return nullptr;
}

 Card* CombinationManager::isSet(CardSet &cardSet)
 {
	 vector<CardSet> cardsByRange = CombinationManager::getCardsByRange(cardSet);

	 for (vector<CardSet>::reverse_iterator i = cardsByRange.rbegin(); i != cardsByRange.rend(); i++)
	 {
		 if ((*i).size() == 3)
			 return (*i)[0];
	 }

	 return nullptr;
 }

 pair<Card*, Card*> CombinationManager::isTwoPair(CardSet &cardSet)
 {
	 pair<Card*, Card*> res;
	 res.first = nullptr;

	 vector<CardSet> cardsByRange = CombinationManager::getCardsByRange(cardSet);

	 int threeIndex = -1;
	 int j = cardsByRange.size() - 1;
	 for (vector<CardSet>::reverse_iterator i = cardsByRange.rbegin(); i != cardsByRange.rend(); i++)
	 {
		 if ((*i).size() == 2)
		 {
			 threeIndex = j;
			 res.first = (*i)[0];
			 break;
		 }
		 j--;
	 }

	 if (threeIndex == -1)
		 return res;

	 j = cardsByRange.size() - 1;
	 for (vector<CardSet>::reverse_iterator i = cardsByRange.rbegin(); i != cardsByRange.rend(); i++)
	 {
		 if (threeIndex != j && (*i).size() == 2)
		 {
			 threeIndex = j;
			 res.second = (*i)[0];
			 return res;
		 }
		 j--;
	 }

	 res.first = nullptr;
	 return res;
 }

Card* CombinationManager::isPair(CardSet &cardSet)
 {
	 vector<CardSet> cardsByRange = CombinationManager::getCardsByRange(cardSet);

	 for (vector<CardSet>::reverse_iterator i = cardsByRange.rbegin(); i != cardsByRange.rend(); i++)
	 {
		 if ((*i).size() == 2)
			 return (*i)[0];
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
		res->comb = Combinations::STREET_FLASH;
		res->card = highCard;
		return res;
	}

	//if care
	highCard = CombinationManager::isCare(tCardSet);
	if (highCard != NULL)
	{
		res->comb = Combinations::CARE;
		res->card = highCard;
		return res;
	}

	//if full house
	pair<Card*, Card*> p = CombinationManager::isFullHouse(tCardSet);
	if (p.first != NULL)
	{
		res->comb = Combinations::FULL_HOUSE;
		res->card = p.first;
		res->secondCard = p.second;
		return res;
	}

	//if flash
	highCard = CombinationManager::isFlash(tCardSet);
	if (highCard != NULL)
	{
		res->comb = Combinations::FLASH;
		res->card = highCard;
		return res;
	}

	//if street
	highCard = CombinationManager::isStreet(tCardSet);
	if (highCard != NULL)
	{
		res->comb = Combinations::STREET;
		res->card = highCard;
		return res;
	}

	//if set
	highCard = CombinationManager::isSet(tCardSet);
	if (highCard != NULL)
	{
		res->comb = Combinations::SET;
		res->card = highCard;
		return res;
	}

	//if two pairs
	p = CombinationManager::isTwoPair(tCardSet);
	if (p.first != NULL)
	{
		res->comb = Combinations::TWO_PAIR;
		res->card = p.first;
		res->secondCard = p.second;
		return res;
	}

	//if pair
	highCard = CombinationManager::isPair(tCardSet);
	if (highCard != NULL)
	{
		res->comb = Combinations::PAIR;
		res->card = highCard;
		return res;
	}

	return nullptr;
}

Combination* CombinationManager::getCurrentCombination(Player* player, CardSet& tableCards)
{
	Card* card0 = player->getCard(0);
	Card* card1 = player->getCard(1);
	if (card0 == NULL || card1 == NULL)
		return nullptr;

	CardSet tSet(tableCards.begin(), tableCards.end());	

	tSet.push_back(card0);
	tSet.push_back(card1);

	Combination* res = CombinationManager::getMaxCombination(tSet);

	if (res == NULL)
	{
		res = new Combination;
		res->comb = Combinations::KICKER;
		res->card = card0->range > card1->range ? card0 : card1;
	}

	return res;
}

GameResult CombinationManager::getGameResult(Player* user, Player* comp, CardSet& tableCards)
{
	Combination* userComb = CombinationManager::getCurrentCombination(user, tableCards);
	Combination* compComb = CombinationManager::getCurrentCombination(comp, tableCards);
	if (userComb->comb > compComb->comb)
		return GameResult::WIN;
	else if (userComb->comb < compComb->comb)
		return GameResult::FAIL;
	else
	{
		if (userComb->card > compComb->card)
			return GameResult::WIN;
		else if (userComb->card < compComb->card)
			return GameResult::FAIL;
		else
			return GameResult::HALF;
	}
}