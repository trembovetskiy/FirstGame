#include "GameMechanic.h"

GameMechanic::GameMechanic()
{
	this->state = GameState::BEGIN_STATE;
	this->comp = new Player( PlayerType::COMPUTER );
	this->user = new Player( PlayerType::USER );
	this->compFirst = true;
}

GameMechanic::~GameMechanic()
{
	delete(comp);
	delete(user);
	for (int i = 0; i < tableCards.size(); i++)
		delete( tableCards[ i ] );
	delete ( CardPool::getInstance() );
}

void GameMechanic::incrementState()
{
	
	switch (this->state)
	{
	case GameState::BEGIN_STATE:

		GameScene::getInstance()->staticViewSynchronize();
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
		comp->setCards(cards[0], cards[1]);
		comp->setBet( SMALL_BLIND );

		user->setCards(cards[2], cards[3]);
		user->setBet( BIG_BLIND );
	}
	else
	{
		user->setCards(cards[0], cards[1]);
		user->setBet( SMALL_BLIND );

		comp->setCards(cards[2], cards[3]);
		comp->setBet( BIG_BLIND );
	}

	float delay = gameScene->addStartCards(cards, !this->compFirst);
	gameScene->staticViewSynchronize(delay);
	//
	CombinationManager* m = new CombinationManager();
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