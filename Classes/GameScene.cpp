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

	for (int i = CardPlace::COMP_0; i <= CardPlace::PACK; i++)
	{
		CardPlace place = (CardPlace)i;
		std::string textureName;
		int opacity;
		if (place == CardPlace::PACK)
		{
			textureName = "image/card_shirt.png";
			opacity = 255;
		}
		else
		{
			textureName = "image/card_bg.png";
			opacity = 150;
		};

		Sprite* placeSprite = Sprite::create( textureName );
		Vec2 pos = CardSprite::getCardPosition(place);
		
		placeSprite->setScale(CARD_SCALE);
		placeSprite->setPosition(pos);
		placeSprite->setOpacity(opacity);

		this->addChild(placeSprite);
	}
	
	/*
	for (int i = 0; i < 9; i++)
	{
		CardPlace place = (CardPlace)i;
		Card c;
		c.range = (Range) (rand() % RANGE_COUNT);
		c.suite = (Suite)(rand() % SUITE_COUNT);
		CardSprite* card = CardSprite::createCard(c, place);
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
