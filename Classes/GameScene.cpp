#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
	delete( GameMechanic::getInstance());
}

void GameScene::onBtnClick(Object* sender)
{
	MenuItemImage* m = (MenuItemImage*)sender;
	int num = m->getTag();
	Turn* turn = new Turn;
	turn->turn = (Turns)num;
	turn->value = 0;

	GameMechanic::getInstance()->setUserTurn( turn );

	for (int i = Turns::TURN_CHECK; i <= Turns::TURN_FOLD; i++)
		this->userButtons[i]->setVisible(false);
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

	//auto menu = Menu::create(m, NULL);
	//menu->setPosition(50, 50);
	//this->addChild(menu);
	
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

		label = LabelTTF::create(LanguageManager::getInstance()->getStringForKey("BetCaption").c_str() , "fonts/times.ttf", LABEL_FONT_SIZE);
		label->setPosition(betPos[i]);
		label->setColor(Color3B::ORANGE);
		this->betLabels[i] = label;
		this->addChild(label);

		label = LabelTTF::create(LanguageManager::getInstance()->getStringForKey("TurnCaption").c_str(), "fonts/times.ttf", LABEL_FONT_SIZE);
		label->setPosition(betPos[i] + Vec2(0,-40));
		label->setColor(Color3B::RED);
		label->setVerticalAlignment(cocos2d::kCCVerticalTextAlignmentTop);
		this->turnLabels[i] = label;
		this->addChild(label);
	}

	combinationLabel = LabelTTF::create("", "fonts/times.ttf", LABEL_FONT_SIZE);
	combinationLabel->setPosition(pos[USER] + Vec2(0, -50));
	combinationLabel->setColor(Color3B(50, 200, 50));
	this->addChild(combinationLabel);

	this->bankLabel = LabelTTF::create(LanguageManager::getInstance()->getStringForKey("BankCaption").c_str(), "fonts/times.ttf", LABEL_FONT_SIZE);
	this->bankLabel->setPosition(CardSprite::getCardPosition(CardPlace::PACK) + Vec2(TABLE_DELTA_X , 0));
	this->addChild( this->bankLabel );
}

void GameScene::createButtons()
{
	std::string texName[] = {"check","call","raise","pass"};
	auto userMenu = Menu::create();
	userMenu->setPosition(Vec2(0, 0));

	for (int i = Turns::TURN_CHECK; i <= Turns::TURN_FOLD; i++)
	{
		MenuItemImage* m = MenuItemImage::create("buttons/" + texName[i] + ".png", "buttons/" + texName[i] + "_press.png", "", CC_CALLBACK_1(GameScene::onBtnClick, this));
		m->setTag(i);
		m->setVisible(false);
		this->userButtons[i] = m;

		userMenu->addChild(m);
	}
	this->addChild(userMenu);

}

void GameScene::addCard(float firstDelay, Card* card, CardPlace place)
{
	
	CardSprite* c = CardSprite::createCard(card, place);
	this->addChild(c);
	c->animate( firstDelay );
}

float GameScene::addStartCards(vector<Card*> cards, bool isReverse)
{
	GameState state = GameMechanic::getInstance()->getGameState();

	for (int i = 0; i < cards.size(); i++)
	{
		int placeIndex;
		if (state == GameState::BEGIN_STATE)
			placeIndex = isReverse ? (2 + i) % 4 : i;
		else if (state == GameState::PREFLOP)
			placeIndex = CardPlace::TABLE_0 + i;
		else if (state == GameState::FLOP)
			placeIndex = CardPlace::TABLE_3;
		else if (state == GameState::TURN)
			placeIndex = CardPlace::TABLE_4;
		

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
	this->createButtons();

	GameMechanic *mechanic = GameMechanic::getInstance();
	mechanic->incrementState();

	return true;
}


void GameScene::staticViewSynchronize() 
{
	GameMechanic* mechanic = GameMechanic::getInstance();
	Player* comp = mechanic->getComp();
	Player* user = mechanic->getUser();
	Player* players[2] = { comp, user };

	for (int i = PlayerType::COMPUTER; i <= PlayerType::USER; i++)
	{
		PlayerType pType = (PlayerType)i;
		Turn* turn = players[i]->getCurrentTurn();

		LabelTTF* label = this->turnLabels[pType];
		std::string txt = LanguageManager::getInstance()->getStringForKey("TurnCaption") + "\n";
		if (turn != NULL)
		{
			txt += LanguageManager::getInstance()->getStringForKey("Turn" + std::to_string(turn->turn));
			if (turn->value > 0)
				txt += " " + std::to_string(turn->value);
		}
		label->setString(txt);
	
		this->moneyLabels[pType]->setString( std::to_string(players[i]->getMoney()) + "$");

		std::string betTxt = LanguageManager::getInstance()->getStringForKey("BetCaption");
		if (players[i]->getBetMoney() > 0) betTxt += std::to_string( players[i]->getBetMoney()) + "$";
		
		this->betLabels[pType]->setString(betTxt);
	}

	Combination* combination = mechanic->getUserCombination();
	this->combinationLabel->setString( GameScene::getCombinationText(combination ));

	std::string bankText = LanguageManager::getInstance()->getStringForKey("BankCaption").c_str();
	if (mechanic->getBank() > 0)
		bankText += " " + std::to_string(mechanic->getBank()) + "$";
	this->bankLabel->setString(bankText);
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


void GameScene::setUserButtons(std::vector<Turn*> turns)
{
	int posIndex = 0;
	for (std::vector<Turn*>::iterator i = turns.begin(); i != turns.end(); i++)
	{
		Turn* turn = *i;
		auto btn = this->userButtons[turn->turn];
		btn->setPosition(Vec2(150 + btn->getContentSize().width * posIndex, 30));
		btn->setVisible(true);
		posIndex++;
	}
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

std::string GameScene::getCombinationText(Combination* comb)
{
	std::string txt = LanguageManager::getInstance()->getStringForKey("CombCaption")+"\n";
	if (comb != NULL)
	{
	
		txt+= LanguageManager::getInstance()->getStringForKey("Combination"+ std::to_string(comb->comb));
		std::string cardText = RANGE_NAMES[comb->card->range];
		if (comb->card->range > Range::CARD_10)
			cardText = cardText.substr(0, 1);
	
		std::transform(cardText.begin(), cardText.end(), cardText.begin(), toupper);
		txt += " (" + cardText + ")";
	}
	return txt;	
}

