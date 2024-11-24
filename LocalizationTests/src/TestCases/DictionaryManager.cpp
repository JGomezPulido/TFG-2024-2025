#include "DictionaryManager.h"

#include <nuspell/finder.hxx>
#include <vector>
#include <filesystem>
#include <iostream>

DictionaryManager::DictionaryManager() : dictionaries()
{
}

bool DictionaryManager::setup()
{
	dirs = std::vector<std::filesystem::path>();
	nuspell::append_default_dir_paths(dirs);
	
	try {
		loadDict(Language::EnglishUS, "en_US");
		loadDict(Language::Spanish, "es_ES");
	}
	catch (const nuspell::Dictionary_Loading_Error& e) {
		std::cout << e.what() << std::endl;
	}

	
	
	return !dictionaries.empty();
}

nuspell::Dictionary& DictionaryManager::getDict(Language lan)
{
	// TODO: Insertar una instrucción "return" aquí
}

nuspell::Dictionary DictionaryManager::loadDict(Language lan, const std::string& dictStem)
{
	auto dictPath = nuspell::search_dirs_for_one_dict(dirs, dictStem);
	auto dict = nuspell::Dictionary();
	dict.load_aff_dic(dictPath);
	dictionaries.insert({ lan, dict });
	return dict;
	
	
}
