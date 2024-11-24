#pragma once

#include <unordered_map>
#include <nuspell/dictionary.hxx>
#include <filesystem>
#include <string>
#include <vector>
class DictionaryManager {
public:
	enum class Language {
		EnglishUS,
		Spanish
	};

public:
	DictionaryManager();
	bool setup();
	nuspell::Dictionary& getDict(Language lan);
private:
	nuspell::Dictionary loadDict(Language lan, const std::string& dictStem);
private:
	std::unordered_map<Language, nuspell::Dictionary> dictionaries;
	std::vector<std::filesystem::path> dirs;
};