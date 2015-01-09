#ifndef _GAMECARDS_H
#define _GAMECARDS_H
#include <string>

typedef enum{
	SUITE_CLUBS, //
	SUITE_DIAMONDS, //
	SUITE_HEARTS, //
	SUITE_SPADES //
} Suite;

const int SUITE_COUNT = 4;


const std::string SUITE_NAMES[] =
{ 
	"clubs"
,	"diamonds"
,	"hearts"
,	"spades"
};

typedef enum{
	CARD_2,
	CARD_3,
	CARD_4,
	CARD_5,
	CARD_6,
	CARD_7,
	CARD_8,
	CARD_9,
	CARD_10,
	CARD_J,
	CARD_Q,
	CARD_K,
	CARD_A
} Range;

const int RANGE_COUNT = 13;

const std::string RANGE_NAMES[] =
{
	"2"
	, "3"
	, "4"
	, "5"
	, "6"
	, "7"
	, "8"
	, "9"
	, "10"
	, "jack"
	, "queen"
	, "king"
	, "ace"
};

struct Card
{
	Suite suite;
	Range range;
};

#endif