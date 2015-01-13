#ifndef _GAMEMECHANIC_H
#define _GAMEMECHANIC_H

#include "Player.h"
#include "CardPool.h"
#include "GameScene.h"
#include "CombinationManager.h"
#include <vector>
using namespace std;

enum GameState{
	BEGIN_STATE,
	PREFLOP,
	FLOP,
	TURN,
	RIVER
};

class GameMechanic
{
private:
	Player* comp;
	Player* user;
	vector<Card*> tableCards;
	GameState state;
	bool compFirst;

	void toPreflopState();

	static GameMechanic* instance;
public:
	GameMechanic();
	~GameMechanic();
	
	void incrementState();

	Player* getComp(){ return comp; }
	Player* getUser(){ return user; }
	static GameMechanic* getInstance();
};

#endif