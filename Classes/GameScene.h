#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include <map>
#include <vector>

#include "cocos2d.h"
#include "Card.h"
#include "Config.h"
#include "GameMechanic.h"

using namespace cocos2d;
using namespace std;

class GameScene: public Scene
{
public:
	GameScene();
	~GameScene();

	virtual bool init();
	
	void addCard(float firstDelay, Card* card, CardPlace place);
	void addStartCards(vector<Card*> cards, bool isReverse);

	static GameScene* instance;
	static GameScene* getInstance();
	
private:
	map<CardPlace, CardSprite*> cards;

	void createBackground();
};
#endif

