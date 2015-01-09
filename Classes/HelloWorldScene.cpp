#include "HelloWorldScene.h"

USING_NS_CC;

HelloWorld::HelloWorld()
{

}


HelloWorld::~HelloWorld()
{

}

bool HelloWorld::init()
{
	if (!Scene::init())
		return false;
	/*
	auto background = Sprite::create("image/splash.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(background);
	*/

	return true;
}

