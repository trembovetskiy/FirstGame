#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

void GameScene::createBackground()
{
	auto background = Sprite::create();
	background->setTexture("image/background.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(background);

	
	auto mySprite = Sprite::create();
	mySprite->setTexture("2.png");

	mySprite->setPosition(Vec2(200, 200));

	//auto moveTo = MoveTo::create(2, Vec2(1000, 1000));
	//mySprite->runAction(moveTo);
	
	
	

	//this->addChild(mySprite);
	for (int i = 0; i < 9; i++)
	{
		CardPlace place = (CardPlace)i;
		Card c;
		c.range = (Range) (rand() % RANGE_COUNT);
		c.suite = (Suite)(rand() % SUITE_COUNT);
		CardSprite* card = CardSprite::createCard(c, place);
		this->addChild(card);
	}
	/*
	Card c;
	for (int r_i = 0; r_i < RANGE_COUNT; r_i++)
	for (int s_i = 0; s_i < SUITE_COUNT; s_i++)
	{
		c.range = (Range) r_i;
		c.suite = (Suite) s_i;
		Vec2 pos;
		pos.x = 100 + r_i * 50;
		pos.y = 100 + s_i * 100;
		CardSprite* card = CardSprite::createCard(c, pos);

		this->addChild(card);
	}
	*/
	
}

bool GameScene::init()
{
	if (!Scene::init())
		return false;
	this->createBackground();

	//card = new Card();
	//card->createCard();
	//this->addChild(card);

	return true;
}
