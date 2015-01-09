#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "Card.h"
#include "VisualConfig.h"
using namespace cocos2d;

class GameScene: public Scene
{
public:
	GameScene();
	~GameScene();

	virtual bool init();
	CREATE_FUNC(GameScene);
private:
	void createBackground();
	CardSprite* card;
};
#endif

