#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class HelloWorld: public Scene
{
public:
	HelloWorld();
	~HelloWorld();

	virtual bool init();
	CREATE_FUNC(HelloWorld);
	/*void onEnter() override;

private:
	void loadingCallBack(Texture2D *texture);*/
};

#endif // __HELLOWORLD_SCENE_H__
