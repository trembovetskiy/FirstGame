#include "GameMechanic.h"

GameMechanic::GameMechanic()
{
	this->state = GameState::BEGIN_STATE;
	this->comp = nullptr;
	this->user = nullptr;
	this->compFirst = true;
}

GameMechanic::~GameMechanic()
{
	delete(comp);
	delete(user);
	for (int i = 0; i < tableCards.size(); i++)
		delete( tableCards[ i ] );
}

void GameMechanic::incrementState()
{
	switch (this->state)
	{
	case GameState::BEGIN_STATE:
		this->toPreflopState();
		break;
	default:
		break;
	}

	this->state = (GameState) ( this->state + 1 );
}


void GameMechanic::toPreflopState()
{
	CardPool* cardPool = CardPool::getInstance();
	GameScene* gameScene = GameScene::getInstance();
	std::vector<Card*> cards;
	for (int i = 0; i < 4; i++)
		cards.push_back(cardPool->getRandomCard());

	if (this->compFirst)
	{
		comp = new Player(cards[0], cards[1]);
		user = new Player(cards[2], cards[3]);
		
	}
	else
	{
		user = new Player(cards[0], cards[1]);
		comp = new Player(cards[2], cards[3]);
	}

	gameScene->addStartCards(cards, !this->compFirst);
}

GameMechanic* GameMechanic::instance = nullptr;
GameMechanic* GameMechanic::getInstance()
{
	if (instance == NULL)
	{
		instance = new GameMechanic();
	};

	return instance;
}