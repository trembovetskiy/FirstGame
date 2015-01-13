#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
	delete( GameMechanic::getInstance());
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
			textureName = SHIRT_TEXTURE_NAME;
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
	
	GameMechanic *mechanic = GameMechanic::getInstance();
	mechanic->incrementState();
	
}

void GameScene::addCard(float firstDelay, Card* card, CardPlace place)
{
	
	CardSprite* c = CardSprite::createCard(card, place);
	this->addChild(c);
	c->animate( firstDelay );
}

void GameScene::addStartCards(vector<Card*> cards, bool isReverse)
{

	for (int i = 0; i < cards.size(); i++)
	{
		int placeIndex = isReverse ? (2 + i) % 4 : i;
		float delay = MIDDLE_CARD_DELAY * i;

		this->addCard(delay, cards[i], (CardPlace)placeIndex);
	};
}

bool GameScene::init()
{
	if (!Scene::init())
		return false;
	this->createBackground();

	return true;
}

GameScene* GameScene::instance = nullptr;
GameScene* GameScene::getInstance()
{
	if (instance == NULL)
	{
		instance = new GameScene();
		if (instance && instance->init())
		{
			instance->autorelease();
		}
	}
	return instance;
}

