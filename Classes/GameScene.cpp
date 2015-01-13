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
	
}

void GameScene::createLabels()
{
	
	Vec2 pos[2];
	pos[PlayerType::USER] = CardSprite::getCardPosition(CardPlace::USER_0) + Vec2(TABLE_DELTA_X / 2, -TABLE_DELTA_Y / 2);
	pos[PlayerType::COMPUTER] = CardSprite::getCardPosition(CardPlace::COMP_0) + Vec2(TABLE_DELTA_X / 2, TABLE_DELTA_Y / 2);

	Vec2 betPos[2];
	betPos[PlayerType::USER] = CardSprite::getCardPosition(CardPlace::USER_1) + Vec2(TABLE_DELTA_X  , 0);
	betPos[PlayerType::COMPUTER] = CardSprite::getCardPosition(CardPlace::COMP_1) + Vec2(TABLE_DELTA_X , 0);

	for (int i = PlayerType::COMPUTER; i <= PlayerType::USER; i++)
	{
		Sprite* t = Sprite::create();
		t->setTextureRect(Rect(0, 0, 80, 30));
		t->setColor(Color3B(40, 230, 0));
		t->setOpacity(120);
		t->setPosition(pos[i]);
		this->addChild(t);

		LabelTTF* label = LabelTTF::create("0$", "fonts/GameFont.ttf", LABEL_FONT_SIZE);
		label->setPosition(pos[i]);
		this->moneyLabels[i] = label;
		this->addChild(label);

		label = LabelTTF::create("Bet:", "fonts/GameFont.ttf", LABEL_FONT_SIZE);
		label->setPosition(betPos[i]);
		label->setColor(Color3B::ORANGE);
		this->betLabels[i] = label;
		this->addChild(label);
	}
}

void GameScene::addCard(float firstDelay, Card* card, CardPlace place)
{
	
	CardSprite* c = CardSprite::createCard(card, place);
	this->addChild(c);
	c->animate( firstDelay );
}

float GameScene::addStartCards(vector<Card*> cards, bool isReverse)
{

	for (int i = 0; i < cards.size(); i++)
	{
		int placeIndex = isReverse ? (2 + i) % 4 : i;
		float delay = MIDDLE_CARD_DELAY * i;

		this->addCard(delay, cards[i], (CardPlace)placeIndex);
	};

	return MIDDLE_CARD_DELAY * cards.size();
}

bool GameScene::init()
{
	if (!Scene::init())
		return false;

	this->createBackground();
	this->createLabels();

	GameMechanic *mechanic = GameMechanic::getInstance();
	mechanic->incrementState();

	return true;
}


void GameScene::staticViewSynchronize()
{
	GameMechanic* mechanic = GameMechanic::getInstance();
	Player* comp = mechanic->getComp();
	Player* user = mechanic->getUser();

	this->moneyLabels[PlayerType::COMPUTER]->setString( std::to_string(comp->getMoney()) + "$");
	this->moneyLabels[PlayerType::USER]->setString(std::to_string(user->getMoney()) + "$");

	if (comp->getBetMoney() > 0)
		this->betLabels[PlayerType::COMPUTER]->setString("Bet: " + std::to_string(comp->getBetMoney()) + "$");

	if (comp->getBetMoney() > 0)
		this->betLabels[PlayerType::USER]->setString("Bet: " + std::to_string(user->getBetMoney()) + "$");
}

void GameScene::staticViewSynchronize(double delay)
{
	DelayTime* delayAction = DelayTime::create(delay);
	auto callback = CallFunc::create([this]() {
		this->staticViewSynchronize();
	});

	Sequence* seq = Sequence::create(delayAction, callback, nullptr);
	this->runAction(seq);
}

//-----------------------------static----------------------------------
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

