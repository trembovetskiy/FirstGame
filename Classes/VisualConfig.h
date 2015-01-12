#ifndef _VISUAL_CONFIG_H
#define _VISUAL_CONFIG_H

#include "cocos2d.h"
using namespace cocos2d;

#define CARD_SCALE 0.5

enum CardPlace{
	COMP_0,
	COMP_1,

	USER_0,
	USER_1,

	TABLE_0,
	TABLE_1,
	TABLE_2,
	TABLE_3,
	TABLE_4,

	PACK
} ;

const Vec2 TABLE_BEGIN_POSITION = Vec2(100, 300);
const float TABLE_DELTA_X = 100;
const float TABLE_DELTA_Y = 120;

#define MOVE_CARD_DURATION 0.5
#define MIDDLE_CARD_DELAY 0.5
#define SHIRT_TEXTURE_NAME "image/card_shirt.png"

#endif