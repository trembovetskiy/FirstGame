#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include <map>
#include <vector>

#include "cocos2d.h"
#include "Card.h"
#include "Config.h"
#include "LanguageManager.h"
#include "CombinationManager.h"
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
	float addStartCards(vector<Card*> cards, bool isReverse); 

	void staticViewSynchronize();
	void staticViewSynchronize(double delay);
	void setUserButtons(std::vector<Turn*> turns);
	void clearCards(float delay = 0);

	float showFinalEffect(GameResult result);

	static GameScene* instance;
	static GameScene* getInstance();
	
private:
	map<CardPlace, CardSprite*> cards;

	LabelTTF* moneyLabels[2];
	LabelTTF* betLabels[2];
	LabelTTF* combinationLabel;
	LabelTTF* turnLabels[2];
	LabelTTF* bankLabel;

	MenuItemImage* userButtons[4];

	void createBackground();
	void createLabels();
	void createButtons();

	static std::string getCombinationText(Combination* comb);

	void onBtnClick(Object* sender);
};
#endif

