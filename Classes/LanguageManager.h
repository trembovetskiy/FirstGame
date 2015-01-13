#ifndef LanguageManager_h
#define LanguageManager_h

#include <string>
using std::string;

#include "cocos2d.h"
USING_NS_CC;

#include "json/rapidjson.h"
#include "json/document.h"
using namespace rapidjson;

class LanguageManager
{
	Document document;
	LanguageManager(); 
	static LanguageManager* _instance;
public:
	static LanguageManager* getInstance();
	string getStringForKey(string key);
};
#endif