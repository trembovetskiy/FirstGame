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
	}
	else
	{
		this->initUserTurn();
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
		this->incrementState(0.5);

	});

	Sequence* seq = Sequence::create(delayAction, callback, nullptr);
	GameScene::getInstance()->runAction(seq);

}

void GameMechanic::incrementState()
{
	vector<Card*> cards;
	
	switch (this->state)
	{
	case GameState::BEGIN_STATE:

		GameScene::getInstance()->staticViewSynchronize();
		cards = this->toPreflopState();
		break;

	case GameState::PREFLOP:
		cards = this->toFlopState();
		break;

	case GameState::FLOP:
		cards = this->toTurnState();
		break;

	case GameState::TURN:
		cards = this->toRiverState();
		break;

	default:
		break;
	}

	if (cards.size() == 0)
		return;

	GameScene* gameScene = GameScene::getInstance();
	float delay = gameScene->addStartCards(cards, !this->compFirst);
	gameScene->staticViewSynchronize(delay);


	DelayTime* delayAction = DelayTime::create(delay + COMPUTER_TURN_DELAY);
	auto callback = CallFunc::create([this]() {
		this->initTurn();
	});

	Sequence* seq = Sequence::create(delayAction, callback, nullptr);
	GameScene::getInstance()->runAction(seq);

	this->state = (GameState) ( this->state + 1 );
}

void GameMechanic::incrementState(float delay)
{
	DelayTime* delayAction = DelayTime::create(delay);
	auto callback = CallFunc::create([this]() {
		this->incrementState();


	});

	Sequence* seq = Sequence::create(delayAction, callback, nullptr);
	GameScene::getInstance()->runAction(seq);
}


std::vector<Card*> GameMechanic::toPreflopState()
{
	this->bank = 0;
	CardPool* cardPool = CardPool::getInstance();
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

	return cards;

}

std::vector<Card*> GameMechanic::toFlopState()
{
	CardPool* cardPool = CardPool::getInstance();
	GameScene* gameScene = GameScene::getInstance();
	std::vector<Card*> cards;
	for (int i = 0; i < 3; i++)
	{
		Card* card = cardPool->getRandomCard();
		cards.push_back(card);
		this->tableCards.push_back(card);
	}

	return cards;
}

std::vector<Card*> GameMechanic::toTurnState()
{
	CardPool* cardPool = CardPool::getInstance();
	GameScene* gameScene = GameScene::getInstance();
	std::vector<Card*> cards;
	Card* card = cardPool->getRandomCard();
	cards.push_back(card);
	this->tableCards.push_back(card);

	return cards;
}

std::vector<Card*> GameMechanic::toRiverState()
{
	CardPool* cardPool = CardPool::getInstance();
	GameScene* gameScene = GameScene::getInstance();
	std::vector<Card*> cards;
	Card* card = cardPool->getRandomCard();
	cards.push_back(card);
	this->tableCards.push_back(card);

	return cards;
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