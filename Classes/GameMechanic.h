#ifndef _GAMEMECHANIC_H
#define _GAMEMECHANIC_H

#include "Player.h"
#include "CardPool.h"
#include "GameScene.h"
#include "CombinationManager.h"
#include "AI.h"
#include "cocos2d.h"
using namespace cocos2d;

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
	int bank;

	std::vector<Card*> toPreflopState();
	std::vector<Card*> toFlopState();
	std::vector<Card*> toTurnState();
	std::vector<Card*> toRiverState();

	void initTurn();
	void compTurn();
	void initUserTurn();
	void endState(float delay = 2);

	static GameMechanic* instance;
public:
	GameMechanic();
	~GameMechanic();
	
	void incrementState();
	void incrementState(float delay);
	Combination* getUserCombination();
	void setUserTurn(Turn* turn);

	Player* getComp(){ return comp; }
	Player* getUser(){ return user; }
	int getBank() {return bank; }
	GameState getGameState() { return state; }

	static GameMechanic* getInstance();
};

#endif