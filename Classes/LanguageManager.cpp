#include "LanguageManager.h"

LanguageManager* LanguageManager::_instance = 0;

LanguageManager::LanguageManager()
{
	string fileName;
	// detect current language
	switch (CCApplication::sharedApplication()->getCurrentLanguage())
	{
	case kLanguageEnglish:
		fileName = "en.json";
		break;
	case kLanguageRussian:
		fileName = "ru.json";
		break;
	default:
		CCLOG("Unknown language. Use english");
		fileName = "en.json";
		break;
	};

	ssize_t size;
	const char* buf = (const char*)CCFileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "r", &size);
	string content(buf);
	string clearContent = content.substr(0, content.rfind('}') + 1);

	document.Parse<0>(clearContent.c_str());
	if (document.HasParseError())
	{
		CCLOG("Language file parsing error!");
		return;
	}
}

LanguageManager* LanguageManager::getInstance()
{
	if (!_instance)
		_instance = new LanguageManager();
	return _instance;
}

string LanguageManager::getStringForKey(string key)
{
	return document[key.c_str()].GetString();
}