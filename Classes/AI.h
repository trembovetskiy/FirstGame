#ifndef __AI_H_
#define __AI_H_

#include <vector>
#include "Player.h"
#include "Config.h"

class AI
{
public:
	static Turn* getTurn(Player* player, std::vector<Card*> table, std::vector<Turn*> allowTurns);
};

#endif