//https://github.com/guilhermeagostinelli/levenshtein/blob/master/levenshtein.cpp
#pragma once
#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <iostream>

class Levenshtein {
public:
	static int levenshteinDist(std::string word1, std::string word2);
};
#endif