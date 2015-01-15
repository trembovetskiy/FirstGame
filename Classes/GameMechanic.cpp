#include "GameMechanic.h"
USING_NS_CC;

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

Combination* GameMechanic::getUserCombination()
{
	if (this->user != NULL)
		return CombinationManager::getCurrentCombination(this->user, this->tableCards);
	else
		return nullptr;
}

void GameMechanic::initTurn()
{
	if (this->compFirst)
	{
		this->compTurn();
		//this->initUserTurn();
	}
}


void GameMechanic::compTurn()
{
	vector<Turn*> compTurns = comp->getAllowTurns(this->user);
	Turn* compTurn = AI::getTurn(this->comp, this->tableCards, compTurns);
	comp->setTurn(compTurn);
	GameScene::getInstance()->staticViewSynchronize();

	if (this->compFirst || compTurn->turn == Turns::TURN_RAISE)
	{
		this->initUserTurn();
	}
	else
	{
		this->endState();
	}
}

void GameMechanic::initUserTurn()
{
	vector<Turn*> turns = this->user->getAllowTurns(this->comp);
	GameScene::getInstance()->setUserButtons(turns);
}


void GameMechanic::setUserTurn(Turn* turn)
{
	user->setTurn(turn);
	GameScene::getInstance()->staticViewSynchronize();
	if (!this->compFirst || turn->turn == Turns::TURN_RAISE)
	{
		this->compTurn();
	}
	else
	{
		this->endState();
	}

}

void GameMechanic::endState(float delay)
{
	

	DelayTime* delayAction = DelayTime::create(delay);
	auto callback = CallFunc::create([this]() {
		this->bank += this->comp->releaseTurn();
		this->bank += this->user->releaseTurn();
		GameScene::getInstance()->staticViewSynchronize();
	});

	Sequence* seq = Sequence::create(delayAction, callback, nullptr);
	GameScene::getInstance()->runAction(seq);

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
	this->bank = 0;
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


	DelayTime* delayAction = DelayTime::create(delay + COMPUTER_TURN_DELAY);
	auto callback = CallFunc::create([this]() {
		this->initTurn();
	});

	Sequence* seq = Sequence::create(delayAction, callback, nullptr);
	GameScene::getInstance()->runAction(seq);

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